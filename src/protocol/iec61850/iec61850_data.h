#ifndef IEC61850_DATA_H
#define IEC61850_DATA_H

#include "asn1ber.h"

class IEC61850_Data : public ASN1BER
{
public:
	IEC61850_Data(const MyConfig& Config);
	~IEC61850_Data();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_DATA_H
