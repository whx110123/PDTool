#include "frmanalysis.h"
#include "ui_frmanalysis.h"
#include "quiwidget.h"
#include <QString>
#include <app.h>
#include <iec101.h>
#include <iec103com.h>
#include <iec103netbaoxin.h>
#include <iec103netwiscom.h>
#include <measuredterminal.h>
#include <modbusrtu.h>
#include <modbustcp.h>
#include "myhighlighter.h"
#include "iec104.h"


frmAnalysis::frmAnalysis(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmAnalysis)
{
	ui->setupUi(this);
	highlighter1 = new myhighlighter(ui->resulttext->document());
	highlighter2 = new myhighlighter(ui->originaltext->document());
	modbusdlg = new DialogModbus(this);
	initForm();
	initConfig();
}

frmAnalysis::~frmAnalysis()
{
	delete highlighter1;
	delete highlighter2;
	qDeleteAll(MyBase::mConfig.groups);
	MyBase::mConfig.groups.clear();
	delete ui;
}

void frmAnalysis::initForm()
{
	ui->protocolcbox->addItems(App::Protocollst);
}

void frmAnalysis::initConfig()
{
	ui->protocolcbox->setCurrentIndex(ui->protocolcbox->findText(App::DefaultProtocol));

	highlighter1->hlformat.setForeground(Qt::magenta);
	highlighter1->hlformat.setFontWeight(QFont::Bold);
	highlighter2->hlformat.setForeground(Qt::magenta);
	highlighter2->hlformat.setFontWeight(QFont::Bold);
	//    connect(ui->protocolcbox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));
}

void frmAnalysis::on_clearBtn_clicked()
{
	ui->originaltext->clear();
	ui->resulttext->clear();
}

void frmAnalysis::on_protocolcbox_currentIndexChanged(const QString& arg1)
{
	emit emitstr(arg1);
}

void frmAnalysis::on_highlightEdit_textChanged(const QString& arg1)
{
	highlighter1->hlstr = arg1;
	highlighter2->hlstr = arg1;
	ui->resulttext->setText(ui->resulttext->toPlainText());
	ui->originaltext->setText(ui->originaltext->toPlainText());
}


void frmAnalysis::on_fontcolor_clicked()
{
	QColor color = QColorDialog::getColor(Qt::magenta, this, tr("颜色对话框"));
	if(color.isValid())
	{
		highlighter1->hlformat.setForeground(color);
		//      highlighter1->hlformat.setFontWeight(QFont::Bold);
		highlighter2->hlformat.setForeground(color);
		//      highlighter2->hlformat.setFontWeight(QFont::Bold);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}

void frmAnalysis::on_backgroundcolor_clicked()
{
	QColor color = QColorDialog::getColor(Qt::white, this, tr("颜色对话框"));
	if(color.isValid())
	{
		highlighter1->hlformat.setBackground(color);
		highlighter2->hlformat.setBackground(color);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}


void frmAnalysis::on_fontchange_clicked()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, this);
	if(ok)
	{
		highlighter1->hlformat.setFont(font);
		highlighter2->hlformat.setFont(font);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}

void frmAnalysis::on_pushButton_Analysis_clicked()
{
	ui->resulttext->clear();
	App::readConfig();
	QString data = ui->originaltext->toPlainText();
	if(data.length() <= 0)
	{
		return;
	}

	MyBase *myprotocol = createByName(ui->protocolcbox->currentText());

	if(myprotocol)
	{
		QString tmp;
		int i = 1;
		QByteArray buffer = QUIHelper::hexStrToByteArray(data);
		while(!buffer.isEmpty())
		{
			tmp.append(QString("####第%1帧####\r\n").arg(i++));
			if(myprotocol->init(buffer))
			{
				tmp.append(myprotocol->showToText());
				buffer.remove(0, myprotocol->len);
			}
			else
			{
				if(ui->checkBox_error->isChecked())
				{
					tmp.append(myprotocol->showToText());
				}
				tmp.append(myprotocol->error);
				break;
			}
			tmp.append("****************************************************************************************************\r\n");
		}
		ui->resulttext->setText(tmp);
		delete myprotocol;
		myprotocol = NULL;
	}

}


void frmAnalysis::on_pushButton_change_clicked()
{
	QString data = ui->originaltext->toPlainText();
	if(ui->pushButton_change->text() == "字母大写")
	{
		ui->pushButton_change->setText("字母小写");
		ui->originaltext->setText(data.toUpper());
	}
	else
	{
		ui->pushButton_change->setText("字母大写");
		ui->originaltext->setText(data.toLower());
	}
}

void frmAnalysis::on_pushButton_clean_clicked()
{
	QString data = ui->originaltext->toPlainText();
	QStringList datalist = data.split('\n');
	data.clear();
	for(int i = 0; i < datalist.count(); i++)
	{
		QString tmp = datalist.at(i).trimmed();
		if(tmp.isEmpty())
		{
			continue;
		}
		if((tmp.at(0) >= '0' && tmp.at(0) <= '9') || (tmp.at(0) >= 'a' && tmp.at(0) <= 'f') || (tmp.at(0) >= 'A' && tmp.at(0) <= 'F'))
		{
			tmp.remove("0x");
			data.append(tmp + "\n");
		}

	}
	ui->originaltext->setText(data.trimmed());
}

void frmAnalysis::on_pushButton_clicked()
{
	modbusdlg->exec();
}

void frmAnalysis::initProtocolConfig()
{

}

MyBase *frmAnalysis::createByName(QString name)
{
	initProtocolConfig();

	MyBase *protocol = NULL;
	if(name == IEC_104)           //分析104报文
	{
		protocol = new IEC104;
	}
	else if(name == IEC_101)		//分析101报文
	{
		protocol = new IEC101;
	}
	else if(name == IEC_103WISCOMNET)//分析金智网络103报文
	{
		protocol = new IEC103NetWiscom;
	}
	else if(name == IEC_103COM ||		//分析串口103报文
			name == IEC_103HUABEI)      //分析华北103报文
	{
		protocol = new IEC103COM;
	}
	else if(name == IEC_103BAOXINNET || name == IEC_103XUJINET)
	{
		protocol = new IEC103NetBaoXin;
	}
	else if(name == IEC_103ASDU || name == IEC_103NANZINET)
	{
		protocol = new IEC103Asdu;
	}
	else if(name == MODBUS_RTU)
	{
		protocol = new ModbusRTU;
	}
	else if(name == MODBUS_TCP)
	{
		protocol = new ModbusTCP;
	}
	else if(name == MEASUREDTERMINAL_NW_NET)
	{
		protocol = new MeasuredTerminal;
	}

	if(protocol)
	{
		protocol->protocolName = ui->protocolcbox->currentText();
	}
	return protocol;
}
