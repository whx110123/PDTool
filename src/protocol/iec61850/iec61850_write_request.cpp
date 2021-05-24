#include "iec61850_listofdata.h"
#include "iec61850_variableaccessspecification.h"
#include "iec61850_write_request.h"

IEC61850_Write_Request::IEC61850_Write_Request(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Write_Request::~IEC61850_Write_Request()
{

}

void IEC61850_Write_Request::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "VariableAccessSpecification";
	group.des = "variableAccessSpecification";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT SEQUENCE OF Data";
	group.des = "listOfData";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Write_Request::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(index == 0)
	{
		ber = new IEC61850_VariableAccessSpecification(mConfig);
		setBERGroup(ber, myIndexMap[index]);
	}
	else if(tagNo == 0)
	{
		ber = new IEC61850_ListOfData(mConfig);
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}

