#ifndef IEC101ASDU111DATA_H
#define IEC101ASDU111DATA_H

#include "iec101asdu110data.h"



class IEC101Asdu111Data : public IEC101Asdu110Data
{
public:
	IEC101Asdu111Data(const MyConfig& Config);
	~IEC101Asdu111Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC101ASDU111DATA_H
