#ifndef IEC103ASDU18DATA_H
#define IEC103ASDU18DATA_H

#include "iec103asdu10data.h"
#include "iec103asdu15data.h"

class HisInfo : public MyBase
{
public:
	HisInfo(const MyConfig& Config);
	~HisInfo();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();

public:
	uchar devaddr;
	uchar eventType;
	uchar fun;
	uchar inf;
	uchar dpi;
	ushort ret;
	short fan;
	float scl;
	uchar fpt;
	QDateTime dt;
	QDateTime rcvdt;
	uchar eventNum;
	QList<IEC103Asdu10DataSet *> setlist;
};

class IEC103Asdu18Data : public IEC103Asdu15Data
{
public:
	IEC103Asdu18Data(const MyConfig& Config);
	~IEC103Asdu18Data();
	virtual bool handle(const QByteArray& buff);
	virtual QString showToText();

public:
	uchar isLast;
	uchar hisNum;
	QList<HisInfo *> hisInfos;
};

#endif // IEC103ASDU18DATA_H
