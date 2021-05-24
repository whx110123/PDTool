#include "iec61850_errorclass.h"
#include "iec61850define.h"

IEC61850_ErrorClass::IEC61850_ErrorClass(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ErrorClass::~IEC61850_ErrorClass()
{

}

void IEC61850_ErrorClass::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::vmd_state;
	group.des = "vmd-state";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::application_reference;
	group.des = "application-reference";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::definition;
	group.des = "definition";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::resource;
	group.des = "resource";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::service;
	group.des = "service";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::service_preempt;
	group.des = "service-preempt";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::time_resolution;
	group.des = "time-resolution";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::access;
	group.des = "access";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::initiate;
	group.des = "initiate";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::conclude;
	group.des = "conclude";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Null;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::cancel;
	group.des = "cancel";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.typeEnum = TypeInteger::file;
	group.des = "file";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::Integer;
	group.typeDes = "IMPLICIT INTEGER";
	group.des = "others";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ErrorClass::CreateContextBER(uint tagNo, uint index)
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
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
