#ifndef IEC103ASDU6DATA_H
#define IEC103ASDU6DATA_H

#include "iec103asdu.h"

class IEC103Asdu6Data : public IEC103AsduData
{
public:
	IEC103Asdu6Data();
	~IEC103Asdu6Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC103ASDU6DATA_H
