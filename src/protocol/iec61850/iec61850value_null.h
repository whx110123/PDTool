#ifndef IEC61850VALUE_NULL_H
#define IEC61850VALUE_NULL_H

#include "asn1bervalue.h"

class IEC61850Value_Null : public ASN1BERValue
{
public:
	IEC61850Value_Null(const MyConfig& Config);
	~IEC61850Value_Null();
	virtual bool init(const QByteArray& buff) override;
};

#endif // IEC61850VALUE_NULL_H
