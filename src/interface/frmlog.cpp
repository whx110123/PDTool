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

void frmLog::handleLog(const MyLog& log)
{
	QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
	item->setText(log.dt.toString("yyyy-MM-dd hh:mm:ss.zzz"));
	QVariant var;
	var.setValue(log);
	item->setData(0xff, var);
}

void frmLog::on_listWidget_itemActivated(QListWidgetItem *item)
{
//	QVariant var = item->data(0xff);
//	MyLog log = var.value<MyLog>();
//	ui->textEdit_content->setText(log.text);
}

void frmLog::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
	QVariant var = current->data(0xff);
	MyLog log = var.value<MyLog>();
	ui->textEdit_content->setText(log.text);
}
