#include "iec61850_domainspecific.h"

IEC61850_DomainSpecific::IEC61850_DomainSpecific(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_DomainSpecific::~IEC61850_DomainSpecific()
{

}

void IEC61850_DomainSpecific::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "Identifier";
	group.des = "domainID";
	myIndexMap.insert(group.index, group);

	group.index = 1;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "Identifier";
	group.des = "itemID";
	myIndexMap.insert(group.index, group);
}
