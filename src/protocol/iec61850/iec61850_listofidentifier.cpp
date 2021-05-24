#include "iec61850_listofidentifier.h"

IEC61850_ListOfIdentifier::IEC61850_ListOfIdentifier(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::SequenceOf;
}

IEC61850_ListOfIdentifier::~IEC61850_ListOfIdentifier()
{

}

void IEC61850_ListOfIdentifier::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "Identifier";
	group.des = "Identifier";
	myIndexMap.insert(group.index, group);
}
