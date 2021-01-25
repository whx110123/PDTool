#ifndef IEC103ASDU108DATA_H
#define IEC103ASDU108DATA_H

#include "iec103asdu.h"



class IEC103Asdu108Data : public IEC103AsduData
{
public:
	IEC103Asdu108Data();
	~IEC103Asdu108Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar rii;
	uchar flag;
	uint fileIndex;
};

#endif // IEC103ASDU108DATA_H
