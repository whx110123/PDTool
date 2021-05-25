#ifndef IEC61850_SERVICESPECIFICINFO_H
#define IEC61850_SERVICESPECIFICINFO_H

#include "asn1ber.h"

class IEC61850_ServiceSpecificInfo : public ASN1BER
{
public:
	IEC61850_ServiceSpecificInfo(const MyConfig& Config);
	~IEC61850_ServiceSpecificInfo();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_SERVICESPECIFICINFO_H
