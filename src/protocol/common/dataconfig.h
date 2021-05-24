#ifndef DATACONFIG_H
#define DATACONFIG_H

#include "globaldefine.h"

class MyLog
{
public:
	MyLog();
	~MyLog();

	enum logType
	{
		DEFAULT,
		SENDDATA,
		RECVDATA,
		ERRORLOG,
		ALLLOG,
	};
	uchar masterType;	//规约类型
	uchar type;			//log类型
	QDateTime dt;		//时间
	QString text_s;		//简易文本
	QString text;		//详细文本
	QString text_error;	//错误说明
};
Q_DECLARE_METATYPE(MyLog)

/*
MyStruct s;
QVariant var;
var.setValue(s); // copy s into the variant

...

// retrieve the value
MyStruct s2 = var.value<MyStruct>();
*/

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

class MyData			//数据包信息
{
public:
	MyData();
	~MyData();
	void getAttribute(const MyData& md);		//获取除了数据以外的属性
	MyData operator+(const MyData& md) const;

	QByteArray data;		//总报文
	uchar sqFlag;			//标记是否需要带地址
	bool reverse;			//0:在后面添加，1:在前面添加

};


#endif // DATACONFIG_H
