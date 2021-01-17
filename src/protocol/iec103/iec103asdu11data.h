#ifndef IEC103ASDU11DATA_H
#define IEC103ASDU11DATA_H

#include "iec103asdu10data.h"

class IEC103Asdu11DataSet : public IEC103Asdu10DataSet
{
public:
	IEC103Asdu11DataSet();
	~IEC103Asdu11DataSet();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

};

class IEC103Asdu11Data : public IEC103AsduData
{
public:
	IEC103Asdu11Data();
	~IEC103Asdu11Data();
	virtual bool handle(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar rii;
	uchar gin[2];
	uchar nde;
	int setnum;
	QList<IEC103Asdu11DataSet *> setlist;
};

#endif // IEC103ASDU11DATA_H
