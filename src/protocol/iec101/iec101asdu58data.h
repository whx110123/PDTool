#ifndef IEC101ASDU58DATA_H
#define IEC101ASDU58DATA_H

#include "iec101asdu45data.h"



class IEC101Asdu58Data : public IEC101Asdu45Data
{
public:
	IEC101Asdu58Data();
	~IEC101Asdu58Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU58DATA_H
