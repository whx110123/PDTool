#include "iec61850_initdetail_response.h"
#include "iec61850define.h"

IEC61850_InitDetail_Response::IEC61850_InitDetail_Response(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_InitDetail_Response::~IEC61850_InitDetail_Response()
{

}

void IEC61850_InitDetail_Response::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer16";
	group.des = "negotiatedVersionNumber";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::BitString;
	group.typeDes = "IMPLICIT ParameterSupportOptions";
	group.typeEnum = TypeBitString::ParameterSupportOptions;
	group.des = "negotiatedParameterCBB";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::BitString;
	group.typeDes = "IMPLICIT ServiceSupportOptions";
	group.typeEnum = TypeBitString::ServiceSupportOptions;
	group.des = "servicesSupportedCalled";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::BitString;
	group.typeDes = "IMPLICIT AdditionalSupportOptions";
	group.typeEnum = TypeBitString::AdditionalSupportOptions;
	group.des = "additionalSupportedCalled";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::BitString;
	group.typeDes = "IMPLICIT AdditionalCBBOptions";
	group.typeEnum = TypeBitString::AdditionalCBBOptions;
	group.des = "additionalCbbSupportedCalled";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT VisibleString";
	group.des = "privilegeClassIdentityCalled";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_InitDetail_Response::CreateContextBER(uint tagNo, uint index)
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


