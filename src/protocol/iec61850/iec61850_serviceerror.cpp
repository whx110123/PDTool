#include "iec61850_errorclass.h"
#include "iec61850_serviceerror.h"
#include "iec61850_servicespecificinfo.h"

IEC61850_ServiceError::IEC61850_ServiceError(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_ServiceError::~IEC61850_ServiceError()
{

}

void IEC61850_ServiceError::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "CHOICE";
	group.des = "errorClass";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER OPTIONAL";
	group.des = "additionalCode";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT VisibleString OPTIONAL";
	group.des = "additionalDescription";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "CHOICE";
	group.des = "serviceSpecificInfo";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ServiceError::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 0:
			ber = new IEC61850_ErrorClass(mConfig);
			break;
		case 3:
			ber = new IEC61850_ServiceSpecificInfo(mConfig);
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
