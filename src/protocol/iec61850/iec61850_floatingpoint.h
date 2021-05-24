#ifndef IEC61850_FLOATINGPOINT_H
#define IEC61850_FLOATINGPOINT_H

#include "asn1ber.h"

class IEC61850_FloatingPoint : public ASN1BER
{
public:
	IEC61850_FloatingPoint(const MyConfig& Config);
	~IEC61850_FloatingPoint();
	virtual void initMap() override;
};

#endif // IEC61850_FLOATINGPOINT_H
