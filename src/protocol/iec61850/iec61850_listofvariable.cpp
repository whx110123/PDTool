#include "iec61850_listofvariable.h"
#include "iec61850_listofvariableitem.h"

IEC61850_ListOfVariable::IEC61850_ListOfVariable(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::SequenceOf;
}

IEC61850_ListOfVariable::~IEC61850_ListOfVariable()
{

}

void IEC61850_ListOfVariable::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "ListOfVariableItem";
	group.des = "ListOfVariableItem";
	myIndexMap.insert(group.index, group);

}

ASN1BER *IEC61850_ListOfVariable::CreateSequenceBER(uint index)
{
	ASN1BER *ber = NULL;
	ber = new IEC61850_ListOfVariableItem(mConfig);
	setBERGroup(ber, myIndexMap[0]);
	return ber;
}



