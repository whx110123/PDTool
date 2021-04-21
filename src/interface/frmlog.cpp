#include "frmlog.h"
#include "ui_frmlog.h"

frmLog::frmLog(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmLog)
{
	ui->setupUi(this);
}

frmLog::~frmLog()
{
	delete ui;
}
