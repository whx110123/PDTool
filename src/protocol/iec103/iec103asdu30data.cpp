#include "iec103asdu30data.h"

IEC103Asdu30Data::IEC103Asdu30Data(const MyConfig& Config): IEC103AsduData(Config)
{
	datauchar = 0;
	tov = 0;
	fan = 0;
	acc = 0;
	ndv = 0;
	nfe = 0;
}

IEC103Asdu30Data::~IEC103Asdu30Data()
{
	sdvs.clear();
}

bool IEC103Asdu30Data::handle(const QByteArray& buff)
{
	sdvs.clear();

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

	ndv = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t扰动值数目NDV:" + QString::number(nfe) + "\r\n");
	mLen++;

	nfe = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t第一个信息元素的序号NFE:" + QString::number(nfe) + "\r\n");
	mLen += 2;

	for(int i = 0; i < ndv; i++)
	{
		short sdv = charToint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t单个扰动值SDV" + QString::number(i + 1) + ": " + QString::number(sdv));
		mText.append("\t对应序号为" + QString::number(nfe + i) + "\r\n");
		sdvs.append(sdv);
		mLen += 2;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


