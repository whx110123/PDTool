#ifndef IEC61850_ARRAY_TYPEDESCRIPTION_H
#define IEC61850_ARRAY_TYPEDESCRIPTION_H

#include "asn1ber.h"

class IEC61850_Array_TypeDescription : public ASN1BER
{
public:
	IEC61850_Array_TypeDescription(const MyConfig& Config);
	~IEC61850_Array_TypeDescription();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_ARRAY_TYPEDESCRIPTION_H
