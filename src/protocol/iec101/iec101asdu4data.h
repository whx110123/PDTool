#ifndef IEC101ASDU4DATA_H
#define IEC101ASDU4DATA_H

#include "iec101asdu3data.h"



class IEC101Asdu4Data : public IEC101Asdu3Data
{
public:
	IEC101Asdu4Data();
	~IEC101Asdu4Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU4DATA_H
