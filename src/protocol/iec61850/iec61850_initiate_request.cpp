#include "iec61850_initiate_request.h"
#include "iec61850_initdetail_request.h"

IEC61850_Initiate_Request::IEC61850_Initiate_Request(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Initiate_Request::~IEC61850_Initiate_Request()
{

}

void IEC61850_Initiate_Request::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer32 OPTIONAL";
	group.des = "localDetailCalling";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer16";
	group.des = "proposedMaxServOutstandingCalling";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer16";
	group.des = "proposedMaxServOutstandingCalled";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT Integer8 OPTIONAL";
	group.des = "proposedDataStructureNestingLevel";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Sequence";
	group.des = "initRequestDetail";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Initiate_Request::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 4:
			ber = new IEC61850_InitDetail_Request(mConfig);
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


