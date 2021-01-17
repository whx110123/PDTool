#ifndef MEASUREDTERMINALASDUDATA_H
#define MEASUREDTERMINALASDUDATA_H

#include <mybase.h>

class MTAsduData : public MyBase
{
public:
	MTAsduData();
	~MTAsduData();
	virtual bool init(const QByteArray& buff);

	QString DAToText();
	QString DIToText();
	void dataClear();							//清除所有数据
	bool handle(const QByteArray& buff);		//处理数据
	bool handleData_1(const QByteArray& buff);	//处理数据方式1：4字节无符号整数，两位小数点

public:

	uchar flag;								//功能标志，用于记录功能码对应的报文内容
	uchar DA[2];							//信息点标识
	uchar DI[4];							//数据标识编码

	ushort dataTpye;						//数据类型

	QVector<uint> uintLst;

	QDateTime dt1;							//数据时间1
	QDateTime dt2;							//数据时间2
	uchar density;							//数据密度

};

#endif // MEASUREDTERMINALASDUDATA_H
