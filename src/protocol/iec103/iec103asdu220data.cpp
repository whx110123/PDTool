#include "iec103asdu220data.h"

IEC103Asdu220Data::IEC103Asdu220Data()
{
	typ = 0;
}

IEC103Asdu220Data::~IEC103Asdu220Data()
{

}

bool IEC103Asdu220Data::handle(const QByteArray& buff)
{
	typ = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + typToText() + "\r\n");
	len++;

	sDateTime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;
	eDateTime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu220Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

QString IEC103Asdu220Data::typToText()
{
	QString text = "事件类型TYP:" + QString::number(typ) + "   ";
	switch(typ)
	{
	case 1:
		text.append("动作元件");
		break;
	case 2:
		text.append("装置自检");
		break;
	case 3:
		text.append("运行告警");
		break;
	case 4:
		text.append("档位");
		break;
	case 5:
		text.append("软压板");
		break;
	case 6:
		text.append("硬压板");
		break;
	case 7:
		text.append("遥信");
		break;
	case 8:
		text.append("操作信息");
		break;
	case 255:
		text.append("所有事件");
		break;
	default:
		text.append("未知事件");
		break;
	}
	return text;
}
