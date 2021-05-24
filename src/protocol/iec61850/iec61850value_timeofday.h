#ifndef IEC61850VALUE_TIMEOFDAY_H
#define IEC61850VALUE_TIMEOFDAY_H

#include "asn1bervalue.h"

class IEC61850Value_TimeOfDay : public ASN1BERValue
{
public:
	IEC61850Value_TimeOfDay(const MyConfig& Config);
	~IEC61850Value_TimeOfDay();
	virtual bool init(const QByteArray& buff) override;
};

#endif // IEC61850VALUE_TIMEOFDAY_H
