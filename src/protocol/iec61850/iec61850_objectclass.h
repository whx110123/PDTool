#ifndef IEC61850_OBJECTCLASS_H
#define IEC61850_OBJECTCLASS_H

#include "asn1ber.h"

class IEC61850_ObjectClass : public ASN1BER
{
public:
	IEC61850_ObjectClass(const MyConfig& Config);
	~IEC61850_ObjectClass();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_OBJECTCLASS_H
