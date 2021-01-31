#ifndef IEC103ASDU42DATA_H
#define IEC103ASDU42DATA_H

#include "iec103asdu.h"

class IEC103Asdu42Data : public IEC103AsduData
{
public:
	IEC103Asdu42Data(const MyConfig& Config);
	~IEC103Asdu42Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar diq;
};

#endif // IEC103ASDU42DATA_H
