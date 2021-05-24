#include "iec61850_array_typedescription.h"
#include "iec61850_floatingpoint.h"
#include "iec61850_structure_typedescription.h"
#include "iec61850_typedescription.h"

IEC61850_TypeDescription::IEC61850_TypeDescription(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_TypeDescription::~IEC61850_TypeDescription()
{

}

void IEC61850_TypeDescription::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT SEQUENCE";
	group.des = "array";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT SEQUENCE";
	group.des = "structure";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT NULL";
	group.des = "boolean";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer32";
	group.des = "bit-string ";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Unsigned8";
	group.des = "integer";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Unsigned8";
	group.des = "unsigned";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT SEQUENCE";
	group.des = "floating-point";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT reserved";
	group.des = "reserved";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer32";
	group.des = "octet-string";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer32";
	group.des = "visible-string";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT NULL";
	group.des = "generalized-time";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::Boolean;
	group.typeDes = "IMPLICIT BOOLEAN";
	group.des = "binary-time";
	myTagNoMap.insert(tagNo, group);

	tagNo = 13;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Unsigned8";
	group.des = "bcd";
	myTagNoMap.insert(tagNo, group);

	tagNo = 14;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT reserved";
	group.des = "reserved";
	myTagNoMap.insert(tagNo, group);

	tagNo = 15;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT NULL";
	group.des = "objId";
	myTagNoMap.insert(tagNo, group);

	tagNo = 16;
	group.type = ASN1BER::Integer;
	group.typeDes = "Integer32";
	group.des = "mMSString";
	myTagNoMap.insert(tagNo, group);

}

ASN1BER *IEC61850_TypeDescription::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_Array_TypeDescription(mConfig);
			break;
		case 2:
			ber = new IEC61850_Structure_TypeDescription(mConfig);
			break;
		case 7:
			ber = new IEC61850_FloatingPoint(mConfig);
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
