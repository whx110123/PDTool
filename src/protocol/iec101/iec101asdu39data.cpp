#include "iec101asdu39data.h"

IEC101Asdu39Data::IEC101Asdu39Data()
{

}

IEC101Asdu39Data::~IEC101Asdu39Data()
{

}

bool IEC101Asdu39Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	spe = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t继电保护设备的启动事件SPE:" + gsToText(spe) + "   " + sl1ToText(spe) + "   " + sl2ToText(spe) + "   " + sl3ToText(spe) + "   " + sieToText(spe) + "   " + srdToText(spe) + "\r\n");
	len++;

	qdp = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t继电保护设备事件的品质描述词QDP:"  + ivToText(qdp) + "   " + ntToText(qdp) + "   " + sbToText(qdp) + "   " + blToText(qdp) + "   " + eiToText(qdp) + "\r\n");
	len++;

	datetime1 = charToDateTime(buff.data() + len, 2, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 2));
	len += 2;

	datetime2 = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu39Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
