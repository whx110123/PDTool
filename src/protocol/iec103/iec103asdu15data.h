#ifndef IEC103ASDU15DATA_H
#define IEC103ASDU15DATA_H

#include "iec103asdu.h"



class IEC103Asdu15Data : public IEC103AsduData
{
public:
	IEC103Asdu15Data();
	~IEC103Asdu15Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar rii;
	QDateTime dtBegin;
	QDateTime dtEnd;
};

#endif // IEC103ASDU15DATA_H
