#include "iec61850_cancel_error.h"
#include "iec61850_serviceerror.h"

IEC61850_Cancel_Error::IEC61850_Cancel_Error(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Cancel_Error::~IEC61850_Cancel_Error()
{

}

void IEC61850_Cancel_Error::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Unsigned32";
	group.des = "originalInvokeID";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ServiceError";
	group.des = "serviceError";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Cancel_Error::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_ServiceError(mConfig);
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
