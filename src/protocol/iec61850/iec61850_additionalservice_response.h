#ifndef IEC61850_ADDITIONALSERVICE_RESPONSE_H
#define IEC61850_ADDITIONALSERVICE_RESPONSE_H

#include "asn1ber.h"

class IEC61850_AdditionalService_Response : public ASN1BER
{
public:
	IEC61850_AdditionalService_Response(const MyConfig& Config);
	~IEC61850_AdditionalService_Response();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_ADDITIONALSERVICE_RESPONSE_H
