#include "iec61850.h"
#include "iec61850_confirmed_error.h"
#include "iec61850_confirmed_request.h"
#include "iec61850_confirmed_response.h"
#include "iec61850_initiate_request.h"
#include "iec61850_initiate_response.h"
#include "iec61850_unconfirmed.h"

IEC61850::IEC61850(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
	myGroup.typeDes = "MMSpdu";
	myGroup.des = "MMSpdu";
}

IEC61850::~IEC61850()
{

}


void IEC61850::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Confirmed-RequestPDU";
	group.des = "Confirmed_Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Confirmed-ResponsePDU";
	group.des = "Confirmed_Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Confirmed-ErrorPDU";
	group.des = "Confirmed_Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Unconfirmed-PDU";
	group.des = "Unconfirmed";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RejectPDU";
	group.des = "reject";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Cancel-RequestPDU";
	group.des = "Cancel_Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Cancel-ResponsePDU";
	group.des = "Cancel_Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Cancel-ErrorPDU";
	group.des = "Cancel_Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Initiate-RequestPDU";
	group.des = "Initiate_Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Initiate-ResponsePDU";
	group.des = "Initiate_Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Initiate-ErrorPDU";
	group.des = "Initiate_Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Conclude-RequestPDU";
	group.des = "Conclude_Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Conclude-ResponsePDU";
	group.des = "Conclude_Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 13;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Conclude-ErrorPDU";
	group.des = "Conclude_Error";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber  = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 0:
			ber = new IEC61850_Confirmed_Request(mConfig);
			break;
		case 1:
			ber = new IEC61850_Confirmed_Response(mConfig);
			break;
		case 2:
			ber = new IEC61850_Confirmed_Error(mConfig);
			break;
		case 3:
			ber = new IEC61850_Unconfirmed(mConfig);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			ber = new IEC61850_Initiate_Request(mConfig);
			break;
		case 9:
			ber = new IEC61850_Initiate_Response(mConfig);
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		default:
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


