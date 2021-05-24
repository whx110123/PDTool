#ifndef IEC61850VALUE_BITSTRING_H
#define IEC61850VALUE_BITSTRING_H

#include "asn1bervalue.h"

class IEC61850Value_BitString : public ASN1BERValue
{
public:
	IEC61850Value_BitString(const MyConfig& Config);
	~IEC61850Value_BitString();
	virtual bool init(const QByteArray& buff) override;

private:
	void initValueMap();
	QMap<uint, QString> valueMap;
};

#endif // IEC61850VALUE_BITSTRING_H
