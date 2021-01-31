#ifndef IEC101ASDU10DATA_H
#define IEC101ASDU10DATA_H

#include "iec101asdu9data.h"



class IEC101Asdu10Data : public IEC101Asdu9Data
{
public:
	IEC101Asdu10Data(const MyConfig& Config);
	~IEC101Asdu10Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU10DATA_H
