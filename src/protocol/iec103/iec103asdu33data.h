#ifndef IEC103ASDU33DATA_H
#define IEC103ASDU33DATA_H

#include "iec103asdu32data.h"



class IEC103Asdu33Data : public IEC103Asdu32Data
{
public:
	IEC103Asdu33Data(const MyConfig& Config);
	~IEC103Asdu33Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC103ASDU33DATA_H
