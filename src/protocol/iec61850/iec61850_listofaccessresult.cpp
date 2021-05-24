#include "iec61850_accessresult.h"
#include "iec61850_listofaccessresult.h"

IEC61850_ListOfAccessResult::IEC61850_ListOfAccessResult(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::SequenceOf;
}

IEC61850_ListOfAccessResult::~IEC61850_ListOfAccessResult()
{

}

void IEC61850_ListOfAccessResult::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "AccessResult";
	group.des = "AccessResult";
	myIndexMap.insert(group.index, group);
}

ASN1BER *IEC61850_ListOfAccessResult::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	ber = new IEC61850_AccessResult(mConfig);
	setBERGroup(ber, myIndexMap[0]);
	return ber;
}


