#ifndef IEC61850_COMPONENTS_H
#define IEC61850_COMPONENTS_H

#include "asn1ber.h"

class IEC61850_Components : public ASN1BER
{
public:
	IEC61850_Components(const MyConfig& Config);
	~IEC61850_Components();
	virtual void initMap() override;
	virtual ASN1BER *CreateSequenceBER(uint index) override;
};

#endif // IEC61850_COMPONENTS_H
