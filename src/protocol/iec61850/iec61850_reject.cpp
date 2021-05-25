#include "iec61850_reject.h"
#include "iec61850_rejectreason.h"

IEC61850_Reject::IEC61850_Reject(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Reject::~IEC61850_Reject()
{

}

void IEC61850_Reject::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "CHOICE";
	group.des = "rejectReason";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Unsigned32 OPTIONAL";
	group.des = "originalInvokeID";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Reject::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		ber = CreateBERByType(myTagNoMap[tagNo].type);
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	else
	{
		ber = new IEC61850_RejectReason(mConfig);
		setBERGroup(ber, myIndexMap[0]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
