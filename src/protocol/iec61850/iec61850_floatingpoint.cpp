#include "iec61850_floatingpoint.h"

IEC61850_FloatingPoint::IEC61850_FloatingPoint(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_FloatingPoint::~IEC61850_FloatingPoint()
{

}

void IEC61850_FloatingPoint::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "Unsigned8";
	group.des = "format-width";
	myIndexMap.insert(group.index, group);

	group.index = 1;
	group.type = ASN1BER::Integer;
	group.typeDes = "Unsigned8";
	group.des = "exponent-width";
	myIndexMap.insert(group.index, group);
}
