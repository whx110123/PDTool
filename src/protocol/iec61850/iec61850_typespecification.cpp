#include "iec61850_objectname.h"
#include "iec61850_typedescription.h"
#include "iec61850_typespecification.h"

IEC61850_TypeSpecification::IEC61850_TypeSpecification(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_TypeSpecification::~IEC61850_TypeSpecification()
{

}

void IEC61850_TypeSpecification::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "TypeDescription";
	group.des = "typeDescription";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "ObjectName";
	group.des = "typeName";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_TypeSpecification::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(tagNo == 0)
	{
		ber = new IEC61850_ObjectName(mConfig);
		setBERGroup(ber, myTagNoMap[0]);
	}
	else
	{
		ber = new IEC61850_TypeDescription(mConfig);
		setBERGroup(ber, myIndexMap[0]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
