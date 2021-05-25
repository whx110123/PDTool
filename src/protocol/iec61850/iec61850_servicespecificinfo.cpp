#include "iec61850_additionalservice_error.h"
#include "iec61850_servicespecificinfo.h"

IEC61850_ServiceSpecificInfo::IEC61850_ServiceSpecificInfo(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ServiceSpecificInfo::~IEC61850_ServiceSpecificInfo()
{

}

void IEC61850_ServiceSpecificInfo::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ObtainFile-Error";
	group.des = "ObtainFile-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Start-Error";
	group.des = "Start-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Stop-Error";
	group.des = "Stop-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Resume-Error";
	group.des = "Resume-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Reset-Error";
	group.des = "Reset-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteVariableAccess-Error";
	group.des = "DeleteVariableAccess-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteNamedVariableList-Error";
	group.des = "DeleteNamedVariableList-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteNamedType-Error";
	group.des = "DeleteNamedType-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventEnrollment-Error";
	group.des = "DefineEventEnrollment-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileRename-Error";
	group.des = "FileRename-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "AdditionalService-Error";
	group.des = "AdditionalService-Error";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ChangeAccessControl-Error";
	group.des = "ChangeAccessControl-Error";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ServiceSpecificInfo::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 10:
			ber = new IEC61850_AdditionalService_Error(mConfig);
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
