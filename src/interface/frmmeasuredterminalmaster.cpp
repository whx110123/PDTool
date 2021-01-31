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

MyConfig frmMeasuredTerminalMaster::initConfig()
{
	MyConfig Config;
	Config.protocolName = MEASUREDTERMINAL_NW_NET;
	Config.lengthType = IEC_DOUBLEDIFF;
	Config.addrLen = 7;
	Config.cotlen = 1;
	Config.comaddrlen = 1;
	Config.infaddrlen = 1;
	return Config;
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
