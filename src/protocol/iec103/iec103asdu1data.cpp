#include "iec103asdu1data.h"

IEC103Asdu1Data::IEC103Asdu1Data()
{
	dpi = 0;
}

IEC103Asdu1Data::~IEC103Asdu1Data()
{

}


bool IEC103Asdu1Data::handle(const QByteArray& buff)
{
	dpi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(dpi) + "\r\n");
	len++;
	if(buff.length() != len)
	{
		if(buff.length() < 16)
		{
			datetime1 = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
			mText.append(timeToText(buff.data() + len, 4));
			len += 4;
		}
		else
		{
			datetime1 = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + len, 7));
			len += 7;
			datetime2 = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + len, 7));
			len += 7;
		}
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC103Asdu1Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
