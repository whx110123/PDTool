#include "asn1ber.h"
#include "asn1bervalue.h"

ASN1BERValue::ASN1BERValue(const MyConfig& Config): MyBase(Config)
{
	myGroup.type = ASN1BER::EndOfContents;
}

ASN1BERValue::~ASN1BERValue()
{

}

