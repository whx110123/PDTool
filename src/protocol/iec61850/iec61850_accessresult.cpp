#include "iec61850_accessresult.h"
#include "iec61850_data.h"
#include "iec61850define.h"

IEC61850_AccessResult::IEC61850_AccessResult(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_AccessResult::~IEC61850_AccessResult()
{

}

void IEC61850_AccessResult::initMap()
{
	BERGroup group;

	myIndexMap.clear();

	group.index = 0;
	group.type = ASN1BER::Choice;
	group.typeDes = "Data";
	group.des = "success";
	myIndexMap.insert(group.index, group);

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT DataAccessError";
	group.typeEnum = TypeInteger::DataAccessError;
	group.des = "failure";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_AccessResult::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		ber = CreateBERByType(myTagNoMap[tagNo].type);
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	else
	{
		ber = new IEC61850_Data(mConfig);
		setBERGroup(ber, myIndexMap[0]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}

