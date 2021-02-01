#include "frmmeasuredterminalmaster.h"
#include "ui_frmmeasuredterminalmaster.h"

#include <app.h>
#include <quiwidget.h>

frmMeasuredTerminalMaster::frmMeasuredTerminalMaster(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmMeasuredTerminalMaster)
{
	ui->setupUi(this);
	manager = NULL;
	init();
	initfrm();
}

frmMeasuredTerminalMaster::~frmMeasuredTerminalMaster()
{
	delete ui;
}

void frmMeasuredTerminalMaster::initfrm()
{
	ui->comboBox->addItems(App::Transferlst);
}

void frmMeasuredTerminalMaster::init()
{
	if(manager)
	{
		delete manager;
		manager = NULL;
	}

	initConfig();
	manager = new ManagerMTMaster(myConfig);
	manager->initConfig(&managerConfig);
	connect(manager, &ManagerMTMaster::Send, this, &frmMeasuredTerminalMaster::sendData);
	connect(manager, &ManagerMTMaster::toText, this, &frmMeasuredTerminalMaster::showToText);
	connect(manager, &ManagerMTMaster::toLog, this, &frmMeasuredTerminalMaster::showLog);
}

void frmMeasuredTerminalMaster::initConfig()
{
	managerConfig.protocolName = MEASUREDTERMINAL_NW_NET;
	managerConfig.isMaster = true;
	managerConfig.A1 = ui->lineEdit_A1->text().toUInt();
	managerConfig.A2 = ui->lineEdit_A2->text().toUInt();
	managerConfig.A3 = ui->lineEdit_A3->text().toUInt();

	myConfig.protocolName = MEASUREDTERMINAL_NW_NET;
	myConfig.lengthType = IEC_FOURDIFF;
	myConfig.addrLen = 7;
	myConfig.cotlen = 1;
	myConfig.comaddrlen = 1;
	myConfig.infaddrlen = 1;

}

void frmMeasuredTerminalMaster::dealRcvData(const QString& data, const QString& title)
{
	if(ui->comboBox->currentText().contains(title))
	{
		if(ui->pushButton_startdebug->text() == QString("停止"))
		{
			if(manager)
			{
				manager->addRcvData(QUIHelper::hexStrToByteArray(data));
			}
		}
	}
}

void frmMeasuredTerminalMaster::sendData(const QByteArray& data)
{
	if(manager)
	{
		if(manager->protocolShow.init(data))
		{
			showToText(manager->protocolShow.mRecvData.toHex(' ') + "\r\n" + manager->protocolShow.showToText(), 1);
		}
		else
		{
			showLog(manager->protocolShow.mRecvData.toHex(' ') + "\r\n" + manager->protocolShow.error);
		}
	}
	emitsignals(data.toHex(' '));
}

void frmMeasuredTerminalMaster::startdebug()
{
	ui->pushButton_startdebug->setText("停止");

	init();

	if(manager)
	{
		manager->flag = STATE_INIT;
		manager->start();
	}
}

void frmMeasuredTerminalMaster::stopdebug()
{
	ui->pushButton_startdebug->setText("开始");

	if(manager)
	{
		manager->stop();
		delete manager;
		manager = NULL;
	}
}

void frmMeasuredTerminalMaster::showToText(const QString& data, int type)
{
	if(type == 1)
	{
		ui->textEdit_data->setTextColor(QColor("darkgreen"));
		ui->textEdit_data->append(QString("[发送报文][%1]").arg(DATETIME));
	}
	else
	{
		ui->textEdit_data->setTextColor(QColor("red"));
		ui->textEdit_data->append(QString("[接收报文][%1]").arg(DATETIME));
	}
	ui->textEdit_data->append(data);
	ui->textEdit_data->append("***********************************************");
}

void frmMeasuredTerminalMaster::showLog(const QString& data)
{
	ui->textEdit_data->setTextColor(QColor("Magenta"));
	ui->textEdit_data->append(QString("[%1]").arg(DATETIME));
	ui->textEdit_data->append(data);
	ui->textEdit_data->append("***********************************************");
}

void frmMeasuredTerminalMaster::emitsignals(const QString& data)
{
	if(ui->comboBox->currentText().contains("TCP客户端"))
	{
		emit ToTcpClient(data);
	}
	else if(ui->comboBox->currentText().contains("TCP服务器"))
	{
		emit ToTcpServer(data);
	}
	else if(ui->comboBox->currentText().contains("UDP客户端"))
	{
		emit ToUdpClient(data);
	}
	else if(ui->comboBox->currentText().contains("UDP服务器"))
	{
		emit ToUdpServer(data);
	}
	else if(ui->comboBox->currentText().contains("COM串口"))
	{
		emit ToCom(data);
	}
}

void frmMeasuredTerminalMaster::on_pushButton_startdebug_clicked()
{
	if(ui->pushButton_startdebug->text() == QString("开始"))
	{
		startdebug();
	}
	else
	{
		stopdebug();
	}
}

void frmMeasuredTerminalMaster::on_pushButton_MTstart_clicked()
{
	manager->addSndData(manager->afn2Create(0));
}

void frmMeasuredTerminalMaster::on_pushButton_MTread1_clicked()
{
	QByteArray ba;
	ba += 0x0c;
	ba += 0x60;
	ba += uintToBa(ui->lineEdit_MTDA->text().toUInt(NULL, 16), 2);
	ba += uintToBa(0x00010000, 4);
	manager->addSndData(ba);
}

void frmMeasuredTerminalMaster::on_pushButton_MTread2_clicked()
{
	QByteArray ba;
	ba += 0x0c;
	ba += 0x60;
	ba += uintToBa(ui->lineEdit_MTDA->text().toUInt(NULL, 16), 2);
	ba += uintToBa(0x00020000, 4);
	manager->addSndData(ba);
}

void frmMeasuredTerminalMaster::on_pushButton_MTreaddata_clicked()
{
	QByteArray ba;
	ba += 0x0c;
	ba += 0x60;
	ba += uintToBa(ui->lineEdit_MTDA->text().toUInt(NULL, 16), 2);
	ba += uintToBa(ui->lineEdit_MTDI->text().toUInt(NULL, 16), 4);
	manager->addSndData(ba);
}

void frmMeasuredTerminalMaster::on_pushButton_MTreadhisdata_clicked()
{
	QByteArray ba;
	ba += 0x0d;
	ba += 0x60;
	ba += uintToBa(ui->lineEdit_MTDA->text().toUInt(NULL, 16), 2);
	ba += uintToBa(ui->lineEdit_MTDI->text().toUInt(NULL, 16), 4);

	QByteArray tmp = QUIHelper::hexStrToByteArray(ui->lineEdit_MTTimeBegin->text());
	BaReverse(tmp);
	tmp.resize(6);
	ba += tmp;
	tmp = QUIHelper::hexStrToByteArray(ui->lineEdit_MTTimeEnd->text());
	BaReverse(tmp);
	tmp.resize(6);
	ba += tmp;

	ba += ui->lineEdit_MTm->text().toUShort() & 0xff;
	manager->addSndData(ba);
}
