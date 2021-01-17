#ifndef IEC101ASDU7DATA_H
#define IEC101ASDU7DATA_H

#include "iec101asdu51data.h"



class IEC101Asdu7Data : public IEC101Asdu51Data
{
public:
	IEC101Asdu7Data();
	~IEC101Asdu7Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar qds;
};

#endif // IEC101ASDU7DATA_H
