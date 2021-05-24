#ifndef IEC61850_LISTOFDATA_H
#define IEC61850_LISTOFDATA_H

#include "asn1ber.h"

class IEC61850_ListOfData : public ASN1BER
{
public:
	IEC61850_ListOfData(const MyConfig& Config);
	~IEC61850_ListOfData();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_LISTOFDATA_H
