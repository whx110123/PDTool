#ifndef IEC61850_TYPESPECIFICATION_H
#define IEC61850_TYPESPECIFICATION_H

#include "asn1ber.h"

class IEC61850_TypeSpecification : public ASN1BER
{
public:
	IEC61850_TypeSpecification(const MyConfig& Config);
	~IEC61850_TypeSpecification();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_TYPESPECIFICATION_H
