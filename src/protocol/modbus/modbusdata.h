#ifndef MODBUSDATA_H
#define MODBUSDATA_H

#include <mybase.h>

class ModbusData : public MyBase
{
public:
	ModbusData();
	~ModbusData();
	bool initData(const QByteArray& buff, ModbusDataGroup *group);

public:
	QString mtype;		//类型
	QChar mcode;		//解析码

	char datachar;
	uchar datauchar;
	short datashort;
	ushort dataushort;
	int dataint;
	uint datauint;
	float datafloat;
	double datadouble;
	QDateTime datetime;
};

#endif // MODBUSDATA_H
