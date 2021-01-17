#ifndef MEASUREDTERMINAL_H
#define MEASUREDTERMINAL_H

#include "measuredterminalapci.h"
#include "measuredterminalasdu.h"

class MeasuredTerminal : public MyBase
{
public:
	MeasuredTerminal();
	~MeasuredTerminal();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	MTApci apci;
	MTAsdu asdu;
	uchar crc;
	uchar end;

public:
	QString mLengthType;		//长度域类型
};

#endif // MEASUREDTERMINAL_H
