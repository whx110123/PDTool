#ifndef IEC61850_REJECTREASON_H
#define IEC61850_REJECTREASON_H

#include "asn1ber.h"

class IEC61850_RejectReason : public ASN1BER
{
public:
	IEC61850_RejectReason(const MyConfig& Config);
	~IEC61850_RejectReason();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_REJECTREASON_H
