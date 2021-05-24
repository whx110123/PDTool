#include "iec61850_components.h"
#include "iec61850_structure_typedescription.h"

IEC61850_Structure_TypeDescription::IEC61850_Structure_TypeDescription(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Sequence;
}

IEC61850_Structure_TypeDescription::~IEC61850_Structure_TypeDescription()
{

}

void IEC61850_Structure_TypeDescription::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	uint tagNo = 0;
	group.type = ASN1BER::Boolean;
	group.typeDes = "IMPLICIT BOOLEAN DEFAULT FALSE";
	group.des = "packed";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::SequenceOf;
	group.typeDes = "IMPLICIT SEQUENCE OF SEQUENCE";
	group.des = "components";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_Structure_TypeDescription::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_Components(mConfig);
			break;
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

