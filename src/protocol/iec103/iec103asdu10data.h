#ifndef IEC103ASDU10DATA_H
#define IEC103ASDU10DATA_H

#include "iec103asdu.h"

class IEC103Asdu10DataSetGdd;
class IEC103Asdu10DataSetGid : public MyBase
{
public:
	IEC103Asdu10DataSetGid(const MyConfig& Config);
	~IEC103Asdu10DataSetGid();
	bool initgid(const QByteArray& buff, uchar *ch);
	virtual bool createData(MyData& proData);

public:
	QByteArray gid;
	QList<IEC103Asdu10DataSetGdd *> gddlist;
};

class IEC103Asdu10DataSetGdd : public MyBase
{
public:
	IEC103Asdu10DataSetGdd(const MyConfig& Config);
	~IEC103Asdu10DataSetGdd();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar gdd[3];
	int gidnum;
	QList<IEC103Asdu10DataSetGid *> gidlist;
};

class IEC103Asdu10DataSet : public MyBase
{
public:
	IEC103Asdu10DataSet(const MyConfig& Config);
	~IEC103Asdu10DataSet();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar gin[2];
	uchar kod;
	IEC103Asdu10DataSetGdd mygdd;
};

class IEC103Asdu10Data : public IEC103AsduData
{
public:
	IEC103Asdu10Data(const MyConfig& Config);
	~IEC103Asdu10Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar rii;
	uchar ngd;
	QList<IEC103Asdu10DataSet *> setlist;
};

#endif // IEC103ASDU10DATA_H
