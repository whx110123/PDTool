#include "iec61850_array_typedescription.h"
#include "iec61850_typespecification.h"

IEC61850_Array_TypeDescription::IEC61850_Array_TypeDescription(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Array_TypeDescription::~IEC61850_Array_TypeDescription()
{

}

void IEC61850_Array_TypeDescription::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Boolean;
	group.typeDes = "IMPLICIT BOOLEAN DEFAULT FALSE";
	group.des = "packed";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Unsigned32";
	group.des = "numberOfElements";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "TypeSpecification";
	group.des = "elementType";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Array_TypeDescription::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 2:
			ber = new IEC61850_TypeSpecification(mConfig);
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

