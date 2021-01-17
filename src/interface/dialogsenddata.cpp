#include "dialogsenddata.h"
#include "ui_dialogsenddata.h"
#include "quiwidget.h"
#include "globaldefine.h"

DialogSendData::DialogSendData(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogSendData)
{
	ui->setupUi(this);
	initfrom();
//	piec104 = NULL;
}

DialogSendData::~DialogSendData()
{
	delete ui;
//	if(piec104)
//	{
//		delete piec104;
//		piec104 = NULL;
//	}
}

void DialogSendData::initfrom()
{
	timercycle = new QTimer(this);
//	handleDataTimer = new QTimer(this);
	recflag = 0;
//	haveData = false;

	connect(timercycle, SIGNAL(timeout()), this, SLOT(sendDatacycle()));
//	connect(handleDataTimer, SIGNAL(timeout()), this, SLOT(handleData()));
	ui->comboBox->addItems(App::Transferlst);
	mapline.insert(1, ui->linedata1);
	mapline.insert(2, ui->linedata2);
	mapline.insert(3, ui->linedata3);
	mapline.insert(4, ui->linedata4);
	mapline.insert(5, ui->linedata5);
	mapline.insert(6, ui->linedata6);
	mapline.insert(7, ui->linedata7);
	mapline.insert(8, ui->linedata8);
	mapline.insert(9, ui->linedata9);
	mapline.insert(10, ui->linedata10);

	mapchk.insert(1, ui->checkBox1);
	mapchk.insert(2, ui->checkBox2);
	mapchk.insert(3, ui->checkBox3);
	mapchk.insert(4, ui->checkBox4);
	mapchk.insert(5, ui->checkBox5);
	mapchk.insert(6, ui->checkBox6);
	mapchk.insert(7, ui->checkBox7);
	mapchk.insert(8, ui->checkBox8);
	mapchk.insert(9, ui->checkBox9);
	mapchk.insert(10, ui->checkBox10);

}

void DialogSendData::initdataList()
{
	lstindex = 0;
	dataList.clear();

	QString data;
	mapstr.clear();
	for(int i = 0; i < mapline.size(); i++)
	{
		data = mapline[i + 1]->text();
		if(mapchk[i + 1]->isChecked() && !data.trimmed().isEmpty())
		{
			dataList.append(data);
			mapstr.insert(i + 1, data);
		}
	}
}

void DialogSendData::closeEvent(QCloseEvent *event)
{
	stopTimer();
	event->accept();
}

void DialogSendData::dealData(const QString& data, const QString& title)
{
	if(ui->comboBox->currentText().contains(title))
	{
		recflag = 1;
	}
}

void DialogSendData::sendDatacycle()
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

void DialogSendData::emitsignals(const QString& data)
{
	if(ui->comboBox->currentText().contains("TCP客户端"))
	{
		emit dlgTotcpclient(data);
	}
	else if(ui->comboBox->currentText().contains("TCP服务器"))
	{
		emit dlgTotcpserver(data);
	}
	else if(ui->comboBox->currentText().contains("UDP客户端"))
	{
		emit dlgToudpclient(data);
	}
	else if(ui->comboBox->currentText().contains("UDP服务器"))
	{
		emit dlgToudpserver(data);
	}
	else if(ui->comboBox->currentText().contains("COM串口"))
	{
		emit dlgTocom(data);
	}
	QPalette palette1;
	palette1.setColor(QPalette::Base, Qt::red);
	QPalette palette2;
	palette2.setColor(QPalette::Base, Qt::white);
	for(int i = 0; i < mapstr.size(); i++)
	{
		if(mapstr[i + 1] == data)
		{
			mapline[i + 1]->setPalette(palette1);

		}
		else
		{
			mapline[i + 1]->setPalette(palette2);
		}
	}
}

void DialogSendData::stopTimer()
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

void DialogSendData::on_btnSendAll_clicked()
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

void DialogSendData::on_btnSendcycle_clicked()
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

void DialogSendData::on_comboBox_currentIndexChanged(int index)
{
	stopTimer();
}

void DialogSendData::on_Cb_recv_stateChanged(int arg1)
{
	stopTimer();
}

void DialogSendData::on_timeinterval_textChanged(const QString& arg1)
{
	stopTimer();
}

void DialogSendData::on_checkBox_stateChanged(int arg1)
{
	for(int i = 0; i < mapchk.size(); i++)
	{
		mapchk[i + 1]->setCheckState(Qt::CheckState(arg1));
	}
}

void DialogSendData::on_pushButton_clicked()
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

void DialogSendData::on_pushButton_2_clicked()
{
	int ret = QMessageBox::question(this, tr("对话框"), tr("确认清空报文吗？"), QMessageBox::Yes, QMessageBox::No);
	if(ret == QMessageBox::No)
	{
		return;
	}
	QPalette palette2;
	palette2.setColor(QPalette::Base, Qt::white);

	for(int i = 0; i < mapline.size(); i++)
	{
		mapline[i + 1]->clear();
		mapline[i + 1]->setPalette(palette2);
	}
	stopTimer();
}

void DialogSendData::on_btnopenfile_clicked()
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

void DialogSendData::on_btnsendfile_clicked()
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
	//以下代码为测试读取不同编码方式的文件报文
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
	}
}



void DialogSendData::on_pushButton_send1_clicked()
{
	QString data = ui->linedata1->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send2_clicked()
{
	QString data = ui->linedata2->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send3_clicked()
{
	QString data = ui->linedata3->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send4_clicked()
{
	QString data = ui->linedata4->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send5_clicked()
{
	QString data = ui->linedata5->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send6_clicked()
{
	QString data = ui->linedata6->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send7_clicked()
{
	QString data = ui->linedata7->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send8_clicked()
{
	QString data = ui->linedata8->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send9_clicked()
{
	QString data = ui->linedata9->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}

void DialogSendData::on_pushButton_send10_clicked()
{
	QString data = ui->linedata10->text().trimmed();
	if(!data.isEmpty())
	{
		emitsignals(data);
	}
}
