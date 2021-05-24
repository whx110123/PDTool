#ifndef MYBASE_H
#define MYBASE_H

#include "dataconfig.h"
#include "functotext.h"


class MyBase
{
public:
	explicit MyBase(const MyConfig& Config);
	virtual ~MyBase();
	virtual bool init(const QByteArray& buff);		//初始化
	virtual bool createData(MyData& proData);		//生成报文
	const QString showToText();						//显示解析结果
	void setDefault(const QByteArray& buff);
protected:
	QString mText;			//详细解析
public:
	QByteArray mSendData;	//发送报文
	QByteArray mRecvData;	//接收报文
	int mLen;				//接收报文长度
	static QString mTextS;	//简要解析
	static QString mError;	//错误说明
	int mIndex;				//此段内容在整个报文中的下标
	MyConfig mConfig;		//报文格式信息
};

#endif // MYBASE_H
