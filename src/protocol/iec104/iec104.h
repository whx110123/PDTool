#ifndef IEC104_H
#define IEC104_H

#include "iec104apci.h"
#include "iec101asdu.h"

class IEC104 : public MyBase
{
public:
	IEC104();
	~IEC104();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	IEC104Apci apci;
	IEC101Asdu asdu;

public:
	QString mLengthType;
};

#endif // IEC104_H
