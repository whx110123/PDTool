#include "iec61850_unconfirmed.h"
#include "iec61850_unconfirmedservice.h"

IEC61850_Unconfirmed::IEC61850_Unconfirmed(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Unconfirmed::~IEC61850_Unconfirmed()
{

}

void IEC61850_Unconfirmed::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "UnconfirmedService";
	group.des = "UnconfirmedService";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 79;
	group.type = ASN1BER::Sequence;
	group.typeDes = "Unconfirmed-Detail OPTIONAL";
	group.des = "Unconfirmed-Detail";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Unconfirmed::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(tagNo == 79)
	{
//		ber = new IEC61850_UnconfirmedDetail(mConfig);
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	else
	{
		ber = new IEC61850_UnconfirmedService(mConfig);
		setBERGroup(ber, myIndexMap[0]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
