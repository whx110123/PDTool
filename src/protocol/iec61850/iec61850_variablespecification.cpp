#include "iec61850_address.h"
#include "iec61850_objectname.h"
#include "iec61850_variablespecification.h"

IEC61850_VariableSpecification::IEC61850_VariableSpecification(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_VariableSpecification::~IEC61850_VariableSpecification()
{

}

void IEC61850_VariableSpecification::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "ObjectName";
	group.des = "ObjectName";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "Address";
	group.des = "Address";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT SEQUENCE";
	group.des = "variableDescription";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT ScatteredAccessDescription";
	group.des = "scatteredAccessDescription";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT NULL";
	group.des = "invalidated";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_VariableSpecification::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 0:
			ber = new IEC61850_ObjectName(mConfig);
			break;
		case 1:
			ber = new IEC61850_Address(mConfig);
			break;
		case 2:
//			ber = new IEC61850_VariableDescription(mConfig);
			break;
		case 3:
//			ber = new IEC61850_ScatteredAccessDescription(mConfig);
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

