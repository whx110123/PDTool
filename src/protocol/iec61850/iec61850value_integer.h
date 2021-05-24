#ifndef IEC61850VALUE_INTEGER_H
#define IEC61850VALUE_INTEGER_H

#include "asn1bervalue.h"

class IEC61850Value_Integer : public ASN1BERValue
{
public:
	IEC61850Value_Integer(const MyConfig& Config);
	~IEC61850Value_Integer();
	virtual bool init(const QByteArray& buff) override;

private:
	void initValueMap();
	QMap<int, QString> valueMap;
	int intData;
	uint uintData;
};

#endif // IEC61850VALUE_INTEGER_H
