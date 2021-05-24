#include "iec61850_informationreport.h"
#include "iec61850_listofaccessresult.h"
#include "iec61850_variableaccessspecification.h"

IEC61850_InformationReport::IEC61850_InformationReport(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_InformationReport::~IEC61850_InformationReport()
{

}

void IEC61850_InformationReport::initMap()
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
	group.typeDes = "IMPLICIT SEQUENCE OF AccessResult";
	group.des = "listOfAccessResult";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_InformationReport::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(index == 0)
	{
		ber = new IEC61850_VariableAccessSpecification(mConfig);
		setBERGroup(ber, myIndexMap[index]);
	}
	else if(tagNo == 0)
	{
		ber = new IEC61850_ListOfAccessResult(mConfig);
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
