#ifndef IEC61850_LISTOFIDENTIFIER_H
#define IEC61850_LISTOFIDENTIFIER_H

#include "asn1ber.h"

class IEC61850_ListOfIdentifier : public ASN1BER
{
public:
	IEC61850_ListOfIdentifier(const MyConfig& Config);
	~IEC61850_ListOfIdentifier();
	virtual void initMap() override;
};

#endif // IEC61850_LISTOFIDENTIFIER_H
