#include "frmfunctions.h"
#include "ui_frmfunctions.h"


frmFunctions::frmFunctions(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmFunctions)
{
	ui->setupUi(this);
	m_dialogsenddata = new DialogSendData(this);
	m_dialogdealdata = new DialogDealData(this);
	m_dialogintroduction = new DialogIntroduction(this);
	m_dialogdebug = new DialogDebug(this);
	m_dialogpma = new DialogPMA(this);
	initfrom();
}

frmFunctions::~frmFunctions()
{
	delete ui;
}

void frmFunctions::on_pbfunc1_clicked()
{

	m_dialogsenddata->show();
}

void frmFunctions::initfrom()
{

}

void frmFunctions::on_pbfunc2_clicked()
{
	m_dialogdealdata->show();
}

void frmFunctions::on_pbintro_clicked()
{
	m_dialogintroduction->exec();
}


void frmFunctions::on_pbfunc3_clicked()
{
	m_dialogdebug->show();
}

void frmFunctions::on_pbfunc4_clicked()
{
	m_dialogpma->show();
}
