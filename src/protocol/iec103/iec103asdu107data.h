#ifndef IEC103ASDU107DATA_H
#define IEC103ASDU107DATA_H

#include "iec103asdu104data.h"



class IEC103Asdu107Data : public IEC103Asdu104Data
{
public:
	IEC103Asdu107Data(const MyConfig& Config);
	~IEC103Asdu107Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC103ASDU107DATA_H
