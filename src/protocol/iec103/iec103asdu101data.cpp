#include "iec103asdu101data.h"

IEC103Asdu101Data::IEC103Asdu101Data(const MyConfig& Config): IEC103Asdu15Data(Config)
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu101Data::~IEC103Asdu101Data()
{

}

bool IEC103Asdu101Data::handle(const QByteArray& buff)
{
	if(mConfig.protocolName == IEC_103HUABEI)
	{
		//规约无此内容
	}
	else
	{
		rii = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
		mLen++;
	}

	dtBegin = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	dtEnd = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	QByteArray ba(buff.data() + mLen, 100);
	fileName = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + mLen, 100) + "\t一般文件名称100个字节:   " + fileName + "\r\n");
	mLen += 100;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
