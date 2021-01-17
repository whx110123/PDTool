#ifndef IEC101ASDU12DATA_H
#define IEC101ASDU12DATA_H

#include "iec101asdu10data.h"



class IEC101Asdu12Data : public IEC101Asdu10Data
{
public:
	IEC101Asdu12Data();
	~IEC101Asdu12Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU12DATA_H
