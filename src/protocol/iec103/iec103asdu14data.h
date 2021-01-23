#ifndef IEC103ASDU14DATA_H
#define IEC103ASDU14DATA_H

#include "iec103asdu.h"



class IEC103Asdu14Data : public IEC103AsduData
{
public:
	IEC103Asdu14Data();
	~IEC103Asdu14Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar rii;
	uchar isLast;
	uint fileIndex;
	QByteArray fileData;
};

#endif // IEC103ASDU14DATA_H
