#include "iec61850_objectscope.h"

IEC61850_ObjectScope::IEC61850_ObjectScope(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ObjectScope::~IEC61850_ObjectScope()
{

}

void IEC61850_ObjectScope::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT NULL ";
	group.des = "vmdSpecific";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::VisibleString;
	group.typeDes = "IMPLICIT Identifier";
	group.des = "domainSpecific";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT NULL";
	group.des = "aaSpecific";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ObjectScope::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{

		default:
			ber = CreateBERByType(myTagNoMap[tagNo].type);
			break;
		}
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	return ber;
}
