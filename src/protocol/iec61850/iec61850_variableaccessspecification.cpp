#include "iec61850_listofvariable.h"
#include "iec61850_objectname.h"
#include "iec61850_variableaccessspecification.h"

IEC61850_VariableAccessSpecification::IEC61850_VariableAccessSpecification(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_VariableAccessSpecification::~IEC61850_VariableAccessSpecification()
{

}

void IEC61850_VariableAccessSpecification::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT SEQUENCE OF SEQUENCE";
	group.des = "listOfVariable";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "ObjectName";
	group.des = "variableListName";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_VariableAccessSpecification::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 0:
			ber = new IEC61850_ListOfVariable(mConfig);
			break;
		case 1:
			ber = new IEC61850_ObjectName(mConfig);
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

