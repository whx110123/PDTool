#ifndef MYBASE_H
#define MYBASE_H

#include "dataconfig.h"
#include "functotext.h"


class MyBase
{
public:
	MyBase();
	virtual ~MyBase();
	virtual bool init(const QByteArray& buff);			//初始化
	virtual QString showToText();						//显示解析结果
	virtual bool createData(IECDataConfig& config);		//生成报文
	void setDefault(const QByteArray& buff);
public:
	QString protocolName;		//规约名
	QByteArray mSendData;	//发送报文
	QByteArray mRecvData;	//接收报文
	int len;				//接收报文长度
	QString mText;			//解析
	static QString error;	//错误说明
	int masterState;		//主站状态
	int slaveState;			//子站状态
	int index;				//此段内容在整个报文中的下标
	static MyConfig mConfig;
};

#endif // MYBASE_H
