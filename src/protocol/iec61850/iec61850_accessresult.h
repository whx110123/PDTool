#ifndef IEC61850_ACCESSRESULT_H
#define IEC61850_ACCESSRESULT_H

#include "asn1ber.h"

class IEC61850_AccessResult : public ASN1BER
{
public:
	IEC61850_AccessResult(const MyConfig& Config);
	~IEC61850_AccessResult();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;

};

#endif // IEC61850_ACCESSRESULT_H
