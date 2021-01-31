#ifndef IEC101ASDU32DATA_H
#define IEC101ASDU32DATA_H

#include "iec101asdu6data.h"


class IEC101Asdu32Data : public IEC101Asdu6Data
{
public:
	IEC101Asdu32Data(const MyConfig& Config);
	~IEC101Asdu32Data();
	virtual bool handle(const QByteArray& buff);

};

#endif // IEC101ASDU32DATA_H
