#include "iec101asdu125data.h"

IEC101Asdu125Data::IEC101Asdu125Data(const MyConfig& Config): IEC101AsduData(Config)
{
	nof = 0;
	nos = 0;
	los = 0;
}

IEC101Asdu125Data::~IEC101Asdu125Data()
{

}

bool IEC101Asdu125Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t文件名称NOF: " + QString::number(nof) + "\r\n");
	mLen += 2;

	nos = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t节名称NOS: " + QString::number(nos) + "\r\n");
	mLen++;

	los = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t段的长度: " + QString::number(los) + "\r\n");
	mLen++;

	QByteArray ba(buff.data() + mLen, los);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	gbkstr = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + mLen, los) + "\t段内容:\r\n" + gbkstr + "\r\n");
	mLen += los;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


