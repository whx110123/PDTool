#ifndef IEC103ASDU5DATA_H
#define IEC103ASDU5DATA_H

#include "iec103asdu.h"



class IEC103Asdu5Data : public IEC103AsduData
{
public:
	IEC103Asdu5Data();
	~IEC103Asdu5Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar col;
	QString gbkstr;
	uchar ch[4];
};

#endif // IEC103ASDU5DATA_H
