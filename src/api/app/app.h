#ifndef APP_H
#define APP_H

#include "head.h"

class App
{
public:
	static QString ConfigFile;          //配置文件路径
	static QString SendFileName;        //发送配置文件名
	static QString DeviceFileName;      //模拟设备数据文件名

	static int CurrentIndex;            //当前索引

	//TCP客户端配置参数
	static bool HexSendTcpClient;       //16进制发送
	static bool HexReceiveTcpClient;    //16进制接收
	static bool AsciiTcpClient;         //ASCII模式
	static bool DebugTcpClient;         //启用数据调试
	static bool AutoSendTcpClient;      //自动发送数据
	static int IntervalTcpClient;       //发送数据间隔
	static QString TcpServerIP;         //服务器IP
	static int TcpServerPort;           //服务器端口

	//TCP服务器配置参数
	static bool HexSendTcpServer;       //16进制发送
	static bool HexReceiveTcpServer;    //16进制接收
	static bool AsciiTcpServer;         //ASCII模式
	static bool DebugTcpServer;         //启用数据调试
	static bool AutoSendTcpServer;      //自动发送数据
	static int IntervalTcpServer;       //发送数据间隔
	static QString TcpListenIP;         //监听地址
	static int TcpListenPort;           //监听端口
	static bool SelectAllTcpServer;     //选中所有

	//UDP客户端配置参数
	static bool HexSendUdpClient;       //16进制发送
	static bool HexReceiveUdpClient;    //16进制接收
	static bool AsciiUdpClient;         //ASCII模式
	static bool DebugUdpClient;         //启用数据调试
	static bool AutoSendUdpClient;      //自动发送数据
	static int IntervalUdpClient;       //发送数据间隔
	static QString UdpServerIP;         //服务器IP
	static int UdpServerPort;           //服务器端口

	//UDP服务器配置参数
	static bool HexSendUdpServer;       //16进制发送
	static bool HexReceiveUdpServer;    //16进制接收
	static bool AsciiUdpServer;         //ASCII模式
	static bool DebugUdpServer;         //启用数据调试
	static bool AutoSendUdpServer;      //自动发送数据
	static int IntervalUdpServer;       //发送数据间隔
	static QString UdpListenIP;         //监听地址
	static int UdpListenPort;           //监听端口
	static bool SelectAllUdpServer;     //选中所有

	//Com口配置参数
	static QString PortName;            //串口号
	static int BaudRate;                //波特率
	static int DataBit;                 //数据位
	static QString Parity;              //校验位
	static double StopBit;              //停止位

	static bool HexSend;                //16进制发送
	static bool HexReceive;             //16进制接收
	static bool Debug;                  //模拟设备
	static bool AutoClear;              //自动清空

	static bool AutoSend;               //自动发送
	static int SendInterval;            //自动发送间隔
	static bool AutoSave;               //自动保存
	static int SaveInterval;            //自动保存间隔

	static QString Mode;                //转换模式
	static QString ServerIP;            //服务器IP
	static int ServerPort;              //服务器端口
	static int ListenPort;              //监听端口
	static int SleepTime;               //延时时间
	static bool AutoConnect;            //自动重连


	//解析报文配置参数
	static QString DefaultProtocol;       //默认规约

	//皮肤
	static uint CurrentSkin;			//默认皮肤

	//读写配置参数及其他操作
	static void readConfig();           //读取配置参数
	static void writeConfig();          //写入配置参数
	static void newConfig();            //以初始值新建配置文件
	static bool checkConfig();          //校验配置文件

	static QStringList Intervals;
	static QStringList Datas;
	static QStringList Keys;
	static QStringList Values;
	static QMap<QString, QStringList> m_map;	//模拟装置的数据表
	static int debugdelay;					//模拟装置的延时时间
	static QStringList Protocollst;     //规约表
	static QStringList Transferlst;     //通信方式表
	static QStringList CRClst;          //校验方式
	static QStringList Transfermode;    //数字与16进制转换方式

	static void readSendData();
	static void readDeviceData();
};

#endif // APP_H
