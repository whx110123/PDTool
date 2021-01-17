#include "dialogintroduction.h"
#include "ui_dialogintroduction.h"

DialogIntroduction::DialogIntroduction(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogIntroduction)
{
	ui->setupUi(this);
}

DialogIntroduction::~DialogIntroduction()
{
	delete ui;
}
