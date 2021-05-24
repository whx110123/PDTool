#ifndef IEC61850_H
#define IEC61850_H

#include "asn1ber.h"

class IEC61850MMSpdu;
class IEC61850 : public ASN1BER
{
public:
	IEC61850(const MyConfig& Config);
	~IEC61850();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_H
