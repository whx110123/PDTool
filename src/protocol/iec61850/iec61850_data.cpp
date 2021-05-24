#include "iec61850_listofdata.h"
#include "iec61850_data.h"

IEC61850_Data::IEC61850_Data(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_Data::~IEC61850_Data()
{

}

void IEC61850_Data::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 1;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT SEQUENCE OF Data";
	group.des = "array";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT SEQUENCE OF Data";
	group.des = "structure";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Boolean;
	group.typeDes = "IMPLICIT BOOLEAN";
	group.des = "boolean";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::BitString;
	group.typeDes = "IMPLICIT BIT STRING";
	group.des = "bit-string";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.des = "integer";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER, -- shall not be negative";
	group.des = "unsigned";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::OctetString;
	group.typeDes = "IMPLICIT FloatingPoint";
	group.des = "floating-point";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT reserved";
	group.des = "reserved";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::OctetString;
	group.typeDes = "IMPLICIT OCTET STRING";
	group.des = "octet-string";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT VisibleString";
	group.des = "visible-string";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::GeneralizedTime;
	group.typeDes = "IMPLICIT GeneralizedTime";
	group.des = "generalized-time";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::TimeOfDay;
	group.typeDes = "IMPLICIT TimeOfDay";
	group.des = "binary-time";
	myTagNoMap.insert(tagNo, group);

	tagNo = 13;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER, -- shall not be negative";
	group.des = "bcd";
	myTagNoMap.insert(tagNo, group);

	tagNo = 14;
	group.type = ASN1BER::BitString;
	group.typeDes = "IMPLICIT BIT STRING";
	group.des = "booleanArray";
	myTagNoMap.insert(tagNo, group);

	tagNo = 15;
	group.type = ASN1BER::ObjectIdentifier;
	group.typeDes = "IMPLICIT OBJECT IDENTIFIER";
	group.des = "objId";
	myTagNoMap.insert(tagNo, group);

	tagNo = 16;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT MMSString";
	group.des = "mMSString";
	myTagNoMap.insert(tagNo, group);

	tagNo = 17;
	group.type = ASN1BER::UtcTime;
	group.typeDes = "IMPLICIT UtcTime";
	group.des = "utc-time";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Data::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_ListOfData(mConfig);
			break;
		case 2:
			ber = new IEC61850_ListOfData(mConfig);
			break;
		default:
			ber = CreateBERByType(myTagNoMap[tagNo].type);
			break;
		}
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}

