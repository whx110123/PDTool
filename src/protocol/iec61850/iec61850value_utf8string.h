#ifndef IEC61850VALUE_UTF8STRING_H
#define IEC61850VALUE_UTF8STRING_H

#include "asn1bervalue.h"

class IEC61850Value_UTF8String : public ASN1BERValue
{
public:
	IEC61850Value_UTF8String(const MyConfig& Config);
	~IEC61850Value_UTF8String();
	virtual bool init(const QByteArray& buff) override;
private:
	QString str;
};

#endif // IEC61850VALUE_UTF8STRING_H
