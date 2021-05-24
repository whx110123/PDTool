#include "iec61850value_integer.h"

IEC61850Value_Integer::IEC61850Value_Integer(const MyConfig& Config): ASN1BERValue(Config)
{

}

IEC61850Value_Integer::~IEC61850Value_Integer()
{

}

bool IEC61850Value_Integer::init(const QByteArray& buff)
{
	setDefault(buff);
	initValueMap();
	uchar length = buff.length();
	if(myGroup.typeDes.contains("Unsigned", Qt::CaseInsensitive))
	{
		uintData = charTouint(buff.data() + mLen, length, 1);
		mText.append(CharToHexStr(buff.data() + mLen, length) + "\t" + QString::number(uintData) + "  " + valueMap[uintData] + "\r\n");
	}
	else
	{
		intData = charToint(buff.data() + mLen, length, 1);
		mText.append(CharToHexStr(buff.data() + mLen, length) + "\t" + QString::number(intData) + "  " + valueMap[intData] + "\r\n");
	}

	mText.append("----------------------------------------\r\n");
	mLen += length;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

void IEC61850Value_Integer::initValueMap()
{
	valueMap.clear();
	//初始化
	{
		valueMap.insert(0, "");
		valueMap.insert(1, "");
		valueMap.insert(2, "");
		valueMap.insert(3, "");
		valueMap.insert(4, "");
		valueMap.insert(5, "");
		valueMap.insert(6, "");
		valueMap.insert(7, "");
		valueMap.insert(8, "");
		valueMap.insert(9, "");
		valueMap.insert(10, "");
		valueMap.insert(11, "");
		valueMap.insert(12, "");
		valueMap.insert(13, "");
		valueMap.insert(14, "");
		valueMap.insert(15, "");
		valueMap.insert(16, "");
		valueMap.insert(17, "");
		valueMap.insert(18, "");
		valueMap.insert(19, "");
		valueMap.insert(20, "");
		valueMap.insert(21, "");
		valueMap.insert(22, "");
		valueMap.insert(23, "");
		valueMap.insert(24, "");
		valueMap.insert(25, "");
		valueMap.insert(26, "");
		valueMap.insert(27, "");
		valueMap.insert(28, "");
		valueMap.insert(29, "");
		valueMap.insert(30, "");
		valueMap.insert(31, "");
		valueMap.insert(32, "");
		valueMap.insert(33, "");
		valueMap.insert(34, "");
		valueMap.insert(35, "");
		valueMap.insert(36, "");
		valueMap.insert(37, "");
		valueMap.insert(38, "");
		valueMap.insert(39, "");
		valueMap.insert(40, "");
		valueMap.insert(41, "");
		valueMap.insert(42, "");
		valueMap.insert(43, "");
		valueMap.insert(44, "");
		valueMap.insert(45, "");
		valueMap.insert(46, "");
		valueMap.insert(47, "");
		valueMap.insert(48, "");
		valueMap.insert(49, "");
		valueMap.insert(50, "");
		valueMap.insert(51, "");
		valueMap.insert(52, "");
		valueMap.insert(53, "");
		valueMap.insert(54, "");
		valueMap.insert(55, "");
		valueMap.insert(56, "");
		valueMap.insert(57, "");
		valueMap.insert(58, "");
		valueMap.insert(59, "");
		valueMap.insert(60, "");
		valueMap.insert(61, "");
		valueMap.insert(62, "");
		valueMap.insert(63, "");
		valueMap.insert(64, "");
		valueMap.insert(65, "");
		valueMap.insert(66, "");
		valueMap.insert(67, "");
		valueMap.insert(68, "");
		valueMap.insert(69, "");
		valueMap.insert(70, "");
		valueMap.insert(71, "");
		valueMap.insert(72, "");
		valueMap.insert(73, "");
		valueMap.insert(74, "");
		valueMap.insert(75, "");
		valueMap.insert(76, "");
		valueMap.insert(77, "");
		valueMap.insert(78, "");
		valueMap.insert(79, "");
		valueMap.insert(80, "");
		valueMap.insert(81, "");
		valueMap.insert(82, "");
		valueMap.insert(83, "");
		valueMap.insert(84, "");
		valueMap.insert(85, "");
		valueMap.insert(86, "");
		valueMap.insert(87, "");
		valueMap.insert(88, "");
		valueMap.insert(89, "");
		valueMap.insert(90, "");
		valueMap.insert(91, "");
		valueMap.insert(92, "");
		valueMap.insert(93, "");
		valueMap.insert(94, "");
		valueMap.insert(95, "");
		valueMap.insert(96, "");
		valueMap.insert(97, "");
		valueMap.insert(98, "");
		valueMap.insert(99, "");
	}
	if(myGroup.des.contains("basicObjectClass"))
	{
		valueMap.insert(0, "namedVariable");
		valueMap.insert(1, "scatteredAccess");
		valueMap.insert(2, "namedVariableList");
		valueMap.insert(3, "namedType");
		valueMap.insert(4, "semaphore");
		valueMap.insert(5, "eventCondition");
		valueMap.insert(6, "eventAction");
		valueMap.insert(7, "eventEnrollment");
		valueMap.insert(8, "journal");
		valueMap.insert(9, "domain");
		valueMap.insert(10, "programInvocation");
		valueMap.insert(11, "operatorStation");
		valueMap.insert(12, "dataExchange");
		valueMap.insert(13, "accessControlList");
	}
	else if(myGroup.des.contains("csObjectClass"))
	{
		valueMap.insert(0, "eventConditionList");
		valueMap.insert(1, "unitControl");
	}
	if(myGroup.des.contains("DataAccessError"))
	{
		valueMap.insert(0, "object-invalidated");
		valueMap.insert(1, "hardware-fault");
		valueMap.insert(2, "temporarily-unavailable");
		valueMap.insert(3, "object-access-denied");
		valueMap.insert(4, "object-undefined");
		valueMap.insert(5, "invalid-address");
		valueMap.insert(6, "type-unsupported");
		valueMap.insert(7, "type-inconsistent");
		valueMap.insert(8, "object-attribute-inconsistent");
		valueMap.insert(9, "object-access-unsupported");
		valueMap.insert(10, "object-non-existent");
		valueMap.insert(11, "object-value-invalid");
	}
}
