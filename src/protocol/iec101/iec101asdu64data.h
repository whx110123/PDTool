#ifndef IEC101ASDU64DATA_H
#define IEC101ASDU64DATA_H

#include "iec101asdu51data.h"



class IEC101Asdu64Data : public IEC101Asdu51Data
{
public:
	IEC101Asdu64Data();
	~IEC101Asdu64Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU64DATA_H
