#include "iec103asdu12data.h"

IEC103Asdu12Data::IEC103Asdu12Data(const MyConfig& Config): IEC103AsduData(Config)
{

}

IEC103Asdu12Data::~IEC103Asdu12Data()
{

}

bool IEC103Asdu12Data::handle(const QByteArray& buff)
{

	fpt = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + fptToText(fpt) + "\r\n");
	len++;

	jpt = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + jptToText(jpt) + "\r\n");
	len++;

	scl = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t短路位置SCL: " + QString::number(scl) + "\r\n");
	len += 4;

	dpi_ch = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpichToText(jpt) + "\r\n");
	len++;

	time_ch = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t重合闸时间: " + QString::number(time_ch) + "ms\r\n");
	len += 2;

	datafloat[0] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ua幅值: " + QString::number(datafloat[0]) + "\r\n");
	len += 4;
	datafloat[1] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ua相角: " + QString::number(datafloat[1]) + "\r\n");
	len += 4;
	datafloat[2] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ub幅值: " + QString::number(datafloat[2]) + "\r\n");
	len += 4;
	datafloat[3] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ub相角: " + QString::number(datafloat[3]) + "\r\n");
	len += 4;
	datafloat[4] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Uc幅值: " + QString::number(datafloat[4]) + "\r\n");
	len += 4;
	datafloat[5] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Uc相角: " + QString::number(datafloat[5]) + "\r\n");
	len += 4;
	datafloat[6] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ia幅值: " + QString::number(datafloat[6]) + "\r\n");
	len += 4;
	datafloat[7] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ia相角: " + QString::number(datafloat[7]) + "\r\n");
	len += 4;
	datafloat[8] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ib幅值: " + QString::number(datafloat[8]) + "\r\n");
	len += 4;
	datafloat[9] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ib相角: " + QString::number(datafloat[9]) + "\r\n");
	len += 4;
	datafloat[10] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ic幅值: " + QString::number(datafloat[10]) + "\r\n");
	len += 4;
	datafloat[11] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障前Ic相角: " + QString::number(datafloat[11]) + "\r\n");
	len += 4;

	datafloat[12] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ua幅值: " + QString::number(datafloat[12]) + "\r\n");
	len += 4;
	datafloat[13] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ua相角: " + QString::number(datafloat[13]) + "\r\n");
	len += 4;
	datafloat[14] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ub幅值: " + QString::number(datafloat[14]) + "\r\n");
	len += 4;
	datafloat[15] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ub相角: " + QString::number(datafloat[15]) + "\r\n");
	len += 4;
	datafloat[16] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Uc幅值: " + QString::number(datafloat[16]) + "\r\n");
	len += 4;
	datafloat[17] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Uc相角: " + QString::number(datafloat[17]) + "\r\n");
	len += 4;
	datafloat[18] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ia幅值: " + QString::number(datafloat[18]) + "\r\n");
	len += 4;
	datafloat[19] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ia相角: " + QString::number(datafloat[19]) + "\r\n");
	len += 4;
	datafloat[20] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ib幅值: " + QString::number(datafloat[20]) + "\r\n");
	len += 4;
	datafloat[21] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ib相角: " + QString::number(datafloat[21]) + "\r\n");
	len += 4;
	datafloat[22] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ic幅值: " + QString::number(datafloat[22]) + "\r\n");
	len += 4;
	datafloat[23] = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t故障后Ic相角: " + QString::number(datafloat[23]) + "\r\n");
	len += 4;

	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append("\t故障时间:\r\n" + timeToText(buff.data() + len, 7));
	len += 7;

	uchar waveFileNameLen;
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		waveFileNameLen = 128;
	}
	else
	{
		waveFileNameLen = 64;
	}

	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QByteArray ba(buff.data() + len, waveFileNameLen);
	waveFileName = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, waveFileNameLen) + "\t不含扩展名的录波文件名:   " + waveFileName + "\r\n");
	len += waveFileNameLen;

	ba.clear();
	ba.append(buff.data() + len, 40);
	name = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, 40) + "\t故障间隔名（如线路）40个字节:   " + name + "\r\n");
	len += 40;

	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append("\t子站接受时间:\r\n" + timeToText(buff.data() + len, 7));
	len += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

