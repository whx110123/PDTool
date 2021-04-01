#ifndef DATACONFIG_H
#define DATACONFIG_H

#include "globaldefine.h"

struct ModbusDataGroup
{
	uchar dataLen;		//应答报文数据字节数
	QString type;		//数据类型
	QString analysis;	//解析码
	QString sort;		//顺序
};

struct MyConfig			//报文格式
{
	QString protocolName;				//规约名
	QString lengthType;					//长度域类型
	int addrLen;						//地址域字节数
	int cotlen ;						//cot长度
	int comaddrlen ;					//公共地址长度
	int infaddrlen ;					//信息体地址长度
	QVector<ModbusDataGroup> groups;	//界面提供的解析方式
};

class MyData			//数据信息
{
public:
	MyData();
	~MyData();
	QByteArray data;		//总报文
	uint len;				//报文长度
	uchar flag;				//标记是否需要带地址
};


#endif // DATACONFIG_H
