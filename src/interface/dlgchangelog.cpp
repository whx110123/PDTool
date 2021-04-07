#include "dlgchangelog.h"
#include "ui_dlgchangelog.h"

DlgChangeLog::DlgChangeLog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgChangeLog)
{
	ui->setupUi(this);
}

DlgChangeLog::~DlgChangeLog()
{
	delete ui;
}
