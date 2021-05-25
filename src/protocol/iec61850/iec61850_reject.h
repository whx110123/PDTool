#ifndef IEC61850_REJECT_H
#define IEC61850_REJECT_H

#include "asn1ber.h"

class IEC61850_Reject : public ASN1BER
{
public:
	IEC61850_Reject(const MyConfig& Config);
	~IEC61850_Reject();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_REJECT_H
