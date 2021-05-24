#ifndef IEC61850_DOMAINSPECIFIC_H
#define IEC61850_DOMAINSPECIFIC_H

#include "asn1ber.h"

class IEC61850_DomainSpecific : public ASN1BER
{
public:
	IEC61850_DomainSpecific(const MyConfig& Config);
	~IEC61850_DomainSpecific();
	virtual void initMap() override;
};

#endif // IEC61850_DOMAINSPECIFIC_H
