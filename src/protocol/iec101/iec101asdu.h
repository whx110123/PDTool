#ifndef IEC101ASDU_H
#define IEC101ASDU_H

#include <mybase.h>

class IEC101AsduData : public MyBase
{
public:
	IEC101AsduData(const MyConfig& Config);
	virtual ~IEC101AsduData();
	virtual bool init(const QByteArray& buff);
	virtual bool init(const QByteArray& buff, uint addr);
	virtual bool handle(const QByteArray& buff);				//单独处理数据

public:
	uchar asduType;										//保留asdu类型
	uint infaddr;
};

class IEC101Asdu : public MyBase
{
public:
	IEC101Asdu(const MyConfig& Config);
	~IEC101Asdu();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(MyData& proData);

public:
	QString typeToText();
	QString vsqToText();
	QString cotToText();
	uchar type;
	uchar vsq;					//SQ 0：每个信息元素都带地址 1：只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
	uchar cot[2];
	uint commonaddr;

	QList<IEC101AsduData *> datalist;

private:
	IEC101AsduData *CreateAsduData(uchar type);
};

#endif // IEC101ASDU_H
