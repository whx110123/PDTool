#ifndef IEC61850_WRITE_RESPONSEITEM_H
#define IEC61850_WRITE_RESPONSEITEM_H

#include "asn1ber.h"

class IEC61850_Write_ResponseItem : public ASN1BER
{
public:
	IEC61850_Write_ResponseItem(const MyConfig& Config);
	~IEC61850_Write_ResponseItem();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_WRITE_RESPONSEITEM_H
