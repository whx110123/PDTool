#include "iec103asdu33data.h"

IEC103Asdu33Data::IEC103Asdu33Data(const MyConfig& Config): IEC103Asdu32Data(Config)
{

}

IEC103Asdu33Data::~IEC103Asdu33Data()
{

}

bool IEC103Asdu33Data::handle(const QByteArray& buff)
{
	int meaNum = 0;
	switch(inf)
	{
	case 148:
		meaNum = 9;
		break;
	default:
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！inf错误"));
		return false;
		break;

	}
	if(this->mIndex < meaNum)
	{
		shortdata = charToshortwithQ(buff.data() + mLen);
		qds = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t带品质描述词的被测值(bit4-16):" + QString::number(shortdata) + "\r\n\t" + ovToText(qds) + "   " + erToText(qds) + "\r\n");
		mLen += 2;
	}
	else if(mLen + 4 == buff.size())
	{
		datetime = charToDateTime(buff.data() + mLen, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 4));
		mLen += 4;
	}
	else
	{
		hr = charTouint(buff.data() + mLen, 3);
		mText.append(hrToText(buff.data() + mLen, 3) + "\r\n");
		mLen += 3;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


