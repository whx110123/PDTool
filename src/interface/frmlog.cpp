﻿#include "frmlog.h"
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
		item->setForeground(QColor("gray"));
		text.append(QString("[其他报告][%1]").arg(log.dt.toString("yyyy-MM-dd hh:mm:ss.zzz")));
		break;
	}
	item->setText(text);

	QVariant var;
	var.setValue(log);
	item->setData(Qt::UserRole, var);
}

void frmLog::clearlist()
{
	if(ui->listWidget->count() > 0)
	{
		ui->listWidget->reset();
		ui->listWidget->clear();
	}
	ui->plainTextEdit_attr->clear();
	ui->plainTextEdit_content->clear();
}

void frmLog::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
	QVariant var = current->data(Qt::UserRole);
	MyLog log = var.value<MyLog>();
	ui->plainTextEdit_content->setPlainText(log.text);

	ui->plainTextEdit_attr->clear();
	ui->plainTextEdit_attr->appendPlainText(masterTypeToText(log.masterType));
	ui->plainTextEdit_attr->appendPlainText(log.text_s);
	if(log.type == MyLog::ERRORLOG)
	{
		ui->plainTextEdit_attr->appendPlainText(log.text_error);
	}
}

void frmLog::on_listWidget_customContextMenuRequested(const QPoint&)
{
	popMenu->exec(QCursor::pos());
}

void frmLog::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *)
{

	uchar type = MyLog::DEFAULT;
	if(current->text(0) == QString("全部"))
	{
		type = MyLog::ALLLOG;
	}
	else if(current->text(0) == QString("发送报文"))
	{
		type = MyLog::SENDDATA;
	}
	else if(current->text(0) == QString("接收报文"))
	{
		type = MyLog::RECVDATA;
	}
	else if(current->text(0) == QString("错误"))
	{
		type = MyLog::ERRORLOG;
	}
	int row = 0;
	while(row < (ui->listWidget->count()))
	{
		QListWidgetItem *item = ui->listWidget->item(row);
		QVariant var = item->data(Qt::UserRole);
		MyLog log = var.value<MyLog>();
		if(type == MyLog::ALLLOG || log.type == type)
		{
			item->setHidden(false);
		}
		else
		{
			item->setHidden(true);
		}
		row++;
	}
}
