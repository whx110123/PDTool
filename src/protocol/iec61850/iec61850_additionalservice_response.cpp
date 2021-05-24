#include "iec61850_additionalservice_response.h"

IEC61850_AdditionalService_Response::IEC61850_AdditionalService_Response(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_AdditionalService_Response::~IEC61850_AdditionalService_Response()
{

}

void IEC61850_AdditionalService_Response::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT VMDStop-Response";
	group.des = "VMDStop-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT VMDReset-Response";
	group.des = "VMDReset-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Select-Response";
	group.des = "Select-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterProgramInvocationAttributes-Response";
	group.des = "AlterProgramInvocationAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitiateUnitControlLoad-Response";
	group.des = "InitiateUnitControlLoad-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT UnitControlLoadSegment-Response";
	group.des = "UnitControlLoadSegment-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT UnitControlUpload-Response";
	group.des = "UnitControlUpload-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StartUnitControl-Response";
	group.des = "StartUnitControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StopUnitControl-Response";
	group.des = "StopUnitControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CreateUnitControl-Response";
	group.des = "CreateUnitControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AddToUnitControl-Response";
	group.des = "AddToUnitControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RemoveFromUnitControl-Response";
	group.des = "RemoveFromUnitControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetUnitControlAttributes-Response";
	group.des = "GetUnitControlAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 13;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT LoadUnitControlFromFile-Response";
	group.des = "LoadUnitControlFromFile-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 14;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StoreUnitControlToFile-Response";
	group.des = "StoreUnitControlToFile-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 15;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteUnitControl-Response";
	group.des = "DeleteUnitControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 16;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventConditionList-Response";
	group.des = "DefineEventConditionList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 17;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventConditionList-Response";
	group.des = "DeleteEventConditionList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 18;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AddEventConditionListReference-Response";
	group.des = "AddEventConditionListReference-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 19;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RemoveEventConditionListReference-Response";
	group.des = "RemoveEventConditionListReference-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 20;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventConditionListAttributes-Response";
	group.des = "GetEventConditionListAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 21;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventConditionListStatus-Response";
	group.des = "ReportEventConditionListStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 22;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterEventConditionListMonitoring-Response";
	group.des = "AlterEventConditionListMonitoring-Response";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_AdditionalService_Response::CreateContextBER(uint tagNo, uint index)
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
