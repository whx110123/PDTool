#include "iec61850_informationreport.h"
#include "iec61850_unconfirmedservice.h"

IEC61850_UnconfirmedService::IEC61850_UnconfirmedService(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_UnconfirmedService::~IEC61850_UnconfirmedService()
{

}

void IEC61850_UnconfirmedService::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InformationReport";
	group.des = "informationReport";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT UnsolicitedStatus";
	group.des = "unsolicitedStatus";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT EventNotification";
	group.des = "eventNotification";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_UnconfirmedService::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 0:
			ber = new IEC61850_InformationReport(mConfig);
			break;
		case 1:
//			ber = new IEC61850_StatusResponse(mConfig);
			break;
		case 2:
//			ber = new IEC61850_EventNotification(mConfig);
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
