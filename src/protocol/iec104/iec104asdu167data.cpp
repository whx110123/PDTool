#include "iec104asdu167data.h"

IEC104Asdu167Data::IEC104Asdu167Data(const MyConfig& Config): IEC101AsduData(Config), asdu(Config)
{
	ctrl = 0;
	memset(devaddr, 0, sizeof(devaddr));
	iec103len = 0;
}

IEC104Asdu167Data::~IEC104Asdu167Data()
{

}

bool IEC104Asdu167Data::init(const QByteArray& buff)
{
	setDefault(buff);

	ctrl = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + ctrlToText() + "\r\n");
	mLen++;

	memcpy(devaddr, buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t保护装置地址L:" + QString::number(devaddr[0]) + "\r\n");
	mLen++;
	mText.append(CharToHexStr(buff.data() + mLen) + "\t保护装置地址H:" + QString::number(devaddr[1]) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	iec103len = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\tIEC103数据长度:" + QString::number(iec103len) + "\r\n");
	mLen++;

	asdu.mConfig.cotlen = 1;
	asdu.mConfig.comaddrlen = 1;

	if(!asdu.init(buff.mid(mLen, iec103len)))
	{
		mText.append(asdu.showToText());
		return false;
	}
	mText.append(asdu.showToText());
	mLen += asdu.mLen;
	if(asdu.mLen != iec103len)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

bool IEC104Asdu167Data::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	tmp.data += ctrl;
	tmp.data += QByteArray((char *)devaddr, 2);

	MyData tmp1;
	tmp1.getAttribute(proData);
	if(!asdu.createData(tmp1))
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}

	if(proData.reverse)
	{
		tmp.data += uintToBa(tmp1.data.length() + proData.data.length(), 1);
		proData = tmp + tmp1 + proData;
	}
	else
	{
		tmp.data += uintToBa(tmp1.data.length(), 1);
		proData = proData + tmp + tmp1;
	}
	mSendData = proData.data;
	return true;


}

QString IEC104Asdu167Data::ctrlToText()
{
	QString text = "保护信息传输控制字节，A/S(bit8):" + QString::number(ctrl & 0x80, 16).toUpper() + " ";
	uchar datanum = ctrl & 0x7f;
	if(ctrl & 0x80)
	{
		text.append("有后续帧");
	}
	else
	{
		text.append("无后续帧");
	}
	text.append("当前帧号(bit1-7):" + QString::number(datanum));
	return text;
}
