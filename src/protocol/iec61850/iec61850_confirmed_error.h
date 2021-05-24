#ifndef IEC61850_CONFIRMED_ERROR_H
#define IEC61850_CONFIRMED_ERROR_H

#include "asn1ber.h"

class IEC61850_Confirmed_Error : public ASN1BER
{
public:
	IEC61850_Confirmed_Error(const MyConfig& Config);
	~IEC61850_Confirmed_Error();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_CONFIRMED_ERROR_H
