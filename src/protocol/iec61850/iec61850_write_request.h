#ifndef IEC61850_WRITE_REQUEST_H
#define IEC61850_WRITE_REQUEST_H

#include "asn1ber.h"

class IEC61850_Write_Request : public ASN1BER
{
public:
	IEC61850_Write_Request(const MyConfig& Config);
	~IEC61850_Write_Request();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_WRITE_REQUEST_H
