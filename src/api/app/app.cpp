#include "app.h"
#include "quiwidget.h"

QString App::ConfigFile = "config.ini";
QString App::SendFileName = "send.txt";
QString App::DeviceFileName = "device.txt";

int App::CurrentIndex = 0;

bool App::HexSendTcpClient = true;
bool App::HexReceiveTcpClient = true;
bool App::AsciiTcpClient = false;
bool App::DebugTcpClient = false;
bool App::AutoSendTcpClient = false;
int App::IntervalTcpClient = 1000;
QString App::TcpServerIP = "127.0.0.1";
int App::TcpServerPort = 6000;

bool App::HexSendTcpServer = true;
bool App::HexReceiveTcpServer = true;
bool App::AsciiTcpServer = false;
bool App::DebugTcpServer = false;
bool App::AutoSendTcpServer = false;
int App::IntervalTcpServer = 1000;
QString App::TcpListenIP = "127.0.0.1";
int App::TcpListenPort = 6000;
bool App::SelectAllTcpServer = true;

bool App::HexSendUdpClient = true;
bool App::HexReceiveUdpClient = true;
bool App::AsciiUdpClient = false;
bool App::DebugUdpClient = false;
bool App::AutoSendUdpClient = false;
int App::IntervalUdpClient = 1000;
QString App::UdpServerIP = "127.0.0.1";
int App::UdpServerPort = 6000;

bool App::HexSendUdpServer = true;
bool App::HexReceiveUdpServer = true;
bool App::AsciiUdpServer = false;
bool App::DebugUdpServer = false;
bool App::AutoSendUdpServer = false;
int App::IntervalUdpServer = 1000;
QString App::UdpListenIP = "127.0.0.1";
int App::UdpListenPort = 6000;
bool App::SelectAllUdpServer = true;

QString App::PortName = "COM1";
int App::BaudRate = 9600;
int App::DataBit = 8;
QString App::Parity = "无";
double App::StopBit = 1;

bool App::HexSend = true;
bool App::HexReceive = true;
bool App::Debug = false;
bool App::AutoClear = false;

bool App::AutoSend = false;
int App::SendInterval = 1000;
bool App::AutoSave = false;
int App::SaveInterval = 5000;

QString App::Mode = "Tcp_Client";
QString App::ServerIP = "127.0.0.1";
int App::ServerPort = 6000;
int App::ListenPort = 6000;
int App::SleepTime = 100;
bool App::AutoConnect = false;

QString App::DefaultProtocol = "104";

void App::readConfig()
{
	if(!checkConfig())
	{
		return;
	}

	QSettings set(App::ConfigFile, QSettings::IniFormat);

	set.beginGroup("AppConfig");
	App::CurrentIndex = set.value("CurrentIndex").toInt();
	set.endGroup();

	set.beginGroup("TcpClientConfig");
	App::HexSendTcpClient = set.value("HexSendTcpClient").toBool();
	App::HexReceiveTcpClient = set.value("HexReceiveTcpClient").toBool();
	App::AsciiTcpClient = set.value("AsciiTcpClient").toBool();
	App::DebugTcpClient = set.value("DebugTcpClient").toBool();
	App::AutoSendTcpClient = set.value("AutoSendTcpClient").toBool();
	App::IntervalTcpClient = set.value("IntervalTcpClient").toInt();
	App::TcpServerIP = set.value("TcpServerIP").toString();
	App::TcpServerPort = set.value("TcpServerPort").toInt();
	set.endGroup();

	set.beginGroup("TcpServerConfig");
	App::HexSendTcpServer = set.value("HexSendTcpServer").toBool();
	App::HexReceiveTcpServer = set.value("HexReceiveTcpServer").toBool();
	App::AsciiTcpServer = set.value("AsciiTcpServer").toBool();
	App::DebugTcpServer = set.value("DebugTcpServer").toBool();
	App::AutoSendTcpServer = set.value("AutoSendTcpServer").toBool();
	App::IntervalTcpServer = set.value("IntervalTcpServer").toInt();
	App::TcpListenIP = set.value("TcpListenIP").toString();
	App::TcpListenPort = set.value("TcpListenPort").toInt();
	App::SelectAllTcpServer = set.value("SelectAllTcpServer").toBool();
	set.endGroup();

	set.beginGroup("UdpClientConfig");
	App::HexSendUdpClient = set.value("HexSendUdpClient").toBool();
	App::HexReceiveUdpClient = set.value("HexReceiveUdpClient").toBool();
	App::AsciiUdpClient = set.value("AsciiUdpClient").toBool();
	App::DebugUdpClient = set.value("DebugUdpClient").toBool();
	App::AutoSendUdpClient = set.value("AutoSendUdpClient").toBool();
	App::IntervalUdpClient = set.value("IntervalUdpClient").toInt();
	App::UdpServerIP = set.value("UdpServerIP").toString();
	App::UdpServerPort = set.value("UdpServerPort").toInt();
	set.endGroup();

	set.beginGroup("UdpServerConfig");
	App::HexSendUdpServer = set.value("HexSendUdpServer").toBool();
	App::HexReceiveUdpServer = set.value("HexReceiveUdpServer").toBool();
	App::AsciiUdpServer = set.value("AsciiUdpServer").toBool();
	App::DebugUdpServer = set.value("DebugUdpServer").toBool();
	App::AutoSendUdpServer = set.value("AutoSendUdpServer").toBool();
	App::IntervalUdpServer = set.value("IntervalUdpServer").toInt();
	App::UdpListenIP = set.value("UdpListenIP").toString();
	App::UdpListenPort = set.value("UdpListenPort").toInt();
	App::SelectAllUdpServer = set.value("SelectAllUdpServer").toBool();
	set.endGroup();

	set.beginGroup("ComConfig");
	App::PortName = set.value("PortName").toString();
	App::BaudRate = set.value("BaudRate").toInt();
	App::DataBit = set.value("DataBit").toInt();
	App::Parity = set.value("Parity").toString();
	App::StopBit = set.value("StopBit").toInt();

	App::HexSend = set.value("HexSend").toBool();
	App::HexReceive = set.value("HexReceive").toBool();
	App::Debug = set.value("Debug").toBool();
	App::AutoClear = set.value("AutoClear").toBool();

	App::AutoSend = set.value("AutoSend").toBool();
	App::SendInterval = set.value("SendInterval").toInt();
	App::AutoSave = set.value("AutoSave").toBool();
	App::SaveInterval = set.value("SaveInterval").toInt();
	set.endGroup();

	set.beginGroup("NetConfig");
	App::Mode = set.value("Mode").toString();
	App::ServerIP = set.value("ServerIP").toString();
	App::ServerPort = set.value("ServerPort").toInt();
	App::ListenPort = set.value("ListenPort").toInt();
	App::SleepTime = set.value("SleepTime").toInt();
	App::AutoConnect = set.value("AutoConnect").toBool();
	set.endGroup();


}

void App::writeConfig()
{
	QSettings set(App::ConfigFile, QSettings::IniFormat);

	set.beginGroup("AppConfig");
	set.setValue("CurrentIndex", App::CurrentIndex);
	set.endGroup();

	set.beginGroup("TcpClientConfig");
	set.setValue("HexSendTcpClient", App::HexSendTcpClient);
	set.setValue("HexReceiveTcpClient", App::HexReceiveTcpClient);
	set.setValue("DebugTcpClient", App::DebugTcpClient);
	set.setValue("AutoSendTcpClient", App::AutoSendTcpClient);
	set.setValue("IntervalTcpClient", App::IntervalTcpClient);
	set.setValue("TcpServerIP", App::TcpServerIP);
	set.setValue("TcpServerPort", App::TcpServerPort);
	set.endGroup();

	set.beginGroup("TcpServerConfig");
	set.setValue("HexSendTcpServer", App::HexSendTcpServer);
	set.setValue("HexReceiveTcpServer", App::HexReceiveTcpServer);
	set.setValue("DebugTcpServer", App::DebugTcpServer);
	set.setValue("AutoSendTcpServer", App::AutoSendTcpServer);
	set.setValue("IntervalTcpServer", App::IntervalTcpServer);
	set.setValue("TcpListenIP", App::TcpListenIP);
	set.setValue("TcpListenPort", App::TcpListenPort);
	set.setValue("SelectAllTcpServer", App::SelectAllTcpServer);
	set.endGroup();

	set.beginGroup("UdpClientConfig");
	set.setValue("HexSendUdpClient", App::HexSendUdpClient);
	set.setValue("HexReceiveUdpClient", App::HexReceiveUdpClient);
	set.setValue("DebugUdpClient", App::DebugUdpClient);
	set.setValue("AutoSendUdpClient", App::AutoSendUdpClient);
	set.setValue("IntervalUdpClient", App::IntervalUdpClient);
	set.setValue("UdpServerIP", App::UdpServerIP);
	set.setValue("UdpServerPort", App::UdpServerPort);
	set.endGroup();

	set.beginGroup("UdpServerConfig");
	set.setValue("HexSendUdpServer", App::HexSendUdpServer);
	set.setValue("HexReceiveUdpServer", App::HexReceiveUdpServer);
	set.setValue("DebugUdpServer", App::DebugUdpServer);
	set.setValue("AutoSendUdpServer", App::AutoSendUdpServer);
	set.setValue("IntervalUdpServer", App::IntervalUdpServer);
	set.setValue("UdpListenIP", App::UdpListenIP);
	set.setValue("UdpListenPort", App::UdpListenPort);
	set.setValue("SelectAllUdpServer", App::SelectAllUdpServer);
	set.endGroup();

	set.beginGroup("ComConfig");
	set.setValue("PortName", App::PortName);
	set.setValue("BaudRate", App::BaudRate);
	set.setValue("DataBit", App::DataBit);
	set.setValue("Parity", App::Parity);
	set.setValue("StopBit", App::StopBit);

	set.setValue("HexSend", App::HexSend);
	set.setValue("HexReceive", App::HexReceive);
	set.setValue("Debug", App::Debug);
	set.setValue("AutoClear", App::AutoClear);

	set.setValue("AutoSend", App::AutoSend);
	set.setValue("SendInterval", App::SendInterval);
	set.setValue("AutoSave", App::AutoSave);
	set.setValue("SaveInterval", App::SaveInterval);
	set.endGroup();

	set.beginGroup("NetConfig");
	set.setValue("Mode", App::Mode);
	set.setValue("ServerIP", App::ServerIP);
	set.setValue("ServerPort", App::ServerPort);
	set.setValue("ListenPort", App::ListenPort);
	set.setValue("SleepTime", App::SleepTime);
	set.setValue("AutoConnect", App::AutoConnect);
	set.endGroup();
}

void App::newConfig()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#endif
	writeConfig();
}

bool App::checkConfig()
{
	//如果配置文件大小为0,则以初始值继续运行,并生成配置文件
	QFile file(App::ConfigFile);
	if(file.size() == 0)
	{
		newConfig();
		return false;
	}

	//如果配置文件不完整,则以初始值继续运行,并生成配置文件
	if(file.open(QFile::ReadOnly))
	{
		bool ok = true;
		while(!file.atEnd())
		{
			QString line = file.readLine();
			line = line.replace("\r", "");
			line = line.replace("\n", "");
			QStringList list = line.split("=");

			if(list.count() == 2)
			{
				if(list.at(1) == "")
				{
					ok = false;
					break;
				}
			}
		}

		if(!ok)
		{
			newConfig();
			return false;
		}
	}
	else
	{
		newConfig();
		return false;
	}

	return true;
}

QStringList App::Intervals = QStringList();
QStringList App::Datas = QStringList();
QStringList App::Keys = QStringList();
QStringList App::Values = QStringList();
QMap<QString, QStringList> App::m_map = QMap<QString, QStringList>();
int App::debugdelay = 100;
QStringList App::Protocollst = QStringList();
QStringList App::Transferlst = QStringList();
QStringList App::CRClst = QStringList();
QStringList App::Transfermode = QStringList();

void App::readSendData()
{
	//读取发送数据列表
	App::Datas.clear();
	QString fileName = QString("%1/%2").arg(QUIHelper::appPath()).arg(App::SendFileName);
	QFile file(fileName);
	if(file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text))
	{
		while(!file.atEnd())
		{
			QString line = file.readLine();
			line = line.trimmed();
			line = line.replace("\r", "");
			line = line.replace("\n", "");
			if(!line.isEmpty())
			{
				App::Datas.append(line);
			}
		}

		file.close();
	}
}
/*
void App::readDeviceData()
{
	//读取转发数据列表
	App::Keys.clear();
	App::Values.clear();
	QString fileName = QString("%1/%2").arg(QUIHelper::appPath()).arg(App::DeviceFileName);
	QFile file(fileName);
	if(file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text))
	{
		while(!file.atEnd())
		{
			QString line = file.readLine();
			line = line.trimmed();
			line = line.replace("\r", "");
			line = line.replace("\n", "");
			if(!line.isEmpty())
			{
				QStringList list = line.split(";");
				QString key = list.at(0);
				QString value;
				for(int i = 1; i < list.count(); i++)
				{
					value += QString("%1;").arg(list.at(i));
				}

				//去掉末尾分号
				value = value.mid(0, value.length() - 1);
				App::Keys.append(key);
				App::Values.append(value);
			}
		}

		file.close();
	}
}
*/
void App::readDeviceData()
{
	//读取转发数据列表
	App::Keys.clear();
	App::Values.clear();
	QString fileName = QString("%1/%2").arg(QUIHelper::appPath()).arg(App::DeviceFileName);
	QFile file(fileName);
	if(file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text))
	{
		while(!file.atEnd())
		{
			QString line = file.readLine();
			line = line.trimmed();
			line = line.replace("\r", "");
			line = line.replace("\n", "");
			if(!line.isEmpty())
			{
				if(line.startsWith('#'))
				{
					continue;
				}
				QStringList list = line.split(";");

				if(list.count() > 1)
				{
					QString key = list.at(0).trimmed().toUpper();
					QString value = list.at(1).trimmed().toUpper();
					App::Keys.append(key);
					App::Values.append(value);
				}
			}
		}

		file.close();
	}
}
