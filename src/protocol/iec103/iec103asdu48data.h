#ifndef IEC103ASDU48DATA_H
#define IEC103ASDU48DATA_H

#include "iec103asdu.h"



class IEC103Asdu48Data : public IEC103AsduData
{
public:
	IEC103Asdu48Data(const MyConfig& Config);
	~IEC103Asdu48Data();
	virtual bool handle(const QByteArray& buff);

public:

	float dataFloat;
	uchar qds;
	QDateTime datetime;
};

#endif // IEC103ASDU48DATA_H
