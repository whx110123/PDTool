#include "iec61850_address.h"
#include "iec61850_getvariableaccessattributes_response.h"
#include "iec61850_typedescription.h"

IEC61850_GetVariableAccessAttributes_Response::IEC61850_GetVariableAccessAttributes_Response(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_GetVariableAccessAttributes_Response::~IEC61850_GetVariableAccessAttributes_Response()
{

}

void IEC61850_GetVariableAccessAttributes_Response::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Boolean;
	group.typeDes = "IMPLICIT BOOLEAN";
	group.des = "mmsDeletable";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "Address";
	group.des = "Address";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "TypeDescription";
	group.des = "typeDescription";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT Identifier OPTIONAL";
	group.des = "accessControlList";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT VisibleString OPTIONAL";
	group.des = "meaning";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_GetVariableAccessAttributes_Response::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_Address(mConfig);
			break;
		case 2:
			ber = new IEC61850_TypeDescription(mConfig);
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

