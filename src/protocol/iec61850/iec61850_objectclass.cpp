#include "iec61850_objectclass.h"
#include "iec61850define.h"

IEC61850_ObjectClass::IEC61850_ObjectClass(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ObjectClass::~IEC61850_ObjectClass()
{

}

void IEC61850_ObjectClass::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::basicObjectClass;
	group.des = "basicObjectClass";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::csObjectClass;
	group.des = "csObjectClass";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ObjectClass::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{

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

