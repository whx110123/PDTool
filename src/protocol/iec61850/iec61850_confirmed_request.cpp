#include "iec61850_confirmed_request.h"
#include "iec61850_confirmedservice_request.h"
#include "iec61850_requestdetail.h"

IEC61850_Confirmed_Request::IEC61850_Confirmed_Request(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Confirmed_Request::~IEC61850_Confirmed_Request()
{

}

void IEC61850_Confirmed_Request::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "Unsigned32";
	group.des = "invokeID";
	myIndexMap.insert(group.index, group);

	group.index = 1;
	group.type = ASN1BER::Choice;
	group.typeDes = "ConfirmedServiceRequest";
	group.des = "ConfirmedServiceRequest";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 79;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "Request-Detail OPTIONAL";
	group.des = "Request-Detail";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Confirmed_Request::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(index == 0)
	{
		ber = CreateBERByType(myIndexMap[index].type);
		setBERGroup(ber, myIndexMap[index]);
	}
	else if(tagNo == 79)
	{
		ber = new IEC61850_RequestDetail(mConfig);
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	else
	{
		ber = new IEC61850_ConfirmedService_Request(mConfig);
		setBERGroup(ber, myIndexMap[1]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
