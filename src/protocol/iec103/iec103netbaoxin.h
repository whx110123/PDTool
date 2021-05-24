#ifndef IEC103NETBAOXIN_H
#define IEC103NETBAOXIN_H

#include "iec103asdu.h"
#include <iec104apci.h>

class IEC103NetBaoXin : public MyBase
{
public:
	IEC103NetBaoXin(const MyConfig& Config);
	~IEC103NetBaoXin();
	virtual bool init(const QByteArray& buff);

public:
	IEC104Apci apci;
	IEC103Asdu asdu;

};

#endif // IEC103NETBAOXIN_H
