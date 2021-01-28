#include "frmiec104master.h"
#include "ui_frmiec104master.h"

#include <app.h>
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
	if(!manager)
	{
		MyBase::mConfig.lengthType = IEC_SINGLE;
		MyBase::mConfig.cotlen = 2;
		MyBase::mConfig.comaddrlen = 2;
		MyBase::mConfig.infaddrlen = 3;

		manager = new ManagerIEC104Master;
		connect(manager, &ManagerIEC104Master::Send, this, &frmIEC104Master::sendData);
		connect(manager, &ManagerIEC104Master::toText, this, &frmIEC104Master::showToText);
		connect(manager, &ManagerIEC104Master::toLog, this, &frmIEC104Master::showLog);
	}
}

void frmIEC104Master::dealData(const QString& data, const QString& title)
{
	if(ui->comboBox->currentText().contains(title))
	{
		if(ui->pushButton_start->text() == QString("停止"))
		{
			if(manager)
			{
				manager->addRcvData(QUIHelper::hexStrToByteArray(data));
			}
		}
	}
}

bool frmIEC104Master::createAndSendData(IECDataConfig& config)
{
	return false;
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
	ui->pushButton_start->setText("停止");

	config.comaddr = ui->lineEdit_comaddr->text().toUInt();
	if(manager)
	{
		manager->start();
	}
}

void frmIEC104Master::stopdebug()
{
	ui->pushButton_start->setText("开始");

	if(manager)
	{
		manager->stop();
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
//	if(!mProtocolShow)
//	{
//		return;
//	}
//	while(!ba.isEmpty())
//	{
//		MyBase::mConfig.protocolName = IEC_104;
//		if(!mProtocolShow->init(ba))
//		{
//			ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
//			ui->textEdit_data->append("收到未识别的报文: " + mProtocolShow->mRecvData.toHex(' '));
//			ui->textEdit_data->append("错误描述：" + mProtocolShow->error);
//			ba.clear();
//		}
//		else
//		{

//			ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
//			ui->textEdit_data->append(mProtocolShow->mTextS);
//			mProtocolShow->mTextS.clear();


//			IEC104 *tmp = (IEC104 *)mProtocolShow;
//			if(tmp->asdu.type == 45)
//			{
//				IEC101Asdu45Data *iec101data = (IEC101Asdu45Data *)tmp->asdu.datalist.at(0);
//				if(tmp->asdu.cot[0] == 7)
//				{
//					ui->pushButton_104execute->setEnabled(true);
//					if(iec101data->sco & 0x80)
//					{
//						ui->label_select->setText("选择成功");
//					}
//					else
//					{
//						ui->label_execute->setText("执行成功");
//					}
//				}
//				else if((tmp->asdu.cot[0] & 0x0f) == 7)
//				{
//					ui->pushButton_104execute->setEnabled(false);
//					if(iec101data->sco & 0x80)
//					{
//						ui->label_select->setText("选择失败");
//					}
//					else
//					{
//						ui->label_execute->setText("执行失败");
//					}
//				}
//			}
//			else if(tmp->asdu.type == 46)
//			{
//				IEC101Asdu46Data *iec101data = (IEC101Asdu46Data *)tmp->asdu.datalist.at(0);
//				if(tmp->asdu.cot[0] == 7)
//				{
//					ui->pushButton_104execute->setEnabled(true);
//					if(iec101data->dco & 0x80)
//					{
//						ui->label_select->setText("选择成功");
//					}
//					else
//					{
//						ui->label_execute->setText("执行成功");
//					}
//				}
//				else if((tmp->asdu.cot[0] & 0x0f) == 7)
//				{
//					ui->pushButton_104execute->setEnabled(false);
//					if(iec101data->dco & 0x80)
//					{
//						ui->label_select->setText("选择失败");
//					}
//					else
//					{
//						ui->label_execute->setText("执行失败");
//					}
//				}
//			}

//			ba.remove(0, mProtocolShow->len);
//		}
	//	}
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
	uchar asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	QByteArray tmp;
	ushort tmp_us = 0;
	short tmp_s = 0;
	float tmp_f = 0;
	QDateTime datetime = QDateTime::currentDateTime();
	switch(asdutype)
	{
	case 45:
	case 58:
		if(ui->comboBox_104YKvalue->currentText().contains("合"))
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
		if(ui->comboBox_104YKvalue->currentText().contains("合"))
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
		tmp_s = ui->lineEdit_104YTvalue->text().toShort();
		tmp_us = (ushort)tmp_s;
		tmp += tmp_us & 0xff;
		tmp += (tmp_us >> 8) & 0xff;
		tmp += type;
		break;
	case 50:
		tmp_f = ui->lineEdit_104YTvalue->text().toFloat();
		tmp += floatToBa(tmp_f);
		tmp += type;
		break;
	default:
		break;

	}
	return tmp;
}

void frmIEC104Master::on_pushButton_start_clicked()
{
	if(ui->pushButton_start->text() == QString("开始"))
	{
		startdebug();
	}
	else
	{
		stopdebug();
	}
}
