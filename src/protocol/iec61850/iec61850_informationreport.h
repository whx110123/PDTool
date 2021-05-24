#ifndef IEC61850_INFORMATIONREPORT_H
#define IEC61850_INFORMATIONREPORT_H

#include "asn1ber.h"

class IEC61850_InformationReport : public ASN1BER
{
public:
	IEC61850_InformationReport(const MyConfig& Config);
	~IEC61850_InformationReport();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_INFORMATIONREPORT_H
