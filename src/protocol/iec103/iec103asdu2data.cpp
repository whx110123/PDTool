#include "iec103asdu2data.h"

IEC103Asdu2Data::IEC103Asdu2Data(const MyConfig& Config): IEC103AsduData(Config)
{
	dpi = 0;
	ret = 0;
	fan = 0;

}

IEC103Asdu2Data::~IEC103Asdu2Data()
{

}

bool IEC103Asdu2Data::handle(const QByteArray& buff)
{
	dpi = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + dpiToText(dpi) + "\r\n");
	mLen++;

	ret = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t相对时间RET:" + QString::number(ret) + "\r\n");
	mLen += 2;

	fan = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	mLen += 2;

	if(mConfig.protocolName == IEC_103HUABEI)
	{
		datetime1 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
	}
	else if(buff.length() < 20)
	{
		datetime1 = charToDateTime(buff.data() + mLen, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 4));
		mLen += 4;
	}
	else
	{
		datetime1 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datetime2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


