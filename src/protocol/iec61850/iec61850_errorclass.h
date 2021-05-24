#ifndef IEC61850_ERRORCLASS_H
#define IEC61850_ERRORCLASS_H

#include "asn1ber.h"

class IEC61850_ErrorClass : public ASN1BER
{
public:
	IEC61850_ErrorClass(const MyConfig& Config);
	~IEC61850_ErrorClass();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_ERRORCLASS_H
