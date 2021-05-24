#include "iec61850_write_responseitem.h"

IEC61850_Write_ResponseItem::IEC61850_Write_ResponseItem(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_Write_ResponseItem::~IEC61850_Write_ResponseItem()
{

}

void IEC61850_Write_ResponseItem::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT DataAccessError";
	group.des = "failure";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT NULL";
	group.des = "success";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Write_ResponseItem::CreateContextBER(uint tagNo, uint index)
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
