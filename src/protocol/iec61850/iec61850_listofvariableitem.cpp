#include "iec61850_listofvariableitem.h"
#include "iec61850_variablespecification.h"

IEC61850_ListOfVariableItem::IEC61850_ListOfVariableItem(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_ListOfVariableItem::~IEC61850_ListOfVariableItem()
{

}

void IEC61850_ListOfVariableItem::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "VariableSpecification";
	group.des = "variableSpecification";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 5;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT AlternateAccess OPTIONAL";
	group.des = "alternateAccess";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ListOfVariableItem::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	switch(tagNo)
	{
	case 5:
//		ber = new IEC61850_AlternateAccess(mConfig);
		setBERGroup(ber, myTagNoMap[tagNo]);
		break;
	default:
		ber = new IEC61850_VariableSpecification(mConfig);
		setBERGroup(ber, myIndexMap[0]);
		break;
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
