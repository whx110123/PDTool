#ifndef IEC61850_RESPONSEDETAIL_H
#define IEC61850_RESPONSEDETAIL_H

#include "asn1ber.h"

class IEC61850_ResponseDetail : public ASN1BER
{
public:
	IEC61850_ResponseDetail(const MyConfig& Config);
	~IEC61850_ResponseDetail();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_RESPONSEDETAIL_H
