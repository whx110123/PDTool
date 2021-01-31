#ifndef IEC101ASDU102DATA_H
#define IEC101ASDU102DATA_H

#include "iec101asdu.h"



class IEC101Asdu102Data : public IEC101AsduData
{
public:
	IEC101Asdu102Data(const MyConfig& Config);
	~IEC101Asdu102Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC101ASDU102DATA_H
