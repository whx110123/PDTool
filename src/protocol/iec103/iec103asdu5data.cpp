#include "iec103asdu5data.h"

IEC103Asdu5Data::IEC103Asdu5Data(const MyConfig& Config): IEC103AsduData(Config)
{
	col = 0;
	memset(ch, 0, sizeof(ch));
}

IEC103Asdu5Data::~IEC103Asdu5Data()
{

}

bool IEC103Asdu5Data::handle(const QByteArray& buff)
{

	col = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + colToText(col) + "\r\n");
	mLen++;

	QByteArray ba(buff.data() + mLen, 8);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	gbkstr = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + mLen, 8) + "\tASCII: " + gbkstr + "\r\n");
	mLen += 8;

	memcpy(ch, buff.data() + mLen, 4);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t用户自定义字符\r\n");
	mLen += 4;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


