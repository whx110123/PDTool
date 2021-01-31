#ifndef IEC101ASDU34DATA_H
#define IEC101ASDU34DATA_H

#include "iec101asdu10data.h"



class IEC101Asdu34Data : public IEC101Asdu10Data
{
public:
	IEC101Asdu34Data(const MyConfig& Config);
	~IEC101Asdu34Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC101ASDU34DATA_H
