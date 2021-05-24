#include "iec61850_write_response.h"
#include "iec61850_write_responseitem.h"

IEC61850_Write_Response::IEC61850_Write_Response(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::SequenceOf;
}

IEC61850_Write_Response::~IEC61850_Write_Response()
{

}

void IEC61850_Write_Response::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "WriteResponseItem";
	group.des = "WriteResponseItem";
	myIndexMap.insert(group.index, group);
}

ASN1BER *IEC61850_Write_Response::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	ber = new IEC61850_Write_ResponseItem(mConfig);
	setBERGroup(ber, myIndexMap[0]);
	return ber;
}
