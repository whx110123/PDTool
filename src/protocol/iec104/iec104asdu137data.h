#ifndef IEC104ASDU137DATA_H
#define IEC104ASDU137DATA_H

#include "iec101asdu.h"

//计划曲线传送(南网扩展功能)
class IEC104Asdu137Data : public IEC101AsduData
{
public:
	IEC104Asdu137Data(const MyConfig& Config);
	~IEC104Asdu137Data();
	virtual bool handle(const QByteArray& buff);

public:
	short shortdata;
	uchar qos;
	QDateTime datetime;
};

#endif // IEC104ASDU137DATA_H
