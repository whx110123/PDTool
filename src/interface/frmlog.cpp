#include "frmlog.h"
#include "ui_frmlog.h"

#include <QAction>
#include <QMenu>

frmLog::frmLog(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmLog)
{
	ui->setupUi(this);

	ui->splitter_H->setStretchFactor(0, 1);
	ui->splitter_H->setStretchFactor(1, 2);
	ui->splitter_H->setStretchFactor(2, 4);

	ui->splitter_V->setStretchFactor(0, 1);
	ui->splitter_V->setStretchFactor(1, 3);

	popMenu = new QMenu(this);
	clearSeeds = new QAction(tr("清空列表"), this);
	popMenu->addAction(clearSeeds);
	connect(clearSeeds, &QAction::triggered, this, &frmLog::clearlist);
}

frmLog::~frmLog()
{
	delete ui;
}

void frmLog::handleLog(const MyLog& log)
{
	QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
	QString text;
	switch(log.type)
	{
	case MyLog::SENDDATA:
		item->setForeground(QColor("darkgreen"));
		text.append(QString("[发送报文][%1]").arg(log.dt.toString("yyyy-MM-dd hh:mm:ss.zzz")));
		break;
	case MyLog::RECVDATA:
		item->setForeground(QColor("red"));
		text.append(QString("[接收报文][%1]").arg(log.dt.toString("yyyy-MM-dd hh:mm:ss.zzz")));
		break;
	case MyLog::ERRORLOG:
		item->setForeground(QColor("Magenta"));
		text.append(QString("[错误报告][%1]").arg(log.dt.toString("yyyy-MM-dd hh:mm:ss.zzz")));
		break;
	default:
		break;
	}
	item->setText(text);

	QVariant var;
	var.setValue(log);
	item->setData(0xff, var);
}

void frmLog::clearlist()
{
	if(ui->listWidget->count() > 0)
	{
		ui->listWidget->reset();
		ui->listWidget->clear();
	}
	ui->textEdit_attr->clear();
	ui->textEdit_content->clear();
}

void frmLog::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
	QVariant var = current->data(0xff);
	MyLog log = var.value<MyLog>();
	ui->textEdit_content->setText(log.text);

	ui->textEdit_attr->clear();
	ui->textEdit_attr->append(masterTypeToText(log.masterType));
	ui->textEdit_attr->append(log.text_s);
}

void frmLog::on_listWidget_customContextMenuRequested(const QPoint&)
{
	popMenu->exec(QCursor::pos());
}
