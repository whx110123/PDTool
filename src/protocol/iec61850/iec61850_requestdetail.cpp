#include "iec61850_requestdetail.h"

IEC61850_RequestDetail::IEC61850_RequestDetail(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_RequestDetail::~IEC61850_RequestDetail()
{

}

void IEC61850_RequestDetail::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Null;
	group.typeDes = "NULL";
	group.des = "otherRequests";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 38;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-CreateProgramInvocation-Request";
	group.des = "CS-CreateProgramInvocation-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 40;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-Start-Request";
	group.des = "CS-Start-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 42;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-Resume-Request";
	group.des = "CS-Resume-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 47;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-DefineEventCondition-Request";
	group.des = "CS-DefineEventCondition-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 51;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-AlterEventConditionMonitoring-Request";
	group.des = "CS-AlterEventConditionMonitoring-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 57;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-DefineEventEnrollment-Request";
	group.des = "CS-DefineEventEnrollment-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 59;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CS-AlterEventEnrollment-Request";
	group.des = "CS-AlterEventEnrollment-Request";
	myTagNoMap.insert(tagNo, group);

}

ASN1BER *IEC61850_RequestDetail::CreateContextBER(uint tagNo, uint index)
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
