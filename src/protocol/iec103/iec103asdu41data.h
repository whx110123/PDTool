#ifndef IEC103ASDU41DATA_H
#define IEC103ASDU41DATA_H

#include "iec103asdu40data.h"

class IEC103Asdu41Data : public IEC103Asdu40Data
{
public:
	IEC103Asdu41Data(const MyConfig& Config);
	~IEC103Asdu41Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC103ASDU41DATA_H
