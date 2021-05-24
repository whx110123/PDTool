#ifndef IEC61850VALUE_UTCTIME_H
#define IEC61850VALUE_UTCTIME_H

#include "asn1bervalue.h"

class IEC61850Value_UtcTime : public ASN1BERValue
{
public:
	IEC61850Value_UtcTime(const MyConfig& Config);
	~IEC61850Value_UtcTime();
	virtual bool init(const QByteArray& buff) override;
};

#endif // IEC61850VALUE_UTCTIME_H
