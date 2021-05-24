#include "iec61850_responsedetail.h"

IEC61850_ResponseDetail::IEC61850_ResponseDetail(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ResponseDetail::~IEC61850_ResponseDetail()
{

}

void IEC61850_ResponseDetail::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Null;
	group.typeDes = "NULL";
	group.des = "otherRequests";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "CS-Status-Response";
	group.des = "CS-Status-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 45;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-GetProgramInvocationAttributes-Response";
	group.des = "CS-GetProgramInvocationAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 49;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-GetEventConditionAttributes-Response";
	group.des = "CS-GetEventConditionAttributes-Response";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ResponseDetail::CreateContextBER(uint tagNo, uint index)
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
	else
	{
		ber = CreateBERByType(myIndexMap[0].type);
		setBERGroup(ber, myIndexMap[0]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
