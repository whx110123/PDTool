#include "iec61850_additionalservice_request.h"

IEC61850_AdditionalService_Request::IEC61850_AdditionalService_Request(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_AdditionalService_Request::~IEC61850_AdditionalService_Request()
{

}

void IEC61850_AdditionalService_Request::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT VMDStop-Request";
	group.des = "VMDStop-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT VMDReset-Request";
	group.des = "VMDReset-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Select-Request";
	group.des = "Select-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterProgramInvocationAttributes-Request";
	group.des = "AlterProgramInvocationAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitiateUnitControlLoad-Request";
	group.des = "InitiateUnitControlLoad-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT UnitControlLoadSegment-Request";
	group.des = "UnitControlLoadSegment-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT UnitControlUpload-Request";
	group.des = "UnitControlUpload-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StartUnitControl-Request";
	group.des = "StartUnitControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StopUnitControl-Request";
	group.des = "StopUnitControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CreateUnitControl-Request";
	group.des = "CreateUnitControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AddToUnitControl-Request";
	group.des = "AddToUnitControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RemoveFromUnitControl-Request";
	group.des = "RemoveFromUnitControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetUnitControlAttributes-Request";
	group.des = "GetUnitControlAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 13;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT LoadUnitControlFromFile-Request";
	group.des = "LoadUnitControlFromFile-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 14;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StoreUnitControlToFile-Request";
	group.des = "StoreUnitControlToFile-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 15;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteUnitControl-Request";
	group.des = "DeleteUnitControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 16;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventConditionList-Request";
	group.des = "DefineEventConditionList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 17;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventConditionList-Request";
	group.des = "DeleteEventConditionList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 18;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AddEventConditionListReference-Request";
	group.des = "AddEventConditionListReference-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 19;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RemoveEventConditionListReference-Request";
	group.des = "RemoveEventConditionListReference-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 20;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventConditionListAttributes-Request";
	group.des = "GetEventConditionListAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 21;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventConditionListStatus-Request";
	group.des = "ReportEventConditionListStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 22;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterEventConditionListMonitoring-Request";
	group.des = "AlterEventConditionListMonitoring-Request";
	myTagNoMap.insert(tagNo, group);

}

ASN1BER *IEC61850_AdditionalService_Request::CreateContextBER(uint tagNo, uint index)
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
