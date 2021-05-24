#ifndef MEASUREDTERMINAL_H
#define MEASUREDTERMINAL_H

#include "measuredterminalapci.h"
#include "measuredterminalasdu.h"

class MeasuredTerminal : public MyBase
{
public:
	MeasuredTerminal(const MyConfig& Config);
	~MeasuredTerminal();
	virtual bool init(const QByteArray& buff);

public:
	MTApci apci;
	MTAsdu asdu;
	uchar crc;
	uchar end;
};

#endif // MEASUREDTERMINAL_H
