#include "iec61850_rejectreason.h"
#include "iec61850define.h"

IEC61850_RejectReason::IEC61850_RejectReason(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_RejectReason::~IEC61850_RejectReason()
{

}

void IEC61850_RejectReason::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 1;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_confirmed_requestPDU;
	group.des = "confirmed-requestPDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_confirmed_responsePDU;
	group.des = "confirmed-responsePDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_confirmed_errorPDU;
	group.des = "confirmed-errorPDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_unconfirmedPDU;
	group.des = "unconfirmedPDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_pdu_error;
	group.des = "pdu-error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_cancel_requestPDU;
	group.des = "cancel-requestPDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_cancel_responsePDU;
	group.des = "cancel-responsePDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_cancel_errorPDU;
	group.des = "cancel-errorPDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_conclude_requestPDU;
	group.des = "conclude-requestPDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_conclude_responsePDU;
	group.des = "conclude-responsePDU";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::rejectReason_conclude_errorPDU;
	group.des = "conclude-errorPDU";
	myTagNoMap.insert(tagNo, group);

}

ASN1BER *IEC61850_RejectReason::CreateContextBER(uint tagNo, uint index)
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
