#ifndef MYBASE_H
#define MYBASE_H

#include "dataconfig.h"
#include "functotext.h"


class MyBase
{
public:
	explicit MyBase(const MyConfig& Config);
	virtual ~MyBase();
	virtual bool init(const QByteArray& buff);			//初始化
	virtual QString showToText();						//显示解析结果
	virtual bool createData(MyData& proData);		//生成报文
	void setDefault(const QByteArray& buff);
public:
	QByteArray mSendData;	//发送报文
	QByteArray mRecvData;	//接收报文
	int len;				//接收报文长度
	QString mText;			//详细解析
	static QString mTextS;	//简要解析
	static QString error;	//错误说明
	int masterState;		//主站状态
	int slaveState;			//子站状态
	int index;				//此段内容在整个报文中的下标
	MyConfig mConfig;
};

#endif // MYBASE_H
