#include "iec103asdu10data.h"

IEC103Asdu10DataSetGid::IEC103Asdu10DataSetGid(const MyConfig& Config): MyBase(Config)
{
}

IEC103Asdu10DataSetGid::~IEC103Asdu10DataSetGid()
{
	qDeleteAll(gddlist);
	gddlist.clear();
}

bool IEC103Asdu10DataSetGid::initgid(const QByteArray& buff, uchar *gdd)
{
	setDefault(buff);

	qDeleteAll(gddlist);
	gddlist.clear();

	QString gbkstr;
	QString bit8;
	float datafloat;
	short datashort;
	uint datauint;
	uint datauint2;
	int dataint;
	uchar datauchar;
	uchar datauchar2;
	uchar datauchar3;
	uchar datauchar4;
	QDateTime datet;
	QDateTime datet2;

	switch(gdd[0])
	{
	case 1:
	{
		QByteArray ba(buff.data() + mLen, gdd[1]);
		QTextCodec *gbk = QTextCodec::codecForName("GB18030");
		gbkstr = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data() + mLen, gdd[1]) + "\tOS8(ASCII8位码):" + gbkstr + "\r\n");
		mLen += gdd[1];
		break;
	}
	case 2:
	{
		bit8 = QString("%1").arg(QString::number(*(uchar *)(buff.data() + mLen), 2), 8, '0');
		mText.append(CharToHexStr(buff.data() + mLen) + "\t成组8位串:" + bit8 + "\r\n");
		mLen++;
		break;
	}
	case 3:
		datauint = charTouint(buff.data() + mLen, gdd[1]);
		mText.append(CharToHexStr(buff.data() + mLen, gdd[1]) + "\tGID:无符号整数:" + QString::number(datauint) + "\r\n");
		mLen += gdd[1];
		break;
	case 4:
		dataint = charToint(buff.data() + mLen, gdd[1]);
		mText.append(CharToHexStr(buff.data() + mLen, gdd[1]) + "\tGID:整数:" + QString::number(dataint) + "\r\n");
		mLen += gdd[1];
		break;
	case 7:
		if(gdd[1] != 4)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是4");
			return false;
		}
		datafloat = charTofloat(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, gdd[1]) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat) + "\r\n");
		mLen += gdd[1];
		break;
	case 9:
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		mLen++;
		break;
	case 10:
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + spiToText(datauchar) + "\r\n");
		mLen++;
		break;
	case 11:
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + dpiteToText(datauchar) + "\r\n");
		mLen++;
		break;
	case 12:
		if(gdd[1] != 2)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datashort = charToshortwithQ(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, gdd[1]) + "\tGID:带品质描述词的被测值(bit4-16):" + QString::number(datashort) + "   " + ovToText(*(buff.data() + mLen)) + "   " + erToText(*(buff.data() + mLen)) + "\r\n");
		mLen += gdd[1];
		break;
	case 14:
		if(gdd[1] < 8)
		{
			datet = charToDateTime(buff.data() + mLen, gdd[1], BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, gdd[1]));
			mLen += gdd[1];
		}
		else
		{
			datet = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, 7));
			mLen += 7;
			datet = charToDateTime(buff.data() + mLen, gdd[1] - 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, gdd[1] - 7));
			mLen += (gdd[1] - 7);
		}
		break;
	case 15:
		if(gdd[1] != 2)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:组号: " + QString::number(datauchar) + "\r\n");
		mLen++;
		datauchar2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:条目号: " + QString::number(datauchar2) + "\r\n");
		mLen++;
		break;
	case 16:
		if(gdd[1] != 2)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;
		break;
	case 17:
		if(gdd[1] != 2)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是2");
			return false;
		}
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:FUN: " + QString::number(datauchar) + "\r\n");
		mLen++;
		datauchar2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:INF: " + QString::number(datauchar2) + "\r\n");
		mLen++;
		break;
	case 18:
		if(gdd[1] != 6)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是6");
			return false;
		}
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		mLen++;
		datet = charToDateTime(buff.data() + mLen, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 4));
		mLen += 4;
		datauchar2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:附加信息SIN:" + QString::number(datauchar2) + "\r\n");
		mLen++;
		break;
	case 19:
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		mLen++;
		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;

		datauint2 = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:故障序号FAN:" + QString::number(datauint2) + "\r\n");
		mLen += 2;

		datet = charToDateTime(buff.data() + mLen, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 4));
		mLen += 4;

		datauchar2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:附加信息SIN:" + QString::number(datauchar2) + "\r\n");
		mLen++;

		break;
	case 20:
		datafloat = charTofloat(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat) + "\r\n");
		mLen += 4;
		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;

		datauint2 = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:故障序号FAN:" + QString::number(datauint2) + "\r\n");
		mLen += 2;

		datet = charToDateTime(buff.data() + mLen, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 4));
		mLen += 4;
		break;
	case 21:
		if(gdd[1] > 4)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2大于4");
			return false;
		}
		datauint = charTouint(buff.data() + mLen, gdd[1]);
		mText.append(CharToHexStr(buff.data() + mLen, gdd[1]) + "\tGID:外部文本序号:" + QString::number(datauint) + " \r\n");
		mLen += gdd[1];
		break;
	case 22:
		if(gdd[1] != 1)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GDD2不是1");
			return false;
		}
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + grcToText(datauchar) + "\r\n");
		mLen ++;
		break;
	case 23:
		while(mLen < gdd[1])
		{
			IEC103Asdu10DataSetGdd *mgdd = new IEC103Asdu10DataSetGdd(mConfig);
			if(!mgdd->init(buff.mid(mLen)))
			{
				delete mgdd;
				mgdd = NULL;
				return false;
			}
			mgdd->mIndex = 0;
			mLen += mgdd->mLen;
			gddlist.append(mgdd);
		}
		if(mLen != gdd[1])
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！GID长度错误");
			return false;
		}
		break;
	case 201:
		datauint = charTouint(buff.data() + mLen, 4);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\tGID:无符号整数:" + QString::number(datauint) + "\r\n");
		mLen += 4;
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:预留字节,无定义" + "\r\n");
		mLen++;
		break;
	case 205:
		datafloat = charTofloat(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat) + "\r\n");
		mLen += 4;
		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;

		datauint2 = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:故障序号FAN:" + QString::number(datauint2) + "\r\n");
		mLen += 2;

		datet = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		break;
	case 213:
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		mLen++;
		datet = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datet2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datauchar2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:附加信息SIN:" + QString::number(datauchar2) + "\r\n");
		mLen++;
		break;
	case 214:
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + dpiToText(datauchar) + "\r\n");
		mLen++;
		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;
		datauint2 = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:电网故障序号NOF:" + QString::number(datauint2) + "\r\n");
		mLen += 2;
		datet = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datet2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datauchar2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:附加信息SIN:" + QString::number(datauchar2) + "\r\n");
		mLen++;
		break;
	case 215:
		datafloat = charTofloat(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat) + "\r\n");
		mLen += 4;
		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;
		datauint2 = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:电网故障序号NOF:" + QString::number(datauint2) + "\r\n");
		mLen += 2;
		datet = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datet2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		break;
	case 216:
		datauchar = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + fptToText(datauchar) + "\r\n");
		mLen++;
		datauchar2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:" + jptToText(datauchar2) + "\r\n");
		mLen++;
		datauchar3 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:备用\r\n");
		mLen++;
		datauchar4 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tGID:备用\r\n");
		mLen++;
		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;
		datauint2 = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:电网故障序号NOF:" + QString::number(datauint2) + "\r\n");
		mLen += 2;
		datet = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datet2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		break;
	case 217:
	{
		QByteArray ba(buff.data() + mLen, 40);
		QTextCodec *gbk = QTextCodec::codecForName("GB18030");
		gbkstr = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data() + mLen, 40) + "\t字符值(转为gbk格式显示):   " + gbkstr + "\r\n");
		mLen += 40;

		datauint = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		mLen += 2;
		datauint2 = charTouint(buff.data() + mLen, 2);
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGID:电网故障序号NOF:" + QString::number(datauint2) + "\r\n");
		mLen += 2;
		datet = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		datet2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		break;
	}
	default:
		mError = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的GDD1").arg(gdd[0]);
		return false;
		break;
	}
	gid = mRecvData.left(mLen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu10DataSetGid::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSetGdd *mgdd : gddlist)
	{
		text.append(mgdd->showToText());
	}
	return text;
}

bool IEC103Asdu10DataSetGid::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	tmp.data += gid;
	int index = 0;
	for(IEC103Asdu10DataSetGdd *mgdd : gddlist)
	{
		if(!mgdd->createData(tmp))
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
			return false;
		}
		index++;
	}

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;
}


IEC103Asdu10DataSetGdd::IEC103Asdu10DataSetGdd(const MyConfig& Config): MyBase(Config)
{
	gidnum = 0;
	memset(gdd, 0, sizeof(gdd));
}

IEC103Asdu10DataSetGdd::~IEC103Asdu10DataSetGdd()
{
	qDeleteAll(gidlist);
	gidlist.clear();
}

bool IEC103Asdu10DataSetGdd::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(gidlist);
	gidlist.clear();

	memcpy(gdd, buff.data() + mLen, 3);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + gdd1ToText(gdd[0]) + "\r\n");
	mLen++;
	mText.append(CharToHexStr(buff.data() + mLen) + "\tGDD2:" + QString::number(gdd[1]) + " 数据宽度\r\n");
	mLen++;
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + gdd3ToText(gdd[2]) + "\r\n");
	mLen++;
	if(gdd[0] == 2)
	{
		gidnum = ((ushort)gdd[1] * (gdd[2] & 0x7f) - 1) / 8 + 1;
	}
	else
	{
		gidnum = gdd[2] & 0x7f;
	}

	for(int index = 0; index < gidnum; index++)
	{
		IEC103Asdu10DataSetGid *mgid = new IEC103Asdu10DataSetGid(mConfig);
		bool isOk = mgid->initgid(buff.mid(mLen), gdd);
		if(!isOk)
		{
			delete mgid;
			mgid = NULL;
			return false;
		}
		mgid->mIndex = index;
		mLen += mgid->mLen;
		gidlist.append(mgid);
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu10DataSetGdd::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSetGid *mgid : gidlist)
	{
		text.append(mgid->showToText());
	}
	return text;
}

bool IEC103Asdu10DataSetGdd::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	tmp.data += QByteArray((char *)gdd, 3);

	int index = 0;
	for(IEC103Asdu10DataSetGid *mgid : gidlist)
	{
		if(!mgid->createData(tmp))
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
			return false;
		}
		index++;
	}

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;
}


IEC103Asdu10DataSet::IEC103Asdu10DataSet(const MyConfig& Config): MyBase(Config), mygdd(Config)
{
	memset(gin, 0, sizeof(gin));
	kod = 0;
}

IEC103Asdu10DataSet::~IEC103Asdu10DataSet()
{

}

bool IEC103Asdu10DataSet::init(const QByteArray& buff)
{
	setDefault(buff);

	memcpy(gin, buff.data() + mLen, sizeof(gin));
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\tGIN:组号" + QString::number(gin[0]) + "   条目号" + QString::number(gin[1]) + "\r\n");
	mLen += 2;

	kod = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + kodToText(kod) + "\r\n");
	mLen++;

	if(buff.size() == mLen)
	{
		return true;
	}

	if(!mygdd.init(buff.mid(mLen)))
	{
		return false;
	}
	mLen += mygdd.mLen;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu10DataSet::showToText()
{
	QString text = mText;
	text.append(mygdd.showToText());
	return text;
}

bool IEC103Asdu10DataSet::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	tmp.data += QByteArray((char *)gin, 2);
	tmp.data += kod;

	if(!mygdd.createData(tmp))
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;
}



IEC103Asdu10Data::IEC103Asdu10Data(const MyConfig& Config): IEC103AsduData(Config)
{
	rii = 0;
	ngd = 0;
}

IEC103Asdu10Data::~IEC103Asdu10Data()
{
	qDeleteAll(setlist);
	setlist.clear();
}

bool IEC103Asdu10Data::handle(const QByteArray& buff)
{
	qDeleteAll(setlist);
	setlist.clear();
	rii = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	mLen++;
	if(mLen == buff.size())
	{
		return true;
	}

	ngd = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + ngdToText(ngd) + "\r\n");
	mLen++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	for(int index = 0; index < (ngd & 0x3f); index++)
	{
		IEC103Asdu10DataSet *mset = new IEC103Asdu10DataSet(mConfig);
		bool isOk = mset->init(buff.mid(mLen));
		if(!isOk)
		{
			delete mset;
			mset = NULL;
			return false;
		}
		mset->mIndex = index;
		mLen += mset->mLen;
		setlist.append(mset);
	}

	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


QString IEC103Asdu10Data::showToText()
{
	QString text = mText;
	for(IEC103Asdu10DataSet *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103Asdu10Data::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	if(tmp.sqFlag == SQ_FUNINF)
	{
		tmp.data += fun;
		tmp.data += inf;
	}
	else if(tmp.sqFlag == SQ_INF)
	{
		tmp.data += inf;
	}
	tmp.data += rii;
	ngd = (ngd & 0xc0) + setlist.count();
	tmp.data += ngd;

	int index = 0;
	for(IEC103Asdu10DataSet *mset : setlist)
	{
		if(!mset->createData(tmp))
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
			return false;
		}
		index++;
	}

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;
}



