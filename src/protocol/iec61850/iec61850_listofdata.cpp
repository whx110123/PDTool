#include "iec61850_listofdata.h"
#include "iec61850_data.h"

IEC61850_ListOfData::IEC61850_ListOfData(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::SequenceOf;
}

IEC61850_ListOfData::~IEC61850_ListOfData()
{

}

void IEC61850_ListOfData::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "Data";
	group.des = "Data";
	myIndexMap.insert(group.index, group);
}

ASN1BER *IEC61850_ListOfData::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	ber = new IEC61850_Data(mConfig);
	setBERGroup(ber, myIndexMap[0]);
	return ber;
}



