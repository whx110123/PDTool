#ifndef IEC101ASDU8DATA_H
#define IEC101ASDU8DATA_H

#include "iec101asdu7data.h"



class IEC101Asdu8Data : public IEC101Asdu7Data
{
public:
	IEC101Asdu8Data(const MyConfig& Config);
	~IEC101Asdu8Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU8DATA_H
