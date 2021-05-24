#ifndef IEC61850_LISTOFVARIABLEITEM_H
#define IEC61850_LISTOFVARIABLEITEM_H

#include "asn1ber.h"

class IEC61850_ListOfVariableItem : public ASN1BER
{
public:
	IEC61850_ListOfVariableItem(const MyConfig& Config);
	~IEC61850_ListOfVariableItem();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_LISTOFVARIABLEITEM_H
