#include "iec103asdu27data.h"

IEC103Asdu27Data::IEC103Asdu27Data(const MyConfig& Config): IEC103AsduData(Config)
{
	datauchar = 0;
	tov = 0;
	fan = 0;
	acc = 0;
	rpv = 0;
	rsv = 0;
	rfa = 0;
}

IEC103Asdu27Data::~IEC103Asdu27Data()
{

}

bool IEC103Asdu27Data::handle(const QByteArray& buff)
{
	datauchar = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t未定义,固定为0"  + "\r\n");
	mLen++;

	tov = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + tovToText(tov) + "\r\n");
	mLen++;

	fan = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	mLen += 2;

	acc = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + accToText(acc) + "\r\n");
	mLen++;

	rpv = charTofloat(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t一次额定值RPV:" + QString::number(rpv) + "\r\n");
	mLen += 4;

	rsv = charTofloat(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t二次额定值RSV:" + QString::number(rsv) + "\r\n");
	mLen += 4;

	rfa = charTofloat(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t参比因子RFA:" + QString::number(rfa) + "\r\n");
	mLen += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

