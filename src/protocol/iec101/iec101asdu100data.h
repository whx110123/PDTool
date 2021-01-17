#ifndef IEC101ASDU100DATA_H
#define IEC101ASDU100DATA_H

#include "iec101asdu.h"

class IEC101Asdu100Data : public IEC101AsduData
{
public:
	IEC101Asdu100Data();
	~IEC101Asdu100Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar qoi;

};

#endif // IEC101ASDU100DATA_H
