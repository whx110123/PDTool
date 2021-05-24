#ifndef IEC61850_ADDRESS_H
#define IEC61850_ADDRESS_H

#include "asn1ber.h"

class IEC61850_Address : public ASN1BER
{
public:
	IEC61850_Address(const MyConfig& Config);
	~IEC61850_Address();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_ADDRESS_H
