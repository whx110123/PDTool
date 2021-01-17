#ifndef IEC103ASDU29DATA_H
#define IEC103ASDU29DATA_H

#include "iec103asdu1data.h"

class IEC103Asdu29Data : public IEC103AsduData
{
public:
	IEC103Asdu29Data();
	~IEC103Asdu29Data();
	virtual bool handle(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	ushort fan;
	uchar _not;
	ushort tap;
	QList<IEC103Asdu1Data *> setlist;
};

#endif // IEC103ASDU29DATA_H
