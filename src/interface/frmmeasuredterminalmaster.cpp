#include "frmmeasuredterminalmaster.h"
#include "ui_frmmeasuredterminalmaster.h"

#include <app.h>

frmMeasuredTerminalMaster::frmMeasuredTerminalMaster(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmMeasuredTerminalMaster)
{
	ui->setupUi(this);
//	manager = NULL;
	init();
	initfrm();
}

frmMeasuredTerminalMaster::~frmMeasuredTerminalMaster()
{
	delete ui;
}

void frmMeasuredTerminalMaster::initfrm()
{
	ui->comboBox->addItems(App::Transferlst);
}

void frmMeasuredTerminalMaster::init()
{

}

void frmMeasuredTerminalMaster::initConfig()
{
	managerConfig.protocolName = IEC_104;
	managerConfig.isMaster = true;
	managerConfig.A1 = ui->lineEdit_A1->text().toUInt();
	managerConfig.A2 = ui->lineEdit_A2->text().toUInt();
	managerConfig.A3 = ui->lineEdit_A3->text().toUInt();

	myConfig.protocolName = MEASUREDTERMINAL_NW_NET;
	myConfig.lengthType = IEC_FOURDIFF;
	myConfig.addrLen = 7;
	myConfig.cotlen = 1;
	myConfig.comaddrlen = 1;
	myConfig.infaddrlen = 1;

}

void frmMeasuredTerminalMaster::dealRcvData(const QString& data, const QString& title)
{

}

void frmMeasuredTerminalMaster::sendData(const QByteArray& data)
{

}

void frmMeasuredTerminalMaster::startdebug()
{

}

void frmMeasuredTerminalMaster::stopdebug()
{

}

void frmMeasuredTerminalMaster::showToText(const QString& data, int type)
{

}

void frmMeasuredTerminalMaster::showLog(const QString& data)
{

}

void frmMeasuredTerminalMaster::emitsignals(const QString& data)
{

}
