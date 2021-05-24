#ifndef IEC61850_UNCONFIRMED_H
#define IEC61850_UNCONFIRMED_H

#include "asn1ber.h"

class IEC61850_Unconfirmed : public ASN1BER
{
public:
	IEC61850_Unconfirmed(const MyConfig& Config);
	~IEC61850_Unconfirmed();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_UNCONFIRMED_H
