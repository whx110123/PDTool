#include "measuredterminalasdudata.h"

MTAsduData::MTAsduData()
{
	memset(DA, 0, sizeof(DA));
	memset(DI, 0, sizeof(DI));
	density = 0;
}

MTAsduData::~MTAsduData()
{

}

bool MTAsduData::init(const QByteArray& buff)
{
	setDefault(buff);

	dataClear();

	memcpy(DA, buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + DAToText() + "\r\n");
	len += 2;

	memcpy(DI, buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t" + DIToText() + "\r\n");
	len += 4;

	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	return true;
}

void MTAsduData::dataClear()
{
	uintLst.clear();
}

QString MTAsduData::DAToText()
{
	QString text = "信息点标识DA:";
	if(DA[0] == 0 && DA[1] == 0)
	{
		text.append("终端测量点P0");
	}
	else if(DA[0] && DA[1])
	{
		text.append("对应测量点");
		int sum = 0;
		for(int i = 0; i < 8; i++)
		{
			if((DA[0] >> i) & 0x01)
			{
				text.append("p" + QString::number((DA[1] - 1) * 8 + i + 1) + " ");
				sum++;
			}
		}
		text.append(QString("共%1个点").arg(sum));
	}
	else
	{
		text = "错误的信息点标识";
	}

	return text;
}

QString MTAsduData::DIToText()
{
	dataTpye = 0;
	QString text = "数据标识编码DI: ";
	uint tmp = charTouint(DI, 4);
	switch(tmp)
	{
	case 0x00010000:
		text.append("(当前)正向有功总电能");
		dataTpye = 1;
		break;
	default:
		break;
	}
	return text;
}


bool MTAsduData::handle(const QByteArray& buff)
{
	switch(dataTpye)
	{
	case 1:
		if(flag & ISMASTER)
		{
			break;
		}
		if(!handleData_1(buff))
		{
			return false;
		}
		break;
	default:
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！未知的数据标识编码"));
		return false;
		break;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool MTAsduData::handleData_1(const QByteArray& buff)
{
	uint data = charTouint(buff.data() + len, 4);
	uint dataH = data / 100;
	uint dataL = data % 100;
	QString str = QString::number(dataH) + "." + QString("%1").arg(QString::number(dataL), 2, QLatin1Char('0'));
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t值:" + str + "\r\n");
	uintLst.append(data);
	len += 4;
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}



