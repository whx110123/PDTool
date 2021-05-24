#ifndef IEC61850_OBJECTNAME_H
#define IEC61850_OBJECTNAME_H

#include "asn1ber.h"

class IEC61850_ObjectName : public ASN1BER
{
public:
	IEC61850_ObjectName(const MyConfig& Config);
	~IEC61850_ObjectName();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_OBJECTNAME_H
