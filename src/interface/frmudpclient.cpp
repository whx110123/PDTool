#include "frmudpclient.h"
#include "ui_frmudpclient.h"
#include "quiwidget.h"

#include <app.h>

frmUdpClient::frmUdpClient(QWidget *parent) : QWidget(parent), ui(new Ui::frmUdpClient)
{
	ui->setupUi(this);
	this->initForm();
	this->initConfig();
}

frmUdpClient::~frmUdpClient()
{
	delete ui;
}

void frmUdpClient::dealData(const QString& data)
{
	if(data.length() <= 0)
	{
		return;
	}

	sendData(App::UdpServerIP, App::UdpServerPort, data);
}

void frmUdpClient::initForm()
{
	udpSocket = new QUdpSocket(this);
	connect(udpSocket, &QUdpSocket::readyRead, this, &frmUdpClient::readData);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &frmUdpClient::on_btnSend_clicked);

	ui->cboxInterval->addItems(App::Intervals);
	ui->cboxData->addItems(App::Datas);
}

void frmUdpClient::initConfig()
{
	ui->ckHexSend->setChecked(App::HexSendUdpClient);
	connect(ui->ckHexSend, &QCheckBox::stateChanged, this, &frmUdpClient::saveConfig);

	ui->ckHexReceive->setChecked(App::HexReceiveUdpClient);
	connect(ui->ckHexReceive, &QCheckBox::stateChanged, this, &frmUdpClient::saveConfig);

	ui->ckAscii->setChecked(App::AsciiUdpClient);
	connect(ui->ckAscii, &QCheckBox::stateChanged, this, &frmUdpClient::saveConfig);

	ui->ckDebug->setChecked(App::DebugUdpClient);
	connect(ui->ckDebug, &QCheckBox::stateChanged, this, &frmUdpClient::saveConfig);

	ui->ckAutoSend->setChecked(App::AutoSendUdpClient);
	connect(ui->ckAutoSend, &QCheckBox::stateChanged, this, &frmUdpClient::saveConfig);

	ui->cboxInterval->setCurrentIndex(ui->cboxInterval->findText(QString::number(App::IntervalUdpClient)));
	connect(ui->cboxInterval, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &frmUdpClient::saveConfig);

	ui->txtServerIP->setText(App::UdpServerIP);
	connect(ui->txtServerIP, &QLineEdit::textChanged, this, &frmUdpClient::saveConfig);

	ui->txtServerPort->setText(QString::number(App::UdpServerPort));
	connect(ui->txtServerPort, &QLineEdit::textChanged, this, &frmUdpClient::saveConfig);

	this->changeTimer();
}

void frmUdpClient::saveConfig()
{
	App::HexSendUdpClient = ui->ckHexSend->isChecked();
	App::HexReceiveUdpClient = ui->ckHexReceive->isChecked();
	App::AsciiUdpClient = ui->ckAscii->isChecked();
	App::DebugUdpClient = ui->ckDebug->isChecked();
	App::AutoSendUdpClient = ui->ckAutoSend->isChecked();
	App::IntervalUdpClient = ui->cboxInterval->currentText().toInt();
	App::UdpServerIP = ui->txtServerIP->text().trimmed();
	App::UdpServerPort = ui->txtServerPort->text().trimmed().toInt();
	App::writeConfig();

	this->changeTimer();
}

void frmUdpClient::changeTimer()
{
	timer->setInterval(App::IntervalUdpClient);
	if(App::AutoSendUdpClient)
	{
		if(!timer->isActive())
		{
			timer->start();
		}
	}
	else
	{
		if(timer->isActive())
		{
			timer->stop();
		}
	}
}

void frmUdpClient::append(int type, const QString& data, bool clear)
{
	static int currentCount = 0;
	static int maxCount = 100;

	if(clear)
	{
		ui->txtMain->clear();
		currentCount = 0;
		return;
	}

	if(currentCount >= maxCount)
	{
		ui->txtMain->clear();
		currentCount = 0;
	}

	if(ui->ckShow->isChecked())
	{
		return;
	}

	//过滤回车换行符
	QString strData = data;
	strData = strData.replace("\r", "");
	strData = strData.replace("\n", "");

	//不同类型不同颜色显示
	QString strType;
	if(type == 0)
	{
		strType = "发送";
		ui->txtMain->setTextColor(QColor("darkgreen"));
	}
	else
	{
		strType = "接收";
		ui->txtMain->setTextColor(QColor("red"));
	}

	strData = QString("时间[%1] %2: %3").arg(TIMEMS).arg(strType).arg(strData);
	ui->txtMain->append(strData);
	currentCount++;
}

void frmUdpClient::readData()
{
	QHostAddress host;
	quint16 port;
	QByteArray data;
	QString buffer;

	while(udpSocket->hasPendingDatagrams())
	{
		data.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(data.data(), data.size(), &host, &port);

		if(App::HexReceiveUdpClient)
		{
			buffer = QUIHelper::byteArrayToHexStr(data);
		}
		else if(App::AsciiUdpClient)
		{
			buffer = QUIHelper::byteArrayToAsciiStr(data);
		}
		else
		{
			buffer = QString(data);
		}

		QString ip = host.toString();
		ip = ip.replace("::ffff:", "");
		if(ip.isEmpty())
		{
			continue;
		}

		QString str = QString("[%1:%2] %3").arg(ip).arg(port).arg(buffer);
		append(1, str);
		emit TofrmOthers(str, "UDP客户端");
		if(App::DebugUdpClient)
		{
			if(!App::m_map.isEmpty())
			{
				QStringList list = App::m_map.value(buffer, QStringList());
				for(int i = 0; i < list.length(); i++)
				{
					sendData(ip, port, list.at(i));
					if(i + 1 == list.length())
					{
						break;
					}
					QUIHelper::sleep(App::debugdelay);
				}
			}
			int count = App::Keys.count();
			for(int i = 0; i < count; i++)
			{
				if(App::Keys.at(i) == buffer)
				{
					sendData(ip, port, App::Values.at(i));
					break;
				}
			}
		}
	}
}

void frmUdpClient::sendData(const QString& ip, int port, const QString& data)
{
	QByteArray buffer;
	if(App::HexSendUdpClient)
	{
		buffer = QUIHelper::hexStrToByteArray(data);
	}
	else if(App::AsciiUdpClient)
	{
		buffer = QUIHelper::asciiStrToByteArray(data);
	}
	else
	{
		buffer = data.toLatin1();
	}

	udpSocket->writeDatagram(buffer, QHostAddress(ip), port);

	QString str = QString("[%1:%2] %3").arg(ip).arg(port).arg(data);
	append(0, str);
}

void frmUdpClient::on_btnSave_clicked()
{
	QString data = ui->txtMain->toPlainText();
	if(data.length() <= 0)
	{
		return;
	}

	QString fileName = QString("%1/%2.txt").arg(QUIHelper::appPath()).arg(STRDATETIME);
	QFile file(fileName);
	if(file.open(QFile::WriteOnly | QFile::Text))
	{
		file.write(data.toUtf8());
		file.close();
	}

	on_btnClear_clicked();
}

void frmUdpClient::on_btnClear_clicked()
{
	append(0, "", true);
}

void frmUdpClient::on_btnSend_clicked()
{
	QString data = ui->cboxData->currentText();
	dealData(data);

}
