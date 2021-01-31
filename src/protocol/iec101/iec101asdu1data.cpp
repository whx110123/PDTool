#include "iec101asdu1data.h"

IEC101Asdu1Data::IEC101Asdu1Data(const MyConfig& Config): IEC101AsduData(Config)
{
	siq = 0;
}

IEC101Asdu1Data::~IEC101Asdu1Data()
{

}

bool IEC101Asdu1Data::handle(const QByteArray& buff)
{
	mText.append("\t对应点号是:" + QString::number(infaddr - 1) + "\r\n");
	siq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}



