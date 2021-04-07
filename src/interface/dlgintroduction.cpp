#include "dlgintroduction.h"
#include "ui_dlgintroduction.h"

DlgIntroduction::DlgIntroduction(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgIntroduction)
{
	ui->setupUi(this);
}

DlgIntroduction::~DlgIntroduction()
{
	delete ui;
}
