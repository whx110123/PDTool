#include "dialogpma.h"
#include "ui_dialogpma.h"

#include <iec101asdu45data.h>
#include <iec101asdu46data.h>
#include <quiwidget.h>

DialogPMA::DialogPMA(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogPMA)
{
	ui->setupUi(this);
	mProtocol = NULL;
	mProtocolShow = NULL;
	init();
}

DialogPMA::~DialogPMA()
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

void DialogPMA::dealData(const QString& data, const QString& title)
{
	if(ui->comboBox_connect->currentText().contains(title))
	{
		if(ui->pushButton_start->text() == QString("停止"))
		{
			recvData.append(QUIHelper::hexStrToByteArray(data));
		}
	}
}

bool DialogPMA::createAndSendData(IECDataConfig& config)
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

void DialogPMA::init()
{
	handleDataTimer = new QTimer(this);
	haveData = false;
	connect(handleDataTimer, SIGNAL(timeout()), this, SLOT(handleData()));
	ui->comboBox_cotlen->setCurrentText("2");
	ui->comboBox_comaddrlen->setCurrentText("2");
	ui->comboBox_infaddrlen->setCurrentText("3");
}

void DialogPMA::handleData()
{
	if(!mProtocol)
	{
		return;
	}
	while(!recvData.isEmpty())
	{
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
	if(haveData || (ui->comboBox_state->currentText() == QString("模拟主站") && mProtocol->masterState == STATE_INIT))
	{
		haveData = false;
		config.asdutype = 0;
		if(ui->comboBox_state->currentText() == QString("模拟主站"))
		{
			config.isMaster = true;
			config.masterState = mProtocol->masterState;
		}
		else
		{
			config.isMaster = false;
			config.slaveState = mProtocol->slaveState;
		}
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

void DialogPMA::startdebug()
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
	if(ui->comboBox_protocol->currentText() == QString("104"))
	{
		MyBase::mConfig.lengthType = IEC_SINGLE;
		MyBase::mConfig.cotlen = ui->comboBox_cotlen->currentText().toInt();
		MyBase::mConfig.comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
		MyBase::mConfig.infaddrlen = ui->comboBox_infaddrlen->currentText().toInt();

		mProtocol = new IEC104;
		mProtocol->masterState = STATE_INIT;
		mProtocol->slaveState = STATE_NODATA;

		mProtocolShow = new IEC104;

		config.comaddr = ui->lineEdit_104asduaddr->text().toUInt();
		handleDataTimer->start(1000);
	}
}

void DialogPMA::stopdebug()
{
	if(handleDataTimer->isActive())
	{
		handleDataTimer->stop();
	}
	ui->pushButton_start->setText("开始");
	recvData.clear();
}

void DialogPMA::showToText(QByteArray ba)
{
	if(!mProtocolShow)
	{
		return;
	}
	while(!ba.isEmpty())
	{
		if(!mProtocolShow->init(ba))
		{
			ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			ui->textEdit_data->append("收到未识别的报文: " + mProtocolShow->mRecvData.toHex(' '));
			ui->textEdit_data->append("错误描述：" + mProtocolShow->error);
			ba.clear();
		}
		else
		{
			if(ui->pushButton_reflash->text().contains("暂停刷新"))
			{
				ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
				ui->textEdit_data->append(mProtocolShow->showToText());
			}
			if(ui->comboBox_protocol->currentText() == QString("104"))
			{
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
			}
			ba.remove(0, mProtocolShow->len);
		}
	}
}

void DialogPMA::emitsignals(const QString& data)
{
	if(ui->comboBox_connect->currentText().contains("TCP客户端"))
	{
		emit dlgTotcpclient(data);
	}
	else if(ui->comboBox_connect->currentText().contains("TCP服务器"))
	{
		emit dlgTotcpserver(data);
	}
	else if(ui->comboBox_connect->currentText().contains("UDP客户端"))
	{
		emit dlgToudpclient(data);
	}
	else if(ui->comboBox_connect->currentText().contains("UDP服务器"))
	{
		emit dlgToudpserver(data);
	}
	else if(ui->comboBox_connect->currentText().contains("COM串口"))
	{
		emit dlgTocom(data);
	}
}

QByteArray DialogPMA::getYKYTData(uchar type)
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

void DialogPMA::on_pushButton_start_clicked()
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

void DialogPMA::on_pushButton_sendasdu_clicked()
{
	config.userdata = QUIHelper::hexStrToByteArray(ui->textEdit_104asdu->toPlainText());
	if(ui->comboBox_state->currentText() == QString("模拟主站"))
	{
		config.masterState = STATE_USER;
		config.isMaster = true;
	}
	else
	{
		config.isMaster = false;
		config.slaveState = STATE_USER;
	}
	config.asdutype = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callTitle_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf0;
	config.iec103config->rii = 0;
	config.iec103config->nog = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callRange_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 3;
	createAndSendData(config);

}

void DialogPMA::on_pushButton_104callDescription_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 0x0a;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callAccuracy_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 5;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callDimension_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 9;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callSetting_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 1;
	createAndSendData(config);
}


void DialogPMA::on_pushButton_104setFloatDowm_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x0a;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x28;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf9;
	config.iec103config->rii = 0;
	config.iec103config->ngd = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = ui->lineEdit_104setInf->text().toUShort();
	config.iec103config->kod[0] = 1;
	config.iec103config->gdd[0][0] = 7;
	config.iec103config->gdd[0][1] = 4;
	config.iec103config->gdd[0][2] = 1;
	float tmp = ui->lineEdit_104setValueFloat->text().toFloat();
	memcpy(config.iec103config->gid, &tmp, 4);
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104settingCuring_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x0a;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x28;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xfa;
	config.iec103config->rii = 0;
	config.iec103config->ngd = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104setUintDowm_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x0a;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x28;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf9;
	config.iec103config->rii = 0;
	config.iec103config->ngd = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = ui->lineEdit_104setInf->text().toUShort();
	config.iec103config->kod[0] = 1;
	config.iec103config->gdd[0][0] = 3;
	config.iec103config->gdd[0][1] = 4;
	config.iec103config->gdd[0][2] = 1;
	uint tmp = ui->lineEdit_104setValueUint->text().toUInt();
	memcpy(config.iec103config->gid, &tmp, 4);
	createAndSendData(config);
}



void DialogPMA::on_pushButton_clear_clicked()
{
	ui->textEdit_data->clear();
}

void DialogPMA::on_pushButton_104select_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	config.controltype = ITYPE;
	config.vsq = 1;
	config.cot = 6;
	if(ui->checkBox_104isHex->isChecked())
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt(0, 16);
	}
	else
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt();
	}
	config.infdata = getYKYTData(0x80);
	createAndSendData(config);

	ui->label_select->setText("");
	ui->label_execute->setText("");
	ui->pushButton_104execute->setEnabled(false);
}

void DialogPMA::on_pushButton_104execute_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	config.controltype = ITYPE;
	config.vsq = 1;
	config.cot = 6;
	if(ui->checkBox_104isHex->isChecked())
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt(0, 16);
	}
	else
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt();
	}
	config.infdata = getYKYTData('\0');
	createAndSendData(config);

	ui->label_select->setText("");
	ui->label_execute->setText("");
}

void DialogPMA::on_pushButton_104cancel_clicked()
{
	config.masterState = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	config.controltype = ITYPE;
	config.vsq = 1;
	config.cot = 8;
	if(ui->checkBox_104isHex->isChecked())
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt(0, 16);
	}
	else
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt();
	}
	config.infdata = getYKYTData('\0');
	createAndSendData(config);

	ui->pushButton_104execute->setEnabled(true);
	ui->label_select->setText("");
	ui->label_execute->setText("");
}

void DialogPMA::on_checkBox_104isHex_stateChanged(int arg1)
{
	uint ss = ui->lineEdit_104infaddr->text().toUInt(0, arg1 ? 10 : 16);
	ui->lineEdit_104infaddr->setText(QString::number(ss, arg1 ? 16 : 10));
}

void DialogPMA::on_pushButton_reflash_clicked()
{
	if(ui->pushButton_reflash->text().contains("暂停刷新"))
	{
		ui->pushButton_reflash->setText("正常刷新");
	}
	else
	{
		ui->pushButton_reflash->setText("暂停刷新");
	}
}

void DialogPMA::on_pushButton_104sendUstart_clicked()
{
	config.masterState = STATE_INIT;
	config.isMaster = true;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104sendS_clicked()
{
	config.masterState = STATE_NORMAL;
	config.isMaster = true;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104sendUtest_clicked()
{
	config.masterState = STATE_TESTACT;
	config.isMaster = true;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callall_clicked()
{
	config.masterState = STATE_CALLALL;
	config.isMaster = true;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104setTime_clicked()
{
	config.masterState = STATE_SETTIME;
	config.isMaster = true;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_sendasdu_2_clicked()
{
	config.userdata = QUIHelper::hexStrToByteArray(ui->textEdit_104asdu_2->toPlainText());
	if(ui->comboBox_state->currentText() == QString("模拟主站"))
	{
		config.masterState = STATE_USER;
		config.isMaster = true;
	}
	else
	{
		config.isMaster = false;
		config.slaveState = STATE_USER;
	}
	config.asdutype = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_sendasdu_3_clicked()
{
	config.userdata = QUIHelper::hexStrToByteArray(ui->textEdit_104asdu_3->toPlainText());
	if(ui->comboBox_state->currentText() == QString("模拟主站"))
	{
		config.masterState = STATE_USER;
		config.isMaster = true;
	}
	else
	{
		config.isMaster = false;
		config.slaveState = STATE_USER;
	}
	config.asdutype = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_sendasdu_4_clicked()
{
	config.userdata = QUIHelper::hexStrToByteArray(ui->textEdit_104asdu_4->toPlainText());
	if(ui->comboBox_state->currentText() == QString("模拟主站"))
	{
		config.masterState = STATE_USER;
		config.isMaster = true;
	}
	else
	{
		config.isMaster = false;
		config.slaveState = STATE_USER;
	}
	config.asdutype = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_sendasdu_5_clicked()
{
	config.userdata = QUIHelper::hexStrToByteArray(ui->textEdit_104asdu_5->toPlainText());
	if(ui->comboBox_state->currentText() == QString("模拟主站"))
	{
		config.masterState = STATE_USER;
		config.isMaster = true;
	}
	else
	{
		config.isMaster = false;
		config.slaveState = STATE_USER;
	}
	config.asdutype = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_sendasdu_6_clicked()
{
	config.userdata = QUIHelper::hexStrToByteArray(ui->textEdit_104asdu_6->toPlainText());
	if(ui->comboBox_state->currentText() == QString("模拟主站"))
	{
		config.masterState = STATE_USER;
		config.isMaster = true;
	}
	else
	{
		config.isMaster = false;
		config.slaveState = STATE_USER;
	}
	config.asdutype = 0;
	createAndSendData(config);
}

