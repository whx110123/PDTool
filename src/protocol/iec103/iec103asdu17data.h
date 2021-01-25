#ifndef IEC103ASDU17DATA_H
#define IEC103ASDU17DATA_H

#include "iec103asdu15data.h"



class IEC103Asdu17Data : public IEC103Asdu15Data
{
public:
	IEC103Asdu17Data();
	~IEC103Asdu17Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar eventType;
};

#endif // IEC103ASDU17DATA_H
