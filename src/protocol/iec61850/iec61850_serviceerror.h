#ifndef IEC61850_SERVICEERROR_H
#define IEC61850_SERVICEERROR_H

#include "asn1ber.h"

class IEC61850_ServiceError : public ASN1BER
{
public:
	IEC61850_ServiceError(const MyConfig& Config);
	~IEC61850_ServiceError();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_SERVICEERROR_H
