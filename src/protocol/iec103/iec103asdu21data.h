#ifndef IEC103ASDU21DATA_H
#define IEC103ASDU21DATA_H

#include "iec103asdu10data.h"

class IEC103Asdu21DataSet : public MyBase
{
public:
	IEC103Asdu21DataSet(const MyConfig& Config);
	~IEC103Asdu21DataSet();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar gin[2];
	uchar kod;
};


class IEC103Asdu21Data : public IEC103AsduData
{
public:
	IEC103Asdu21Data(const MyConfig& Config);
	~IEC103Asdu21Data();
	virtual bool handle(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(MyData& proData);

public:
	uchar rii;
	uchar nog;
	QList<IEC103Asdu21DataSet *> setlist;
};

#endif // IEC103ASDU21DATA_H
