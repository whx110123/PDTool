﻿#ifndef IEC61850_UNCONFIRMEDSERVICE_H
#define IEC61850_UNCONFIRMEDSERVICE_H

#include "asn1ber.h"

class IEC61850_UnconfirmedService : public ASN1BER
{
public:
	IEC61850_UnconfirmedService(const MyConfig& Config);
	~IEC61850_UnconfirmedService();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_UNCONFIRMEDSERVICE_H
