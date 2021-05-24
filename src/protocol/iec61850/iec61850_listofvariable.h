#ifndef IEC61850_LISTOFVARIABLE_H
#define IEC61850_LISTOFVARIABLE_H

#include "asn1ber.h"

class IEC61850_ListOfVariable : public ASN1BER
{
public:
	IEC61850_ListOfVariable(const MyConfig& Config);
	~IEC61850_ListOfVariable();
	virtual void initMap() override;
	virtual ASN1BER *CreateSequenceBER(uint index) override;
};

#endif // IEC61850_LISTOFVARIABLE_H
