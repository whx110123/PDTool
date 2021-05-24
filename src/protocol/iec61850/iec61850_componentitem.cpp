#include "iec61850_componentitem.h"
#include "iec61850_typespecification.h"

IEC61850_ComponentItem::IEC61850_ComponentItem(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_ComponentItem::~IEC61850_ComponentItem()
{

}

void IEC61850_ComponentItem::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT Identifier OPTIONAL";
	group.des = "componentName";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "TypeSpecification";
	group.des = "componentType";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ComponentItem::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
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
