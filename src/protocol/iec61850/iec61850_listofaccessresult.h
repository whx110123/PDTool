#ifndef IEC61850_LISTOFACCESSRESULT_H
#define IEC61850_LISTOFACCESSRESULT_H

#include "asn1ber.h"

class IEC61850_ListOfAccessResult : public ASN1BER
{
public:
	IEC61850_ListOfAccessResult(const MyConfig& Config);
	~IEC61850_ListOfAccessResult();
	virtual void initMap() override;
	virtual ASN1BER *CreateContextBER(uint tagNo, uint index) override;
};

#endif // IEC61850_LISTOFACCESSRESULT_H
