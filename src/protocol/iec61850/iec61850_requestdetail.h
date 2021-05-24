#ifndef IEC61850_REQUESTDETAIL_H
#define IEC61850_REQUESTDETAIL_H

#include "asn1ber.h"

class IEC61850_RequestDetail : public ASN1BER
{
public:
	IEC61850_RequestDetail(const MyConfig& Config);
	~IEC61850_RequestDetail();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_REQUESTDETAIL_H
