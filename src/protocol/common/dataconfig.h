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
	void getAttribute(const MyData& md);		//获取除了数据以外的属性
	MyData operator+(const MyData& md) const;

	QByteArray data;		//总报文
	uchar sqFlag;				//标记是否需要带地址
	bool reverse;			//0:在后面添加，1:在前面添加

};


#endif // DATACONFIG_H
