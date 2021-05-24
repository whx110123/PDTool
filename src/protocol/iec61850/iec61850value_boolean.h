#ifndef IEC61850VALUE_BOOLEAN_H
#define IEC61850VALUE_BOOLEAN_H

#include "asn1bervalue.h"

class IEC61850Value_Boolean : public ASN1BERValue
{
public:
	IEC61850Value_Boolean(const MyConfig& Config);
	~IEC61850Value_Boolean();
	virtual bool init(const QByteArray& buff) override;

public:
	uchar data;

};

#endif // IEC61850VALUE_BOOLEAN_H
