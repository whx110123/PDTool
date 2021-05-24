#include "iec61850_address.h"

IEC61850_Address::IEC61850_Address(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_Address::~IEC61850_Address()
{

}

void IEC61850_Address::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Unsigned32";
	group.des = "numericAddress";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "MMSString";
	group.des = "symbolicAddress";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::OctetString;
	group.typeDes = "IMPLICIT OCTET STRING";
	group.des = "unconstrainedAddress";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Address::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		ber = CreateBERByType(myTagNoMap[tagNo].type);

		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}

