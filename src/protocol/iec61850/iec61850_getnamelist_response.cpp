#include "iec61850_getnamelist_response.h"
#include "iec61850_listofidentifier.h"

IEC61850_GetNameList_Response::IEC61850_GetNameList_Response(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_GetNameList_Response::~IEC61850_GetNameList_Response()
{

}

void IEC61850_GetNameList_Response::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT SEQUENCE OF Identifier";
	group.des = "listOfIdentifier";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Boolean;
	group.typeDes = "IMPLICIT BOOLEAN DEFAULT TRUE";
	group.des = "moreFollows";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_GetNameList_Response::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 0:
			ber = new IEC61850_ListOfIdentifier(mConfig);
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

