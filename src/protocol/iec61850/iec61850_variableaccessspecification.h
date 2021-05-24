#ifndef IEC61850_VARIABLEACCESSSPECIFICATION_H
#define IEC61850_VARIABLEACCESSSPECIFICATION_H

#include "asn1ber.h"

class IEC61850_VariableAccessSpecification : public ASN1BER
{
public:
	IEC61850_VariableAccessSpecification(const MyConfig& Config);
	~IEC61850_VariableAccessSpecification();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_VARIABLEACCESSSPECIFICATION_H
