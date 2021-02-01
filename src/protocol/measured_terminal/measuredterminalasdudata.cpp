#include "measuredterminalasdudata.h"

MTAsduData::MTAsduData(const MyConfig& Config): MyBase(Config)
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
	case 0x00020000:
		text.append("(当前)反向有功总电能");
		dataTpye = 1;
		break;
	case 0x00030000:
		text.append("(当前)组合无功1总电能");
		dataTpye = 1;
		break;
	case 0x00040000:
		text.append("(当前)组合无功2总电能");
		dataTpye = 1;
		break;
	case 0x00050000:
		text.append("(当前)第一象限无功总电能");
		dataTpye = 1;
		break;
	case 0x00060000:
		text.append("(当前)第二象限无功总电能");
		dataTpye = 1;
		break;
	case 0x00070000:
		text.append("(当前)第三象限无功总电能");
		dataTpye = 1;
		break;
	case 0x00080000:
		text.append("(当前)第四象限无功总电能");
		dataTpye = 1;
		break;
	case 0x00090000:
		text.append("(当前)正向视在总电能");
		dataTpye = 1;
		break;
	case 0x000a0000:
		text.append("(当前)反向视在总电能");
		dataTpye = 1;
		break;
	case 0x00800000:
		text.append("(当前)关联总电能");
		dataTpye = 1;
		break;
	case 0x00810000:
		text.append("(当前)正向有功基波总电能");
		dataTpye = 1;
		break;
	case 0x00820000:
		text.append("(当前)反向有功基波总电能");
		dataTpye = 1;
		break;
	case 0x00830000:
		text.append("(当前)正向有功谐波总电能");
		dataTpye = 1;
		break;
	case 0x00840000:
		text.append("(当前)反向有功谐波总电能");
		dataTpye = 1;
		break;
	case 0x00850000:
		text.append("(当前)铜损有功总电能补偿量");
		dataTpye = 1;
		break;
	case 0x00860000:
		text.append("(当前)铁损有功总电能补偿量");
		dataTpye = 1;
		break;
	case 0xe0000000:
		text.append("全部确定/否定");
		dataTpye = 2;
		break;
	case 0xe0001000:
		text.append("表示终端登录，数值为规约版本号");
		dataTpye = 3;
		break;
	case 0xe0001001:
		text.append("表示终端心跳，无数据体");
		dataTpye = 255;
		break;
	case 0xe0001002:
		text.append("表示登录退出，无数据体");
		dataTpye = 255;
		break;
	default:
		break;
	}
	return text;
}


bool MTAsduData::handle(const QByteArray& buff)
{
	if(flag & ISMASTER && afn == 0x0d)
	{

	}
	bool ret = true;
	switch(dataTpye)
	{
	case 1:
		ret = handleData_1(buff);
		break;
	case 2:
		ret = handleData_2(buff);
		break;
	case 3:
		ret = handleData_3(buff);
		break;
	case 255:
		break;
	default:
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！未知的数据标识编码"));
		return false;
		break;
	}
	if(!ret)
	{
		return ret;
	}
	if(!(flag & ISMASTER) && afn == 0x0d)
	{

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
	if(flag & ISMASTER)
	{
		return true;
	}
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

bool MTAsduData::handleData_2(const QByteArray& buff)
{
	uchar confirm = *(buff.data() + len) & 0x01;
	mText.append(CharToHexStr(buff.data() + len) + "\t" + QString(confirm ? "全部否定" : "全部肯定") + "\r\n");
	len++;
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool MTAsduData::handleData_3(const QByteArray& buff)
{
	if(flag & ISMASTER)
	{
		return true;
	}
	ushort data = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t值:" + QString::number(data) + "\r\n");
	len += 2;
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}



