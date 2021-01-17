#include "iec101asdu101data.h"

IEC101Asdu101Data::IEC101Asdu101Data()
{
	qcc = 0;
}

IEC101Asdu101Data::~IEC101Asdu101Data()
{

}


bool IEC101Asdu101Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	qcc = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t计数量召唤命令限定词(QCC):\r\n\t" + rqtToText(qcc) + "\r\n\t" + frzToText(qcc) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC101Asdu101Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
