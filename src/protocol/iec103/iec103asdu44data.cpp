#include "iec103asdu44data.h"

IEC103Asdu44Data::IEC103Asdu44Data(const MyConfig& Config): IEC103AsduData(Config)
{
	yx16 = 0;
	yx16flag = 0;
	qds = 0;
}

IEC103Asdu44Data::~IEC103Asdu44Data()
{

}

bool IEC103Asdu44Data::handle(const QByteArray& buff)
{
	yx16 = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t" + yx16ToText() + "\r\n");
	mLen += 2;

	yx16flag = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t" + yx16FlagToText() + "\r\n");
	mLen += 2;

	qds = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	mLen++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}



QString IEC103Asdu44Data::yx16ToText()
{
	QString text = "16个单点遥信状态";
	for(int i = 0; i < 16; i++)
	{
		text.append("\r\n\t");
		text.append((yx16 >> i) & 0x01 ? "1 合位" : "0 分位");
		text.append(" 对应INF:" + QString::number(inf + i));
	}
	return text;
}

QString IEC103Asdu44Data::yx16FlagToText()
{
	QString text = "16个单点遥信与上次查询的变化状态";
	for(int i = 0; i < 16; i++)
	{
		text.append("\r\n\t");
		text.append((yx16flag >> i) & 0x01 ? "1  有改变" : "0  无改变");
		text.append(" 对应INF:" + QString::number(inf + i));
	}
	return text;
}
