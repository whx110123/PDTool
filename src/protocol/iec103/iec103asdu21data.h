#ifndef IEC103ASDU21DATA_H
#define IEC103ASDU21DATA_H

#include "iec103asdu10data.h"

class IEC103Asdu21Data : public IEC103AsduData
{
public:
	IEC103Asdu21Data();
	~IEC103Asdu21Data();
	virtual bool handle(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar rii;
	uchar nog;
	QList<IEC103Asdu10DataSet *> setlist;
};

#endif // IEC103ASDU21DATA_H
