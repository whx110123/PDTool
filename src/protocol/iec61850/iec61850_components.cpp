#include "iec61850_componentitem.h"
#include "iec61850_components.h"

IEC61850_Components::IEC61850_Components(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::SequenceOf;
}

IEC61850_Components::~IEC61850_Components()
{

}

void IEC61850_Components::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "ComponentItem";
	group.des = "ComponentItem";
	myIndexMap.insert(group.index, group);
}

ASN1BER *IEC61850_Components::CreateSequenceBER(uint index)
{
	ASN1BER *ber = NULL;
	ber = new IEC61850_ComponentItem(mConfig);
	setBERGroup(ber, myIndexMap[0]);
	return ber;
}



