#ifndef IEC61850_VARIABLESPECIFICATION_H
#define IEC61850_VARIABLESPECIFICATION_H

#include "asn1ber.h"

class IEC61850_VariableSpecification : public ASN1BER
{
public:
	IEC61850_VariableSpecification(const MyConfig& Config);
	~IEC61850_VariableSpecification();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_VARIABLESPECIFICATION_H
