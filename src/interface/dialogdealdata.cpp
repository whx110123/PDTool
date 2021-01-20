#include "dialogdealdata.h"
#include "ui_dialogdealdata.h"
#include "quiwidget.h"
#include "globaldefine.h"

DialogDealData::DialogDealData(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogDealData)
{
	ui->setupUi(this);
	initfrom();
}

DialogDealData::~DialogDealData()
{
	delete ui;
}

void DialogDealData::initfrom()
{

}

void DialogDealData::on_pbcrc_clicked()
{


}

void DialogDealData::on_pbtransform_clicked()
{

}

void DialogDealData::on_Bt1_clicked()
{

}

void DialogDealData::on_Bt2_clicked()
{

}

void DialogDealData::on_Bt3_clicked()
{

}

void DialogDealData::on_Bt4_clicked()
{

}


void DialogDealData::on_Bt_clear_clicked()
{

}
