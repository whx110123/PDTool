#include "iec103asdu1data.h"

IEC103Asdu1Data::IEC103Asdu1Data(const MyConfig& Config): IEC103AsduData(Config)
{
	dpi = 0;
}

IEC103Asdu1Data::~IEC103Asdu1Data()
{

}


bool IEC103Asdu1Data::handle(const QByteArray& buff)
{
	dpi = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + dpiToText(dpi) + "\r\n");
	mLen++;
	if(buff.length() != mLen)
	{
		if(mConfig.protocolName == IEC_103HUABEI)
		{
			datetime1 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, 7));
			mLen += 7;
		}
		else if(mConfig.protocolName == IEC_103BAOXINNET ||
				mConfig.protocolName == IEC_103BAOXINNET_NW)
		{
			datetime1 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, 7));
			mLen += 7;
			datetime2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, 7));
			mLen += 7;
		}
		else
		{
			datetime1 = charToDateTime(buff.data() + mLen, 4, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, 4));
			mLen += 4;

		}
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


