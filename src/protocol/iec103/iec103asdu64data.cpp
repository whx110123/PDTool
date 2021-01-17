#include "iec103asdu64data.h"

IEC103Asdu64Data::IEC103Asdu64Data()
{
	dcc = 0;
}

IEC103Asdu64Data::~IEC103Asdu64Data()
{

}

bool IEC103Asdu64Data::handle(const QByteArray& buff)
{
	dcc = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dcsToText(dcc) + "   " + seToText(dcc) + "   " + actToText(dcc) + "   " + quToText_iec103(dcc) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu64Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
