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
	mProtocol = NULL;
	mProtocolShow = NULL;
	init();
	initfrm();
}

frmIEC104Master::~frmIEC104Master()
{
	delete ui;
	if(mProtocol)
	{
		delete mProtocol;
		mProtocol = NULL;
	}
	if(mProtocolShow)
	{
		delete mProtocolShow;
		mProtocolShow = NULL;
	}
}

void frmIEC104Master::initfrm()
{
	ui->comboBox->addItems(App::Transferlst);
}

void frmIEC104Master::init()
{
	manager = new ManagerIEC104Master;
	handleDataTimer = new QTimer(this);
	haveData = false;
	connect(handleDataTimer, &QTimer::timeout, this, &frmIEC104Master::handleData);
}

void frmIEC104Master::dealData(const QString& data, const QString& title)
{
	if(ui->comboBox->currentText().contains(title))
	{
		if(ui->pushButton_start->text() == QString("停止"))
		{
			recvData.append(QUIHelper::hexStrToByteArray(data));
		}
	}
}

bool frmIEC104Master::createAndSendData(IECDataConfig& config)
{
	if(ui->pushButton_start->text() == QString("停止") && mProtocol)
	{
		if(mProtocol->createData(config))
		{
			if(config.data.isEmpty())
			{
				return true;
			}
			emitsignals(config.data.toHex(' '));
			showToText(config.data);
			return true;
		}
		else
		{
			ui->textEdit_data->append("错误描述：" + mProtocol->error);
		}
	}
	return false;
}

void frmIEC104Master::handleData()
{
	if(!mProtocol)
	{
		return;
	}
	while(!recvData.isEmpty())
	{
		MyBase::mConfig.protocolName = IEC_104;
		if(!mProtocol->init(recvData))
		{
			ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			ui->textEdit_data->append("收到未识别的报文: " + mProtocol->mRecvData.toHex(' '));
			ui->textEdit_data->append("错误描述：" + mProtocol->error);
			recvData.clear();
			haveData = false;
		}
		else
		{
			haveData = true;
			showToText(recvData.left(mProtocol->len));
			recvData.remove(0, mProtocol->len);
		}
	}
	if(haveData ||  mProtocol->masterState == STATE_INIT)
	{
		haveData = false;
		config.asdutype = 0;
		config.isMaster = true;
		config.masterState = mProtocol->masterState;


		if(mProtocol->createData(config))
		{
			if(config.data.isEmpty())
			{
				return;
			}
			showToText(config.data);
			QString str = config.data.toHex(' ');
			emitsignals(str);
		}
		else
		{
			ui->textEdit_data->append("错误描述：" + mProtocol->error);
		}
	}
}

void frmIEC104Master::startdebug()
{
	recvData.clear();
	ui->pushButton_start->setText("停止");
	if(mProtocol)
	{
		delete mProtocol;
		mProtocol = NULL;
	}
	if(mProtocolShow)
	{
		delete mProtocolShow;
		mProtocolShow = NULL;
	}

	MyBase::mConfig.lengthType = IEC_SINGLE;
	MyBase::mConfig.cotlen = 2;
	MyBase::mConfig.comaddrlen = 2;
	MyBase::mConfig.infaddrlen = 3;

	mProtocol = new IEC104;
	mProtocol->masterState = STATE_INIT;
	mProtocol->slaveState = STATE_NODATA;

	mProtocolShow = new IEC104;

	config.comaddr = ui->lineEdit_comaddr->text().toUInt();
	if(handleDataTimer->isActive())
	{
		handleDataTimer->stop();
	}
	handleDataTimer->start(1000);

}

void frmIEC104Master::stopdebug()
{
	if(handleDataTimer->isActive())
	{
		handleDataTimer->stop();
	}
	ui->pushButton_start->setText("开始");
	recvData.clear();
}

void frmIEC104Master::showToText(QByteArray ba)
{
	if(!mProtocolShow)
	{
		return;
	}
	while(!ba.isEmpty())
	{
		MyBase::mConfig.protocolName = IEC_104;
		if(!mProtocolShow->init(ba))
		{
			ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			ui->textEdit_data->append("收到未识别的报文: " + mProtocolShow->mRecvData.toHex(' '));
			ui->textEdit_data->append("错误描述：" + mProtocolShow->error);
			ba.clear();
		}
		else
		{

			ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			ui->textEdit_data->append(mProtocolShow->mTextS);
			mProtocolShow->mTextS.clear();


			IEC104 *tmp = (IEC104 *)mProtocolShow;
			if(tmp->asdu.type == 45)
			{
				IEC101Asdu45Data *iec101data = (IEC101Asdu45Data *)tmp->asdu.datalist.at(0);
				if(tmp->asdu.cot[0] == 7)
				{
					ui->pushButton_104execute->setEnabled(true);
					if(iec101data->sco & 0x80)
					{
						ui->label_select->setText("选择成功");
					}
					else
					{
						ui->label_execute->setText("执行成功");
					}
				}
				else if((tmp->asdu.cot[0] & 0x0f) == 7)
				{
					ui->pushButton_104execute->setEnabled(false);
					if(iec101data->sco & 0x80)
					{
						ui->label_select->setText("选择失败");
					}
					else
					{
						ui->label_execute->setText("执行失败");
					}
				}
			}
			else if(tmp->asdu.type == 46)
			{
				IEC101Asdu46Data *iec101data = (IEC101Asdu46Data *)tmp->asdu.datalist.at(0);
				if(tmp->asdu.cot[0] == 7)
				{
					ui->pushButton_104execute->setEnabled(true);
					if(iec101data->dco & 0x80)
					{
						ui->label_select->setText("选择成功");
					}
					else
					{
						ui->label_execute->setText("执行成功");
					}
				}
				else if((tmp->asdu.cot[0] & 0x0f) == 7)
				{
					ui->pushButton_104execute->setEnabled(false);
					if(iec101data->dco & 0x80)
					{
						ui->label_select->setText("选择失败");
					}
					else
					{
						ui->label_execute->setText("执行失败");
					}
				}
			}

			ba.remove(0, mProtocolShow->len);
		}
	}
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
