#include "iec104asdu55data.h"

IEC104Asdu55Data::IEC104Asdu55Data(const MyConfig& Config): IEC101AsduData(Config)
{
	code = 0;
	ctrlNo = 0;
	objlen = 0;
	step = 0;
	rii = 0;
	userlen = 0;
}

IEC104Asdu55Data::~IEC104Asdu55Data()
{

}

bool IEC104Asdu55Data::init(const QByteArray& buff)
{
	setDefault(buff);

	code = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + codeToText() + "\r\n");
	mLen++;

	ctrlNo = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t控制对象顺序号:" + QString::number(ctrlNo) + "\r\n");
	mLen++;

	objlen = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t控制对象长度:" + QString::number(objlen) + "\r\n");
	mLen++;

	QByteArray ba(buff.data() + mLen, objlen);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	obj = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + mLen, objlen) + "\t控制对象:" + obj + "\r\n");
	mLen += objlen;

	step = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t步骤号:" + QString::number(step) + (step > 0 ? QString() : QString("  0代表整张票")) + "\r\n");
	mLen++;

	if(buff.length() == 5 + objlen)
	{
		rii = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + riiToText() + "\r\n");
		mLen++;
	}
	else if(buff.length() > 5 + objlen)
	{
		userlen = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t操作用户名长度:" + QString::number(userlen) + "\r\n");
		mLen++;

		QByteArray ba(buff.data() + mLen, userlen);
		user = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data() + mLen, userlen) + "\t操作用户名 :" + user + "\r\n");
		mLen += userlen;
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度错误");
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

QString IEC104Asdu55Data::codeToText()
{
	QString text = "序列控制命令限定词:" + QString::number(code & 0x7f) + " ";
	switch(code & 0x7f)
	{
	case 0:
		text.append("序列控制操作票调阅");
		break;
	case 1:
		text.append("序列控制操作预演");
		break;
	case 2:
		text.append("序列控制操作取消");
		break;
	case 3:
		text.append("序列控制操作执行");
		break;
	case 4:
		text.append("序列控制操作暂停");
		break;
	case 5:
		text.append("序列控制操作继续");
		break;
	case 6:
		text.append("序列控制操作终止");
		break;
	case 7:
		text.append("序列控制单步结果确认");
		break;
	case 11:
		text.append("序列控制成功");
		break;
	case 12:
		text.append("序列控制失败");
		break;
	case 13:
		text.append("预演成功");
		break;
	case 14:
		text.append("预演失败");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("   (bit8):") + QString::number(code & 0x80, 16).toUpper() + " ";
	if(code & 0x80)
	{
		text.append("有后续命令字段");
	}
	else
	{
		text.append("无后续命令字段");
	}
	return text;
}

QString IEC104Asdu55Data::riiToText()
{
	QString text = "返回信息功能码:" + QString::number(rii) + " ";
	switch(rii)
	{
	case 0:
		text.append("成功");
		break;
	case 1:
		text.append("操作执行不成功");
		break;
	case 2:
		text.append("操作前条件不满足");
		break;
	case 3:
		text.append("异常终止");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}
