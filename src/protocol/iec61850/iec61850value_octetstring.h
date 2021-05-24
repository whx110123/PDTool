#ifndef IEC61850VALUE_OCTETSTRING_H
#define IEC61850VALUE_OCTETSTRING_H

#include "asn1bervalue.h"

class IEC61850Value_OctetString : public ASN1BERValue
{
public:
	IEC61850Value_OctetString(const MyConfig& Config);
	~IEC61850Value_OctetString();
	virtual bool init(const QByteArray& buff) override;
};

#endif // IEC61850VALUE_OCTETSTRING_H
