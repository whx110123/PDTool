#ifndef IEC101ASDU110DATA_H
#define IEC101ASDU110DATA_H

#include "iec101asdu.h"



class IEC101Asdu110Data : public IEC101AsduData
{
public:
	IEC101Asdu110Data();
	~IEC101Asdu110Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qpm;
};

#endif // IEC101ASDU110DATA_H
