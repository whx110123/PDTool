#ifndef IEC103ASDU10DATA_H
#define IEC103ASDU10DATA_H

#include "iec103asdu.h"

class IEC103Asdu10DataSetGdd;
class IEC103Asdu10DataSetGid : public MyBase
{
public:
	IEC103Asdu10DataSetGid();
	~IEC103Asdu10DataSetGid();
	bool initgid(const QByteArray& buff, uchar *ch);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	QString gbkstr;
	QString bit8;
	float datafloat;
	short datashort;
	uint datauint;
	uint datauint1;
	int dataint;
	uchar datauchar;
	uchar datauchar1;
	QDateTime datet;
	QList<IEC103Asdu10DataSetGdd *> gddlist;
};

class IEC103Asdu10DataSetGdd : public MyBase
{
public:
	IEC103Asdu10DataSetGdd();
	~IEC103Asdu10DataSetGdd();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar gdd[3];
	int gidnum;
	QList<IEC103Asdu10DataSetGid *> gidlist;
};

class IEC103Asdu10DataSet : public MyBase
{
public:
	IEC103Asdu10DataSet();
	~IEC103Asdu10DataSet();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar gin[2];
	uchar kod;
	IEC103Asdu10DataSetGdd mygdd;
};

class IEC103Asdu10Data : public IEC103AsduData
{
public:
	IEC103Asdu10Data();
	~IEC103Asdu10Data();
	virtual bool handle(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar rii;
	uchar ngd;
	int setnum;
	QList<IEC103Asdu10DataSet *> setlist;

};

#endif // IEC103ASDU10DATA_H
