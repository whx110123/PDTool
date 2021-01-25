#ifndef IEC103ASDU104DATA_H
#define IEC103ASDU104DATA_H

#include "iec103asdu.h"



class IEC103Asdu104Data : public IEC103AsduData
{
public:
	IEC103Asdu104Data();
	~IEC103Asdu104Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar rii;
	uchar isLast;
	uint fileIndex;
	QByteArray fileData;
};

#endif // IEC103ASDU104DATA_H
