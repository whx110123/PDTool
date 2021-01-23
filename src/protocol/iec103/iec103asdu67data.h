#ifndef IEC103ASDU67DATA_H
#define IEC103ASDU67DATA_H

#include "iec103asdu.h"



class IEC103Asdu67Data : public IEC103AsduData
{
public:
	IEC103Asdu67Data();
	~IEC103Asdu67Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar ccc;
};

#endif // IEC103ASDU67DATA_H
