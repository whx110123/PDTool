#include "dialogdebug.h"
#include "ui_dialogdebug.h"
#include "app.h"

#include <quiwidget.h>

DialogDebug::DialogDebug(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogDebug)
{
	ui->setupUi(this);
}

DialogDebug::~DialogDebug()
{
	delete ui;
}

void DialogDebug::on_Bt1_clicked()
{
	QString	text = ui->textmsg->toPlainText().trimmed();
	if(text.isEmpty())
	{
		return;
	}

	QString splitstr;
	QString keystr;
	QString valuesstr;
	if(ui->cb1->currentText().contains("模拟发送的报文"))
	{
		splitstr = "数据";
		keystr = "收";
		valuesstr = "发";
	}
	else if(ui->cb1->currentText().contains("模拟接收的报文"))
	{
		splitstr = "数据";
		keystr = "发";
		valuesstr = "收";
	}
	else
	{
		return;
	}

	QStringList strlist = text.split(splitstr);
	if(strlist.isEmpty())
	{
		return;
	}
	QString key;
	QStringList values;
	App::m_map.clear();

	if(ui->Bt2->text() == "正在模拟")
	{
		ui->Bt2->setText("开始模拟");
	}
	int i = 0;
	while(i < strlist.length())
	{
		if(strlist.at(i).startsWith(keystr))
		{
			key = msgTodata(strlist.at(i));
			values.clear();
			i++;
			if(key.isEmpty())
			{
				continue;
			}
			while(i < strlist.length() && strlist.at(i).startsWith(valuesstr))
			{
				values << msgTodata(strlist.at(i));
				i++;
			}
			if(!values.isEmpty())
			{
				App::m_map.insert(key, values);
				if(ui->Bt1->text() == "开始模拟")
				{
					ui->Bt1->setText("正在模拟");
				}
			}
		}
		else
		{
			i++;
		}
	}


}

QString DialogDebug::msgTodata(QString msg)
{
	QString data = msg.section('\n', 1).trimmed();
	QByteArray buffer;
	buffer = QUIHelper::hexStrToByteArray(data);
	data = buffer.toHex(' ').toUpper();
	return data;

}


void DialogDebug::on_Bt2_clicked()
{
	QString	text = ui->textin->toPlainText().trimmed();
	if(text.isEmpty())
	{
		return;
	}
	QStringList linelist = text.split('\n');
	if(linelist.isEmpty())
	{
		return;
	}
	App::m_map.clear();

	if(ui->Bt1->text() == "正在模拟")
	{
		ui->Bt1->setText("开始模拟");
	}
	for(int i = 0; i < linelist.length(); i++)
	{
		QString line = linelist.at(i);
		line = line.trimmed();
		line = line.replace("\r", "");
		line = line.replace("\n", "");
		if(!line.isEmpty())
		{
			QStringList list = line.split(";");
			if(list.count() > 1)
			{
				QString key = list.at(0).trimmed().toUpper();
				QStringList values;
				for(int j = 1; j < list.count(); j++)
				{
					values << list.at(j).trimmed().toUpper();
				}
				if(!key.isEmpty() && !values.isEmpty())
				{
					App::m_map.insert(key, values);
					if(ui->Bt2->text() == "开始模拟")
					{
						ui->Bt2->setText("正在模拟");
					}
				}
			}
		}
	}

}

void DialogDebug::on_Bt_clear_clicked()
{
	App::m_map.clear();
	ui->Bt1->setText("开始模拟");
	ui->Bt2->setText("开始模拟");
	ui->textmsg->clear();
	ui->textin->clear();
}



void DialogDebug::on_lineEdit_textChanged(const QString& arg1)
{
	App::debugdelay = arg1.toInt();
}
