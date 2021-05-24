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

	memcpy(DA, buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t" + DAToText() + "\r\n");
	mLen += 2;

	memcpy(DI, buff.data() + mLen, 4);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + DIToText() + "\r\n");
	mLen += 4;

	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	mRecvData.resize(mLen);
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
	dataType = 0;
	QString text = "数据标识编码DI: ";
	uint tmp = charTouint(DI, 4);
	switch(tmp)
	{
	case 0x00010000:
		text.append("(当前)正向有功总电能");
		dataType = 1;
		break;
	case 0x00020000:
		text.append("(当前)反向有功总电能");
		dataType = 1;
		break;
	case 0x00030000:
		text.append("(当前)组合无功1总电能");
		dataType = 1;
		break;
	case 0x00040000:
		text.append("(当前)组合无功2总电能");
		dataType = 1;
		break;
	case 0x00050000:
		text.append("(当前)第一象限无功总电能");
		dataType = 1;
		break;
	case 0x00060000:
		text.append("(当前)第二象限无功总电能");
		dataType = 1;
		break;
	case 0x00070000:
		text.append("(当前)第三象限无功总电能");
		dataType = 1;
		break;
	case 0x00080000:
		text.append("(当前)第四象限无功总电能");
		dataType = 1;
		break;
	case 0x00090000:
		text.append("(当前)正向视在总电能");
		dataType = 1;
		break;
	case 0x000a0000:
		text.append("(当前)反向视在总电能");
		dataType = 1;
		break;
	case 0x00800000:
		text.append("(当前)关联总电能");
		dataType = 1;
		break;
	case 0x00810000:
		text.append("(当前)正向有功基波总电能");
		dataType = 1;
		break;
	case 0x00820000:
		text.append("(当前)反向有功基波总电能");
		dataType = 1;
		break;
	case 0x00830000:
		text.append("(当前)正向有功谐波总电能");
		dataType = 1;
		break;
	case 0x00840000:
		text.append("(当前)反向有功谐波总电能");
		dataType = 1;
		break;
	case 0x00850000:
		text.append("(当前)铜损有功总电能补偿量");
		dataType = 1;
		break;
	case 0x00860000:
		text.append("(当前)铁损有功总电能补偿量");
		dataType = 1;
		break;
	case 0xe0000000:
		text.append("全部确定/否定");
		dataType = 2;
		break;
	case 0xe0001000:
		text.append("表示终端登录，数值为规约版本号");
		dataType = 3;
		break;
	case 0xe0001001:
		text.append("表示终端心跳，无数据体");
		dataType = 255;
		break;
	case 0xe0001002:
		text.append("表示登录退出，无数据体");
		dataType = 255;
		break;
	default:
		break;
	}
	return text;
}

QString MTAsduData::densityToText()
{
	QString text = "数据密度: " + QString::number(density) + "---";
	switch(density)
	{
	case 0:
		text.append("终端历史数据存储密度");
		break;
	case 1:
		text.append("1分钟");
		break;
	case 2:
		text.append("5分钟");
		break;
	case 3:
		text.append("15分钟");
		break;
	case 4:
		text.append("30分钟");
		break;
	case 5:
		text.append("60分钟");
		break;
	case 6:
		text.append("1天");
		break;
	case 7:
		text.append("1月");
		break;
	default:
		text.append("出错!未识别的数据密度");
		break;
	}
	return text;
}


bool MTAsduData::handle(const QByteArray& buff)
{
	if(flag & ISMASTER && afn == 0x0d)
	{
		dt1 = charToDateTime(buff.data() + mLen, 6, MYTIME2);
		mText.append(myTime2ToText(buff.data() + mLen, 6));
		mLen += 6;
		dt2 = charToDateTime(buff.data() + mLen, 6, MYTIME2);
		mText.append(myTime2ToText(buff.data() + mLen, 6));
		mLen += 6;
		density = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + densityToText() + "\r\n");
		mLen++;

	}
	bool ret = true;
	switch(dataType)
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
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！未知的数据标识编码"));
		return false;
		break;
	}
	if(!ret)
	{
		return ret;
	}
//	if(!(flag & ISMASTER) && afn == 0x0d)
//	{
//		dt1 = charToDateTime(buff.data() + len, 6, MYTIME2);
//		mText.append(myTime2ToText(buff.data() + len, 6));
//		len += 6;
//	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
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
	uint data = charTouint(buff.data() + mLen, 4);
	uint dataH = data / 100;
	uint dataL = data % 100;
	QString str = QString::number(dataH) + "." + QString("%1").arg(QString::number(dataL), 2, QLatin1Char('0'));
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t值:" + str + "\r\n");
	uintLst.append(data);
	mLen += 4;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

bool MTAsduData::handleData_2(const QByteArray& buff)
{
	uchar confirm = *(buff.data() + mLen) & 0x01;
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + QString(confirm ? "全部否定" : "全部肯定") + "\r\n");
	mLen++;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
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
	ushort data = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t值:" + QString::number(data) + "\r\n");
	mLen += 2;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}



