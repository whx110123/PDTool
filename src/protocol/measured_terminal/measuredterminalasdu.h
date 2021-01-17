#ifndef MEASUREDTERMINALASDU_H
#define MEASUREDTERMINALASDU_H

#include "measuredterminalasdudata.h"

class MTAsdu : public MyBase
{
public:
	MTAsdu();
	~MTAsdu();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	QString afnToText();
	QString seqToText();
	uchar afn;								//应用层功能码
	uchar seq;								//帧序列域
	QList<MTAsduData *> datalist;
	uchar pw[16];							//消息验证码
	QDateTime dt;							//启动帧发送时标
	uchar delayTime;						//允许发送传输延时时间
	uchar flag;								//功能标志，用于记录功能码对应的报文内容
};

#endif // MEASUREDTERMINALASDU_H
