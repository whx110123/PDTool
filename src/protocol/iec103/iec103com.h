#ifndef IEC103COM_H
#define IEC103COM_H

#include "iec103asdu.h"
#include <iec101apci.h>

class IEC103COM : public MyBase
{
public:
	IEC103COM(const MyConfig& Config);
	~IEC103COM();
	virtual bool init(const QByteArray& buff);

public:
	IEC101Apci apci;
	IEC103Asdu asdu;
	uchar crc;
	uchar end;

};

#endif // IEC103COM_H
