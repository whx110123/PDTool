﻿#include "frmiec104master.h"
#include "ui_frmiec104master.h"

#include <app.h>
#include <iec101asdu100data.h>
#include <iec101asdu45data.h>
#include <iec101asdu46data.h>
#include <iec104.h>
#include <quiwidget.h>

frmIEC104Master::frmIEC104Master(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmIEC104Master)
{
	ui->setupUi(this);
	manager = NULL;
	init();
	initfrm();
}

frmIEC104Master::~frmIEC104Master()
{
	delete ui;
}

void frmIEC104Master::initfrm()
{
	ui->comboBox->addItems(App::Transferlst);
}

void frmIEC104Master::init()
{
	if(manager)
	{
		delete manager;
		manager = NULL;
	}

	initConfig();
	manager = new ManagerIEC104Master(config);
	manager->initConfig(&managerConfig);
	connect(manager, &ManagerIEC104Master::Send, this, &frmIEC104Master::sendData);
	connect(manager, &ManagerIEC104Master::toText, this, &frmIEC104Master::showToText);
	connect(manager, &ManagerIEC104Master::toLog, this, &frmIEC104Master::showLog);

}

void frmIEC104Master::initConfig()
{
	managerConfig.protocolName = IEC_104;
	managerConfig.isMaster = true;
	managerConfig.asduAddr = ui->lineEdit_comaddr->text().toUInt();

	config.protocolName = IEC_104;
	config.lengthType = IEC_SINGLE;
	config.cotlen = 2;
	config.comaddrlen = 2;
	config.infaddrlen = 3;
}

void frmIEC104Master::dealRcvData(const QString& data, const QString& title)
{
	if(ui->comboBox->currentText().contains(title))
	{
		if(ui->pushButton_Start->text() == QString("停止"))
		{
			if(manager)
			{
				manager->addRcvData(QUIHelper::hexStrToByteArray(data));
			}
		}
	}
}

void frmIEC104Master::sendData(const QByteArray& data)
{
	if(manager)
	{
		manager->protocolShow.init(data);
		showToText(manager->protocolShow.mRecvData.toHex(' ') + "\r\n" + manager->protocolShow.showToText(), 1);
	}
	emitsignals(data.toHex(' '));
}

void frmIEC104Master::startdebug()
{
	ui->pushButton_Start->setText("停止");

	init();

	if(manager)
	{
		manager->flag = STATE_INIT;
		manager->start();
	}
}

void frmIEC104Master::stopdebug()
{
	ui->pushButton_Start->setText("开始");

	if(manager)
	{
		manager->stop();
		delete manager;
		manager = NULL;
	}

}

void frmIEC104Master::showToText(const QString& data, int type) //type 0接收 1发送
{
	if(type == 1)
	{
		ui->textEdit_data->setTextColor(QColor("darkgreen"));
		ui->textEdit_data->append(QString("[发送报文][%1]").arg(DATETIME));
	}
	else
	{
		ui->textEdit_data->setTextColor(QColor("red"));
		ui->textEdit_data->append(QString("[接收报文][%1]").arg(DATETIME));
	}
	ui->textEdit_data->append(data);

}

void frmIEC104Master::showLog(const QString& data)
{
	ui->textEdit_data->setTextColor(QColor("Magenta"));
	ui->textEdit_data->append(QString("[%1]").arg(DATETIME));
	ui->textEdit_data->append(data);
}


void frmIEC104Master::emitsignals(const QString& data)
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
}

QByteArray frmIEC104Master::getYKYTData(uchar type)
{
	uchar asdutype = ui->comboBox_RemoteType->currentText().split(" ").at(0).toUShort();
	QByteArray tmp;
	ushort tmp_us = 0;
	short tmp_s = 0;
	float tmp_f = 0;
	QDateTime datetime = QDateTime::currentDateTime();
	switch(asdutype)
	{
	case 45:
	case 58:
		if(ui->comboBox_YKValue->currentText().contains("合"))
		{
			tmp += 0x01 | type;
		}
		else
		{
			tmp += type;
		}
		if(asdutype == 58)
		{
			tmp += dateTimeToBa(datetime, 7, BINARYTIME2A);
		}
		break;
	case 46:
	case 47:
	case 59:
		if(ui->comboBox_YKValue->currentText().contains("合"))
		{
			tmp += 0x02 | type;
		}
		else
		{
			tmp += 0x01 | type;
		}
		if(asdutype == 59)
		{
			tmp += dateTimeToBa(datetime, 7, BINARYTIME2A);
		}
		break;
	case 48:
	case 49:
		tmp_s = ui->lineEdit_YTValue->text().toShort();
		tmp_us = (ushort)tmp_s;
		tmp += tmp_us & 0xff;
		tmp += (tmp_us >> 8) & 0xff;
		tmp += type;
		break;
	case 50:
		tmp_f = ui->lineEdit_YTValue->text().toFloat();
		tmp += floatToBa(tmp_f);
		tmp += type;
		break;
	default:
		break;

	}
	return tmp;
}

void frmIEC104Master::on_pushButton_Start_clicked()
{
	if(ui->pushButton_Start->text() == QString("开始"))
	{
		startdebug();
	}
	else
	{
		stopdebug();
	}
}

void frmIEC104Master::on_pushButton_SendUStart_clicked()
{
	if(!manager)
	{
		return;
	}
	manager->SendU(0x07);
}

void frmIEC104Master::on_pushButton_SendUTest_clicked()
{
	if(!manager)
	{
		return;
	}
	manager->SendU(0x43);
}

void frmIEC104Master::on_pushButton_SendS_clicked()
{
	if(!manager)
	{
		return;
	}
	manager->SendS();
}

void frmIEC104Master::on_pushButton_CallAll_clicked()
{
	if(!manager)
	{
		return;
	}
	manager->SendI(manager->asdu100Create());

}

void frmIEC104Master::on_pushButton_SetTime_clicked()
{
	if(!manager)
	{
		return;
	}
	manager->SendI(manager->asdu103Create());
}

void frmIEC104Master::on_pushButton_CallTitle_clicked()
{

}

void frmIEC104Master::on_pushButton_CallDimension_clicked()
{

}

void frmIEC104Master::on_pushButton_CallAccuracy_clicked()
{

}

void frmIEC104Master::on_pushButton_CallRange_clicked()
{

}

void frmIEC104Master::on_pushButton_CallSetting_clicked()
{

}

void frmIEC104Master::on_pushButton_CallDescription_clicked()
{

}

void frmIEC104Master::on_pushButton_SetValue_clicked()
{

}

void frmIEC104Master::on_pushButton_solidify_clicked()
{

}
