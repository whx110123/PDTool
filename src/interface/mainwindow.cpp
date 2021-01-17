#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRibbon.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
//	QRibbon::install(this);

}

MainWindow::~MainWindow()
{
	delete ui;
}

