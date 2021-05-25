#include "iec61850_additionalservice_error.h"

IEC61850_AdditionalService_Error::IEC61850_AdditionalService_Error(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_AdditionalService_Error::~IEC61850_AdditionalService_Error()
{

}

void IEC61850_AdditionalService_Error::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "DefineEventConditionList-Error";
	group.des = "DefineEventConditionList-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "AddEventConditionListReference-Error";
	group.des = "AddEventConditionListReference-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "RemoveEventConditionListReference-Error";
	group.des = "RemoveEventConditionListReference-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Sequence;
	group.typeDes = "InitiateUnitControl-Error";
	group.des = "InitiateUnitControl-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StartUnitControl-Error";
	group.des = "StartUnitControl-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StopUnitControl-Error";
	group.des = "StopUnitControl-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Sequence;
	group.typeDes = "DeleteUnitControl-Error";
	group.des = "DeleteUnitControl-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "LoadUnitControlFromFile-Error";
	group.des = "LoadUnitControlFromFile-Error";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_AdditionalService_Error::CreateContextBER(uint tagNo, uint index)
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
