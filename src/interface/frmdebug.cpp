#include "frmdebug.h"
#include "ui_frmdebug.h"

#include <QTimer>
#include <app.h>

frmDebug::frmDebug(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmDebug)
{
	ui->setupUi(this);
	initfrm();
}

frmDebug::~frmDebug()
{
	delete ui;
}

void frmDebug::initfrm()
{
	timercycle = new QTimer(this);
	recflag = 0;

	connect(timercycle, &QTimer::timeout, this, &frmDebug::sendDatacycle);
	ui->comboBox->addItems(App::Transferlst);
	mapline.insert(1, ui->linedata1);
	mapline.insert(2, ui->linedata2);
	mapline.insert(3, ui->linedata3);
	mapline.insert(4, ui->linedata4);
	mapline.insert(5, ui->linedata5);
	mapline.insert(6, ui->linedata6);

	mapchk.insert(1, ui->checkBox1);
	mapchk.insert(2, ui->checkBox2);
	mapchk.insert(3, ui->checkBox3);
	mapchk.insert(4, ui->checkBox4);
	mapchk.insert(5, ui->checkBox5);
	mapchk.insert(6, ui->checkBox6);
	initdataList();
}

void frmDebug::initdataList()
{
	lstindex = 0;
	dataList.clear();

	QString data;
	mapstr.clear();
	for(int i = 0; i < mapline.size(); i++)
	{
		mapline[i + 1]->setStyleSheet("background-color:rgba(255,255,255,255);color:rgba(0,0,0,255)");
		data = mapline[i + 1]->text();
		if(mapchk[i + 1]->isChecked() && !data.trimmed().isEmpty())
		{
			dataList.append(data);
			mapstr.insert(i + 1, data);
		}
	}
}

void frmDebug::dealData(const QString& data, const QString& title)
{
	if(ui->comboBox->currentText().contains(title))
	{
		recflag = 1;
	}
}

void frmDebug::sendDatacycle()
{
	switch(cycleflag)
	{
	case CYCLEONCEREC:                          //有接受才发，全部发完后停止
		if(recflag == 0)
		{
			break;
		}
	case CYCLEONCE:                             //全部发完后停止
		if(lstindex < dataList.size())
		{
			emitsignals(dataList.at(lstindex));
			lstindex++;
		}
		else
		{
			lstindex = 0;
			if(timercycle->isActive())
			{
				timercycle->stop();
			}
		}
		break;
	case CYCLEREC:                          //有接受才发，循环不停止
		if(recflag == 0)
		{
			break;
		}
	case CYCLE:                         //循环不停止
		if(lstindex >= dataList.size())
		{
			lstindex = 0;
		}
		emitsignals(dataList.at(lstindex));
		lstindex++;
		break;
	default:
		break;

	}
	recflag = 0;
}

void frmDebug::emitsignals(const QString& data)
{
	if(ui->comboBox->currentText().contains("TCP客户端"))
	{
		emit ToTcpClient(data);
	}
	else if(ui->comboBox->currentText().contains("TCP服务器"))
	{
		emit ToTcpServer(data);
	}
	else if(ui->comboBox->currentText().contains("UDP客户端"))
	{
		emit ToUdpClient(data);
	}
	else if(ui->comboBox->currentText().contains("UDP服务器"))
	{
		emit ToUdpServer(data);
	}
	else if(ui->comboBox->currentText().contains("COM串口"))
	{
		emit ToCom(data);
	}

	for(int i = 0; i < mapstr.size(); i++)
	{
		if(mapstr[i + 1] == data)
		{
			mapline[i + 1]->setStyleSheet("background-color:rgba(0,255,255,255);color:rgba(0,0,0,255)");
		}
		else
		{
			mapline[i + 1]->setStyleSheet("background-color:rgba(255,255,255,255);color:rgba(0,0,0,255)");
		}
	}
}

void frmDebug::stopTimer()
{
	if(timercycle->isActive())
	{
		timercycle->stop();
	}
	if(ui->btnSendcycle->text().indexOf("停止轮询") > -1)
	{
		ui->btnSendcycle->setText("开始轮询");
	}
}

void frmDebug::on_btnSendAll_clicked()
{
	stopTimer();

	initdataList();
	if(dataList.size() > 0)
	{
		if(ui->Cb_recv->isChecked())
		{
			cycleflag = CYCLEONCEREC;
		}
		else
		{
			cycleflag = CYCLEONCE;
		}
		//        recflag = 1;       //第一次发送不判是否收到报文，强制发送
		if(!timercycle->isActive())
		{
			timercycle->start(ui->timeinterval->text().toUInt());
		}
	}
}

void frmDebug::on_btnSendcycle_clicked()
{
	if(timercycle->isActive())
	{
		timercycle->stop();
	}
	if(ui->btnSendcycle->text().indexOf("开始轮询") > -1)
	{
		initdataList();
		if(dataList.size() > 0)
		{
			if(ui->Cb_recv->isChecked())
			{
				cycleflag = CYCLEREC;
			}
			else
			{
				cycleflag = CYCLE;
			}
			//        recflag = 1;       //第一次发送不判是否收到报文，强制发送
			ui->btnSendcycle->setText("停止轮询");
			if(!timercycle->isActive())
			{
				timercycle->start(ui->timeinterval->text().toUInt());
			}
		}
	}
	else
	{
		ui->btnSendcycle->setText("开始轮询");
	}
}

void frmDebug::on_comboBox_currentIndexChanged(const QString& arg1)
{
	stopTimer();
}

void frmDebug::on_timeinterval_textChanged(const QString& arg1)
{
	stopTimer();
}

void frmDebug::on_Cb_recv_stateChanged(int arg1)
{
	stopTimer();
}

void frmDebug::on_checkBox_stateChanged(int arg1)
{
	for(int i = 0; i < mapchk.size(); i++)
	{
		mapchk[i + 1]->setCheckState(Qt::CheckState(arg1));
	}
}

void frmDebug::on_pushButton_load_clicked()
{
	QString fileDir = QFileDialog::getOpenFileName(this, tr("打开对话框"), "", tr("文本文件(*ini *txt)"));

	QFile file(fileDir);
	if(file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text))
	{
		stopTimer();
		dataList.clear();
		while(!file.atEnd())
		{
			QString line = file.readLine();
			line = line.trimmed();
			line = line.replace("\r", "");
			line = line.replace("\n", "");
			if(!line.isEmpty())
			{
				dataList.append(line);
			}
		}

		file.close();
	}
	for(int i = 0; i < dataList.size() && i < mapline.size(); i++)
	{
		mapline[i + 1]->setText(dataList.at(i));
	}
}

void frmDebug::on_pushButton_clearAll_clicked()
{
	int ret = QMessageBox::question(this, tr("对话框"), tr("确认清空报文吗？"), QMessageBox::Yes, QMessageBox::No);
	if(ret == QMessageBox::No)
	{
		return;
	}

	for(int i = 0; i < mapline.size(); i++)
	{
		mapline[i + 1]->clear();
		mapline[i + 1]->setStyleSheet("background-color:rgba(255,255,255,255);color:rgba(0,0,0,255)");
	}
	stopTimer();
}

void frmDebug::on_btnopenfile_clicked()
{
	QString fileDir = QFileDialog::getOpenFileName(this, tr("打开对话框"), "", "");
	if(fileDir.isEmpty())
	{
		return;
	}

	QFile file(fileDir);
	if(file.open(QFile::ReadOnly | QIODevice::Text))
	{
		ui->linefiledir->setText(fileDir);
		file.close();
	}
}

void frmDebug::on_btnsendfile_clicked()
{
	QFile file(ui->linefiledir->text());
	if(file.open(QFile::ReadOnly | QIODevice::Text))
	{
		while(!file.atEnd())
		{
			QString str = file.readAll().toHex();
			emitsignals(str);
		}
		file.close();
	}
	/*
	 * 以下代码为测试读取不同编码方式的文件报文
		QFile data(ui->linefiledir->text());
		if(data.open(QFile::ReadOnly | QIODevice::Text))
		{
			QTextStream in(&data);
			in.setCodec("GB18030");
			while(!in.atEnd())
			{
				QString line = in.readLine();
				qDebug() << line;
			}
			data.close();
		}
	 */
}

void frmDebug::on_pushButton_send1_clicked()
{
	QString data = ui->linedata1->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void frmDebug::on_pushButton_send2_clicked()
{
	QString data = ui->linedata2->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void frmDebug::on_pushButton_send3_clicked()
{
	QString data = ui->linedata3->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void frmDebug::on_pushButton_send4_clicked()
{
	QString data = ui->linedata4->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void frmDebug::on_pushButton_send5_clicked()
{
	QString data = ui->linedata5->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void frmDebug::on_pushButton_send6_clicked()
{
	QString data = ui->linedata6->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

