#ifndef ASN1BERVALUE_H
#define ASN1BERVALUE_H

#include "asn1ber.h"

class ASN1BERValue : public MyBase
{
public:
	ASN1BERValue(const MyConfig& Config);
	~ASN1BERValue();

	BERGroup myGroup;
};

#endif // ASN1BERVALUE_H
