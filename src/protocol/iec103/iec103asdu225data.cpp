#include "iec103asdu225data.h"

IEC103Asdu225Data::IEC103Asdu225Data(const MyConfig& Config): IEC103AsduData(Config)
{
	fnam = 0;
	snam = 0;
	tmp = 0;
	dlen = 0;
}

IEC103Asdu225Data::~IEC103Asdu225Data()
{

}

bool IEC103Asdu225Data::handle(const QByteArray& buff)
{
	fnam = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t文件名称FNAM: " + QString::number(fnam) + "\r\n");
	mLen += 2;

	snam = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t节名称SNAM: " + QString::number(snam) + "\r\n");
	mLen++;

	tmp = charTouint(buff.data() + mLen, 2);
	if(mLen + 2 + tmp != buff.length())
	{
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t未知: " + QString::number(tmp) + "\r\n");
		mLen += 2;
	}

	dlen = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t段长度: " + QString::number(dlen) + "\r\n");
	mLen += 2;

	if(mLen + dlen != buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！段长度错误");
		return false;
	}
	QByteArray ba(buff.data() + mLen, dlen);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	gbkstr = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + mLen, dlen) + "\t段内容:\r\n" + gbkstr + "\r\n");
	mLen += dlen;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

