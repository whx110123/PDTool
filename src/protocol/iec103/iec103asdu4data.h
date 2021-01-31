#ifndef IEC103ASDU4DATA_H
#define IEC103ASDU4DATA_H

#include "iec103asdu.h"



class IEC103Asdu4Data : public IEC103AsduData
{
public:
	IEC103Asdu4Data(const MyConfig& Config);
	~IEC103Asdu4Data();
	virtual bool handle(const QByteArray& buff);

public:
	float scl;
	ushort ret;
	ushort fan;
	QDateTime datetime;
};

#endif // IEC103ASDU4DATA_H
