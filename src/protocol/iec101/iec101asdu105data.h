#ifndef IEC101ASDU105DATA_H
#define IEC101ASDU105DATA_H

#include "iec101asdu.h"



class IEC101Asdu105Data : public IEC101AsduData
{
public:
	IEC101Asdu105Data(const MyConfig& Config);
	~IEC101Asdu105Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar grp;
};

#endif // IEC101ASDU105DATA_H
