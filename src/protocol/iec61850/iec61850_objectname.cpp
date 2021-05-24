#include "iec61850_domainspecific.h"
#include "iec61850_objectname.h"

IEC61850_ObjectName::IEC61850_ObjectName(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ObjectName::~IEC61850_ObjectName()
{

}

void IEC61850_ObjectName::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT Identifier";
	group.des = "vmd-specific";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT SEQUENCE";
	group.des = "domain-specific";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT Identifier";
	group.des = "aa-specific";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ObjectName::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_DomainSpecific(mConfig);
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

