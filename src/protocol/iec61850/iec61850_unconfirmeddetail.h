#ifndef IEC61850_UNCONFIRMEDDETAIL_H
#define IEC61850_UNCONFIRMEDDETAIL_H

#include "asn1ber.h"

class IEC61850_UnconfirmedDetail : public ASN1BER
{
public:
	IEC61850_UnconfirmedDetail(const MyConfig& Config);
	~IEC61850_UnconfirmedDetail();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_UNCONFIRMEDDETAIL_H
