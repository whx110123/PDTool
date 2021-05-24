#include "app.h"
#include "quiwidget.h"
#include "globaldefine.h"

/*无需保存*/
QString App::DefaultProtocol = IEC_104;
QString App::ConfigFile = QString();
QString App::SendFileName = "send.txt";
QString App::DeviceFileName = "device.txt";
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

/*[AppConfig]*/
int App::CurrentIndex = 0;
uint App::CurrentSkin = 1;
/*[TcpClientConfig]*/
bool App::HexSendTcpClient = true;
bool App::HexReceiveTcpClient = true;
bool App::AsciiTcpClient = false;
bool App::DebugTcpClient = false;
bool App::AutoSendTcpClient = false;
int App::IntervalTcpClient = 1000;
QString App::TcpServerIP = "127.0.0.1";
int App::TcpServerPort = 6000;
/*[TcpServerConfig]*/
bool App::HexSendTcpServer = true;
bool App::HexReceiveTcpServer = true;
bool App::AsciiTcpServer = false;
bool App::DebugTcpServer = false;
bool App::AutoSendTcpServer = false;
int App::IntervalTcpServer = 1000;
QString App::TcpListenIP = "127.0.0.1";
int App::TcpListenPort = 6000;
bool App::SelectAllTcpServer = true;
/*[UdpClientConfig]*/
bool App::HexSendUdpClient = true;
bool App::HexReceiveUdpClient = true;
bool App::AsciiUdpClient = false;
bool App::DebugUdpClient = false;
bool App::AutoSendUdpClient = false;
int App::IntervalUdpClient = 1000;
QString App::UdpServerIP = "127.0.0.1";
int App::UdpServerPort = 6000;
/*[UdpServerConfig]*/
bool App::HexSendUdpServer = true;
bool App::HexReceiveUdpServer = true;
bool App::AsciiUdpServer = false;
bool App::DebugUdpServer = false;
bool App::AutoSendUdpServer = false;
int App::IntervalUdpServer = 1000;
QString App::UdpListenIP = "127.0.0.1";
int App::UdpListenPort = 6000;
bool App::SelectAllUdpServer = true;
/*[ComConfig]*/
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
/*[NetConfig]*/
QString App::Mode = "Tcp_Client";
QString App::ServerIP = "127.0.0.1";
int App::ServerPort = 6000;
int App::ListenPort = 6000;
int App::SleepTime = 100;
bool App::AutoConnect = false;


void App::readConfig()
{
	if(!QUIHelper::checkIniFile(App::ConfigFile))
	{
		writeConfig();
		return;
	}

	QSettings set(App::ConfigFile, QSettings::IniFormat);

	set.beginGroup("AppConfig");
	App::CurrentIndex = set.value("CurrentIndex", App::CurrentIndex).toInt();
	App::CurrentSkin = set.value("CurrentSkin", App::CurrentSkin).toUInt();
	set.endGroup();

	set.beginGroup("TcpClientConfig");
	App::HexSendTcpClient = set.value("HexSendTcpClient", App::HexSendTcpClient).toBool();
	App::HexReceiveTcpClient = set.value("HexReceiveTcpClient", App::HexReceiveTcpClient).toBool();
	App::AsciiTcpClient = set.value("AsciiTcpClient", App::AsciiTcpClient).toBool();
	App::DebugTcpClient = set.value("DebugTcpClient", App::DebugTcpClient).toBool();
	App::AutoSendTcpClient = set.value("AutoSendTcpClient", App::AutoSendTcpClient).toBool();
	App::IntervalTcpClient = set.value("IntervalTcpClient", App::IntervalTcpClient).toInt();
	App::TcpServerIP = set.value("TcpServerIP", App::TcpServerIP).toString();
	App::TcpServerPort = set.value("TcpServerPort", App::TcpServerPort).toInt();
	set.endGroup();

	set.beginGroup("TcpServerConfig");
	App::HexSendTcpServer = set.value("HexSendTcpServer", App::HexSendTcpServer).toBool();
	App::HexReceiveTcpServer = set.value("HexReceiveTcpServer", App::HexReceiveTcpServer).toBool();
	App::AsciiTcpServer = set.value("AsciiTcpServer", App::AsciiTcpServer).toBool();
	App::DebugTcpServer = set.value("DebugTcpServer", App::DebugTcpServer).toBool();
	App::AutoSendTcpServer = set.value("AutoSendTcpServer", App::AutoSendTcpServer).toBool();
	App::IntervalTcpServer = set.value("IntervalTcpServer", App::IntervalTcpServer).toInt();
	App::TcpListenIP = set.value("TcpListenIP", App::TcpListenIP).toString();
	App::TcpListenPort = set.value("TcpListenPort", App::TcpListenPort).toInt();
	App::SelectAllTcpServer = set.value("SelectAllTcpServer", App::SelectAllTcpServer).toBool();
	set.endGroup();

	set.beginGroup("UdpClientConfig");
	App::HexSendUdpClient = set.value("HexSendUdpClient", App::HexSendUdpClient).toBool();
	App::HexReceiveUdpClient = set.value("HexReceiveUdpClient", App::HexReceiveUdpClient).toBool();
	App::AsciiUdpClient = set.value("AsciiUdpClient", App::AsciiUdpClient).toBool();
	App::DebugUdpClient = set.value("DebugUdpClient", App::DebugUdpClient).toBool();
	App::AutoSendUdpClient = set.value("AutoSendUdpClient", App::AutoSendUdpClient).toBool();
	App::IntervalUdpClient = set.value("IntervalUdpClient", App::IntervalUdpClient).toInt();
	App::UdpServerIP = set.value("UdpServerIP", App::UdpServerIP).toString();
	App::UdpServerPort = set.value("UdpServerPort", App::UdpServerPort).toInt();
	set.endGroup();

	set.beginGroup("UdpServerConfig");
	App::HexSendUdpServer = set.value("HexSendUdpServer", App::HexSendUdpServer).toBool();
	App::HexReceiveUdpServer = set.value("HexReceiveUdpServer", App::HexReceiveUdpServer).toBool();
	App::AsciiUdpServer = set.value("AsciiUdpServer", App::AsciiUdpServer).toBool();
	App::DebugUdpServer = set.value("DebugUdpServer", App::DebugUdpServer).toBool();
	App::AutoSendUdpServer = set.value("AutoSendUdpServer", App::AutoSendUdpServer).toBool();
	App::IntervalUdpServer = set.value("IntervalUdpServer", App::IntervalUdpServer).toInt();
	App::UdpListenIP = set.value("UdpListenIP", App::UdpListenIP).toString();
	App::UdpListenPort = set.value("UdpListenPort", App::UdpListenPort).toInt();
	App::SelectAllUdpServer = set.value("SelectAllUdpServer", App::SelectAllUdpServer).toBool();
	set.endGroup();

	set.beginGroup("ComConfig");
	App::PortName = set.value("PortName", App::PortName).toString();
	App::BaudRate = set.value("BaudRate", App::BaudRate).toInt();
	App::DataBit = set.value("DataBit", App::DataBit).toInt();
	App::Parity = set.value("Parity", App::Parity).toString();
	App::StopBit = set.value("StopBit", App::StopBit).toInt();

	App::HexSend = set.value("HexSend", App::HexSend).toBool();
	App::HexReceive = set.value("HexReceive", App::HexReceive).toBool();
	App::Debug = set.value("Debug", App::Debug).toBool();
	App::AutoClear = set.value("AutoClear", App::AutoClear).toBool();

	App::AutoSend = set.value("AutoSend", App::AutoSend).toBool();
	App::SendInterval = set.value("SendInterval", App::SendInterval).toInt();
	App::AutoSave = set.value("AutoSave", App::AutoSave).toBool();
	App::SaveInterval = set.value("SaveInterval", App::SaveInterval).toInt();
	set.endGroup();

	set.beginGroup("NetConfig");
	App::Mode = set.value("Mode", App::Mode).toString();
	App::ServerIP = set.value("ServerIP", App::ServerIP).toString();
	App::ServerPort = set.value("ServerPort", App::ServerPort).toInt();
	App::ListenPort = set.value("ListenPort", App::ListenPort).toInt();
	App::SleepTime = set.value("SleepTime", App::SleepTime).toInt();
	App::AutoConnect = set.value("AutoConnect", App::AutoConnect).toBool();
	set.endGroup();
}

void App::writeConfig()
{
	QSettings set(App::ConfigFile, QSettings::IniFormat);

	set.beginGroup("AppConfig");
	set.setValue("CurrentIndex", App::CurrentIndex);
	set.setValue("CurrentSkin", App::CurrentSkin);
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

void App::saveData(const QString& data)
{
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
}
