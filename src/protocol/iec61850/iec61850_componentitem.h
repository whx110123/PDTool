#ifndef IEC61850_COMPONENTITEM_H
#define IEC61850_COMPONENTITEM_H

#include "asn1ber.h"

class IEC61850_ComponentItem : public ASN1BER
{
public:
	IEC61850_ComponentItem(const MyConfig& Config);
	~IEC61850_ComponentItem();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_COMPONENTITEM_H
