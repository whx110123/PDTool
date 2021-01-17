#ifndef IEC101ASDU61DATA_H
#define IEC101ASDU61DATA_H

#include "iec101asdu48data.h"



class IEC101Asdu61Data : public IEC101Asdu48Data
{
public:
	IEC101Asdu61Data();
	~IEC101Asdu61Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU61DATA_H
