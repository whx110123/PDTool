#include "frmiec104master.h"
#include "ui_frmiec104master.h"

#include <app.h>
#include <iec101asdu100data.h>
#include <iec101asdu167data.h>
#include <iec101asdu45data.h>
#include <iec101asdu46data.h>
#include <iec101asdu47data.h>
#include <iec101asdu48data.h>
#include <iec101asdu49data.h>
#include <iec101asdu50data.h>
#include <iec101asdu58data.h>
#include <iec101asdu59data.h>
#include <iec103asdu21data.h>
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
	ui->lineEdit_YTValue->hide();
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

	myngd = 0;
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

IEC101AsduData *frmIEC104Master::getYKYTData(uchar type)
{
	IEC101AsduData *asduData = NULL;
	uchar asdutype = ui->comboBox_RemoteType->currentText().split(" ").at(0).toUShort();
	switch(asdutype)
	{
	case 45:
	{
		IEC101Asdu45Data *tmp = new IEC101Asdu45Data(config);
		tmp->sco = (ui->comboBox_YKValue->currentText().contains("合") ? 0x01 : 0x00) | (type & 0x80);
		asduData = tmp;
		break;
	}
	case 46:
	{
		IEC101Asdu46Data *tmp = new IEC101Asdu46Data(config);
		tmp->dco = (ui->comboBox_YKValue->currentText().contains("合") ? 0x02 : 0x01) | (type & 0x80);
		asduData = tmp;
		break;
	}
	case 47:
	{
		IEC101Asdu47Data *tmp = new IEC101Asdu47Data(config);
		tmp->rco = (ui->comboBox_YKValue->currentText().contains("合") ? 0x02 : 0x01) | (type & 0x80);
		asduData = tmp;
		break;
	}
	case 48:
	{
		IEC101Asdu48Data *tmp = new IEC101Asdu48Data(config);
		tmp->shortdata = ui->lineEdit_YTValue->text().toShort();
		tmp->qos = type & 0x80;
		asduData = tmp;
		break;
	}
	case 49:
	{
		IEC101Asdu49Data *tmp = new IEC101Asdu49Data(config);
		tmp->shortdata = ui->lineEdit_YTValue->text().toShort();
		tmp->qos = type & 0x80;
		asduData = tmp;
		break;
	}
	case 50:
	{
		IEC101Asdu50Data *tmp = new IEC101Asdu50Data(config);
		tmp->floatdata = ui->lineEdit_YTValue->text().toFloat();
		tmp->qos = type & 0x80;
		asduData = tmp;
		break;
	}
	case 58:
	{
		IEC101Asdu58Data *tmp = new IEC101Asdu58Data(config);
		tmp->sco = (ui->comboBox_YKValue->currentText().contains("合") ? 0x01 : 0x00) | (type & 0x80);
		tmp->datetime = QDateTime::currentDateTime();
		asduData = tmp;
		break;
	}
	case 59:
	{
		IEC101Asdu59Data *tmp = new IEC101Asdu59Data(config);
		tmp->dco = (ui->comboBox_YKValue->currentText().contains("合") ? 0x02 : 0x01) | (type & 0x80);
		tmp->datetime = QDateTime::currentDateTime();
		asduData = tmp;
		break;
	}
	default:
		break;
	}
	return asduData;
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
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0x15;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x2a;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu21Data *asdudata103 = new IEC103Asdu21Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xf0;
	asdudata103->rii = 0x00;

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_CallUnit_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0x15;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x2a;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu21Data *asdudata103 = new IEC103Asdu21Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xf1;
	asdudata103->rii = 0x00;
	IEC103Asdu21DataSet *set = new IEC103Asdu21DataSet(config);
	asdudata103->setlist.append(set);
	set->gin[0] = ui->lineEdit_SetGroup->text().toUShort();
	set->gin[1] = ui->lineEdit_SetEntry->text().toUShort();
	set->kod = 0x09;

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_CallAccuracy_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0x15;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x2a;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu21Data *asdudata103 = new IEC103Asdu21Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xf1;
	asdudata103->rii = 0x00;
	IEC103Asdu21DataSet *set = new IEC103Asdu21DataSet(config);
	asdudata103->setlist.append(set);
	set->gin[0] = ui->lineEdit_SetGroup->text().toUShort();
	set->gin[1] = ui->lineEdit_SetEntry->text().toUShort();
	set->kod = 0x05;

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_CallRange_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0x15;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x2a;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu21Data *asdudata103 = new IEC103Asdu21Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xf1;
	asdudata103->rii = 0x00;
	IEC103Asdu21DataSet *set = new IEC103Asdu21DataSet(config);
	asdudata103->setlist.append(set);
	set->gin[0] = ui->lineEdit_SetGroup->text().toUShort();
	set->gin[1] = ui->lineEdit_SetEntry->text().toUShort();
	set->kod = 0x03;

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_CallDescription_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0x15;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x2a;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu21Data *asdudata103 = new IEC103Asdu21Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xf1;
	asdudata103->rii = 0x00;
	IEC103Asdu21DataSet *set = new IEC103Asdu21DataSet(config);
	asdudata103->setlist.append(set);
	set->gin[0] = ui->lineEdit_SetGroup->text().toUShort();
	set->gin[1] = ui->lineEdit_SetEntry->text().toUShort();
	set->kod = 0x0a;

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_SelectSetting_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0xa;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x28;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu10Data *asdudata103 = new IEC103Asdu10Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xfa;
	asdudata103->rii = 0x00;
	IEC103Asdu10DataSet *set = new IEC103Asdu10DataSet(config);
	asdudata103->setlist.append(set);
	set->gin[0] = ui->lineEdit_SetGroup->text().toUShort();
	set->gin[1] = ui->lineEdit_SetEntry->text().toUShort();
	set->kod = 0x01;
	set->mygdd.gdd[0] = 0x03;
	set->mygdd.gdd[1] = 0x01;
	set->mygdd.gdd[2] = 0x01;
	IEC103Asdu10DataSetGid *gid = new IEC103Asdu10DataSetGid(config);
	set->mygdd.gidlist.append(gid);
	gid->gid += ui->lineEdit_SetNo->text().toUShort() & 0xff;

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_CallSetting_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0x15;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x2a;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu21Data *asdudata103 = new IEC103Asdu21Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xf1;
	asdudata103->rii = 0x00;
	IEC103Asdu21DataSet *set = new IEC103Asdu21DataSet(config);
	asdudata103->setlist.append(set);
	set->gin[0] = ui->lineEdit_SetGroup->text().toUShort();
	set->gin[1] = ui->lineEdit_SetEntry->text().toUShort();
	set->kod = 0x01;

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_SetValue_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0xa;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x28;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu10Data *asdudata103 = new IEC103Asdu10Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xf9;
	asdudata103->rii = 0x00;
	asdudata103->ngd = 0;
	myngd = 0x40;
	IEC103Asdu10DataSet *set = new IEC103Asdu10DataSet(config);
	asdudata103->setlist.append(set);
	set->gin[0] = ui->lineEdit_SetGroup->text().toUShort();
	set->gin[1] = ui->lineEdit_SetEntry->text().toUShort();
	set->kod = 0x01;
	IEC103Asdu10DataSetGid *gid = new IEC103Asdu10DataSetGid(config);
	set->mygdd.gidlist.append(gid);
	QString valType = ui->comboBox_ValueType->currentText();
	if(valType == QString("FLOAT"))
	{
		set->mygdd.gdd[0] = 0x07;
		set->mygdd.gdd[1] = 0x04;
		set->mygdd.gdd[2] = 0x01;
		gid->gid += floatToBa(ui->lineEdit_SetValue->text().toFloat());
	}
	else if(valType == QString("INT8"))
	{
		set->mygdd.gdd[0] = 0x04;
		set->mygdd.gdd[1] = 0x01;
		set->mygdd.gdd[2] = 0x01;
		gid->gid += intToBa(ui->lineEdit_SetValue->text().toInt(), set->mygdd.gdd[1]);
	}
	else if(valType == QString("INT16"))
	{
		set->mygdd.gdd[0] = 0x04;
		set->mygdd.gdd[1] = 0x02;
		set->mygdd.gdd[2] = 0x01;
		gid->gid += intToBa(ui->lineEdit_SetValue->text().toInt(), set->mygdd.gdd[1]);
	}
	else if(valType == QString("INT32"))
	{
		set->mygdd.gdd[0] = 0x04;
		set->mygdd.gdd[1] = 0x04;
		set->mygdd.gdd[2] = 0x01;
		gid->gid += intToBa(ui->lineEdit_SetValue->text().toInt(), set->mygdd.gdd[1]);
	}
	else if(valType == QString("UINT8"))
	{
		set->mygdd.gdd[0] = 0x03;
		set->mygdd.gdd[1] = 0x01;
		set->mygdd.gdd[2] = 0x01;
		gid->gid += uintToBa(ui->lineEdit_SetValue->text().toUInt(), set->mygdd.gdd[1]);
	}
	else if(valType == QString("UINT16"))
	{
		set->mygdd.gdd[0] = 0x03;
		set->mygdd.gdd[1] = 0x02;
		set->mygdd.gdd[2] = 0x01;
		gid->gid += uintToBa(ui->lineEdit_SetValue->text().toUInt(), set->mygdd.gdd[1]);
	}
	else if(valType == QString("UINT32"))
	{
		set->mygdd.gdd[0] = 0x03;
		set->mygdd.gdd[1] = 0x04;
		set->mygdd.gdd[2] = 0x01;
		gid->gid += uintToBa(ui->lineEdit_SetValue->text().toUInt(), set->mygdd.gdd[1]);
	}
	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_solidify_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = 0xa7;
	asdu.vsq = 0;
	asdu.cot[0] = 5;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101Asdu167Data *asduData  = new IEC101Asdu167Data(config);
	asdu.datalist.append(asduData);

	asduData->ctrl = 0;
	asduData->devaddr[0] = ui->lineEdit_DevAddr->text().toUShort() & 0xff;
	asduData->devaddr[1] = (ui->lineEdit_DevAddr->text().toUShort() >> 8) & 0xff;

	asduData->asdu.mConfig.cotlen = 1;
	asduData->asdu.mConfig.comaddrlen = 1;
	asduData->asdu.type = 0xa;
	asduData->asdu.vsq = 0x81;
	asduData->asdu.cot = 0x28;
	asduData->asdu.commonaddr = 0x01;
	IEC103Asdu10Data *asdudata103 = new IEC103Asdu10Data(config);
	asduData->asdu.datalist.append(asdudata103);
	asdudata103->fun = 0xfe;
	asdudata103->inf = 0xfa;
	asdudata103->rii = 0x00;
	asdudata103->ngd = myngd;
	myngd = 0;
	asdu.createData(sendData);
	manager->SendI(sendData.data);
}



void frmIEC104Master::on_comboBox_RemoteType_currentIndexChanged(const QString& arg1)
{
	uchar asduType = arg1.split(" ").at(0).toUShort();
	switch(asduType)
	{
	case 45:
	case 46:
	case 47:
	case 58:
	case 59:
		ui->comboBox_YKValue->show();
		ui->lineEdit_YTValue->hide();
		break;
	case 48:
	case 49:
	case 50:
		ui->comboBox_YKValue->hide();
		ui->lineEdit_YTValue->show();
		break;
	default:
		ui->comboBox_YKValue->show();
		ui->lineEdit_YTValue->show();
		break;
	}

}

void frmIEC104Master::on_pushButton_Select_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = ui->comboBox_RemoteType->currentText().split(" ").at(0).toUShort();
	asdu.vsq = 1;
	asdu.cot[0] = 6;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101AsduData *asduData = getYKYTData(0x80);

	if(asduData)
	{
		if(ui->checkBox_isHex->isChecked())
		{
			asduData->infaddr = ui->lineEdit_InfAddr->text().toUInt(0, 16);
		}
		else
		{
			asduData->infaddr = ui->lineEdit_InfAddr->text().toUInt();
		}
		asdu.datalist.append(asduData);
	}

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_Execute_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = ui->comboBox_RemoteType->currentText().split(" ").at(0).toUShort();
	asdu.vsq = 1;
	asdu.cot[0] = 6;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101AsduData *asduData = getYKYTData(0x00);

	if(asduData)
	{
		if(ui->checkBox_isHex->isChecked())
		{
			asduData->infaddr = ui->lineEdit_InfAddr->text().toUInt(0, 16);
		}
		else
		{
			asduData->infaddr = ui->lineEdit_InfAddr->text().toUInt();
		}
		asdu.datalist.append(asduData);
	}

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}

void frmIEC104Master::on_pushButton_Cancel_clicked()
{
	if(!manager)
	{
		return;
	}
	MyData sendData;
	IEC101Asdu asdu(config);
	asdu.type = ui->comboBox_RemoteType->currentText().split(" ").at(0).toUShort();
	asdu.vsq = 1;
	asdu.cot[0] = 8;
	asdu.commonaddr = ui->lineEdit_comaddr->text().toUInt();

	IEC101AsduData *asduData = getYKYTData(0x00);

	if(asduData)
	{
		if(ui->checkBox_isHex->isChecked())
		{
			asduData->infaddr = ui->lineEdit_InfAddr->text().toUInt(0, 16);
		}
		else
		{
			asduData->infaddr = ui->lineEdit_InfAddr->text().toUInt();
		}
		asdu.datalist.append(asduData);
	}

	asdu.createData(sendData);
	manager->SendI(sendData.data);
}
