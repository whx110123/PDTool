#include "globaldefine.h"


QString CharToHexStr(uchar data)
{
	return QString("%1").arg(QString::number(data, 16).toUpper(), 2, QLatin1Char('0'));
}
QString CharToHexStr(const char *data, int len)
{
	uchar *mdata = (uchar *)data;
	return CharToHexStr(mdata, len);
}

QString CharToHexStr(uchar *data, int len)
{
	QString str;
	for(int i = 0; i < len; i++)
	{
		str.append(QString("%1").arg(QString::number(*(data + i), 16).toUpper(), 2, QLatin1Char('0')) + " ");
	}
	return str.trimmed();
}

uint charTouint(const char *data, int len, int model)
{
	uchar *mdata = (uchar *)data;
	return charTouint(mdata, len, model);
}
uint charTouint(uchar *data, int len, int model)
{
	uint tmp = 0;
	if(model == 0)
	{
		for(int i = 0; i < len; i++)
		{
			tmp += (uint)data[i] * (0x00000001 << (i * 8));
		}
	}
	else if(model == 1)
	{
		for(int i = 0; i < len; i++)
		{
			tmp += (uint)data[i] * (0x00000001 << ((len - 1 - i) * 8));
		}
	}
	else if(len == 4)
	{
		if(model == 2)
		{
			tmp += (uint)data[0] * 0x00000100;
			tmp += (uint)data[1] * 0x00000001;
			tmp += (uint)data[2] * 0x01000000;
			tmp += (uint)data[3] * 0x00010000;
		}
		else if(model == 3)
		{
			tmp += (uint)data[3] * 0x00000100;
			tmp += (uint)data[2] * 0x00000001;
			tmp += (uint)data[1] * 0x01000000;
			tmp += (uint)data[0] * 0x00010000;
		}
	}
	return tmp;
}
int charToint(uchar *data, int len, int model)
{
	if(len == 0 || len > 4)
	{
		return 0;
	}
	uint tmp1 = charTouint(data, len, model);
	tmp1 = tmp1 << ((4 - len) * 8);
	int tmp = *(int *)(&tmp1) >> ((4 - len) * 8);
	return tmp;
}
int charToint(const char *data, int len, int model)
{
	uchar *mdata = (uchar *)data;
	return charToint(mdata, len, model);
}
short charToshortwithQ(uchar *data, uchar& ov, uchar& er, int model)
{
	ushort tmp1;
	if(model == 0)
	{
		tmp1 = (ushort)data[0] + (ushort)data[1] * 0x100;
		ov = data[0] & 0x01;
		er = (data[0] >> 1) & 0x01;
	}
	else if(model == 1)
	{
		tmp1 = (ushort)data[0] * 0x100 + (ushort)data[1];
		ov = data[1] & 0x01;
		er = (data[1] >> 1) & 0x01;
	}
	short tmp = *(short *)(&tmp1) / 8;
	return tmp;
}

short charToshortwithQ(uchar *data, int model)
{
	ushort tmp1;
	if(model == 0)
	{
		tmp1 = (ushort)data[0] + (ushort)data[1] * 0x100;
	}
	else if(model == 1)
	{
		tmp1 = (ushort)data[0] * 0x100 + (ushort)data[1];
	}
	short tmp = *(short *)(&tmp1) / 8;
	return tmp;
}

short charToshortwithQ(const char *data, int model)
{
	uchar *mdata = (uchar *)data;
	return charToshortwithQ(mdata, model);
}

float charTofloat(const char *data, int model)
{
	uchar *mdata = (uchar *)data;
	return charTofloat(mdata, model);
}

float charTofloat(uchar *data, int model)
{
	uint aaa = charTouint(data, 4, model);
	float tmp = *(float *)&aaa;
	return tmp;
}

QDateTime charToDateTime(uchar *data, int len, int model)
{
	QDateTime datetime = QDateTime::currentDateTime();
	ushort tmp = 0;
	ushort milliseconds = datetime.time().msec();
	uchar second = datetime.time().second();
	uchar minutes = datetime.time().minute();
	uchar hours = datetime.time().hour();
	uchar dayofmonths = datetime.date().day();
	uchar months = datetime.date().month();
	ushort years = datetime.date().year();

	switch(model)
	{
	case BINARYTIME2A:
		if(len < 2)
		{
			return datetime;
		}
		tmp = data[0] + data[1] * 256;
		milliseconds = tmp % 1000;
		second = tmp / 1000;
		if(len == 2)
		{
			break;
		}
		minutes = data[2] & 0x3f;
		if(len == 3)
		{
			break;
		}
		hours = data[3] & 0x1f;
		if(len == 4)
		{
			break;
		}
		dayofmonths = data[4] & 0x1f;
		if(len == 5)
		{
			break;
		}
		months = data[5] & 0x0f;
		if(len == 6)
		{
			break;
		}
		years = (ushort)(data[6] & 0x7f) + (years / 100) * 100;
		break;
	case MYTIME1:
		if(len != 4)
		{
			return datetime;
		}
		milliseconds = 0;
		second = data[0];
		minutes = data[1];
		hours = data[2];
		dayofmonths = data[3];
		break;
	case MYTIME2:
		if(len != 6)
		{
			return datetime;
		}
		milliseconds = 0;
		second = 0;
		minutes = QString::number(data[0], 16).toUShort();
		hours = QString::number(data[1], 16).toUShort();
		dayofmonths = QString::number(data[2], 16).toUShort();
		months = QString::number(data[3], 16).toUShort();
		years = (QString::number(data[5], 16) + QString::number(data[4], 16)).toUShort();
		break;
	default:
		break;
	}
	datetime.setDate(QDate(years, months, dayofmonths));
	datetime.setTime(QTime(hours, minutes, second, milliseconds));
	return datetime;
}

QDateTime charToDateTime(const char *data, int len, int model)
{
	uchar *mdata = (uchar *)data;
	return charToDateTime(mdata, len, model);
}

QByteArray uintToBa(uint data, int len)
{
	QByteArray tmp;
	for(int i = 0; i < len; i++)
	{
		tmp.append((data >> (i * 8)) & 0xff);
	}
	return tmp;
}
QByteArray floatToBa(float data)
{
	char ch[4];
	memcpy(ch, &data, 4);
	QByteArray ba(ch, 4);
	return ba;
}
QByteArray dateTimeToBa(QDateTime datatime, int len, int model)
{

	QByteArray ba;
	switch(model)
	{
	case BINARYTIME2A:
	{
		ushort tmp = datatime.time().msec() + datatime.time().second() * 1000;
		char ch[2];
		memcpy(ch, &tmp, 2);
		ba.append(ch, 2);
		if(len == 2)
		{
			break;
		}
		uchar uch = datatime.time().minute();
		ba.append(uch);
		if(len == 3)
		{
			break;
		}
		uch = datatime.time().hour();
		ba.append(uch);
		if(len == 4)
		{
			break;
		}
		uch = datatime.date().dayOfWeek();
		uch = (uch << 5) + datatime.date().day();
		ba.append(uch);
		if(len == 5)
		{
			break;
		}
		uch = datatime.date().month();
		ba.append(uch);
		if(len == 6)
		{
			break;
		}
		uch = datatime.date().year() % 100;
		ba.append(uch);
		break;
	}
	case BINARYTIME2B:
		break;
	default:
		break;
	}
	return ba;
}

uchar crcsum(const char *data, int start, int end)
{
	uchar tmp = 0;
	for(int i = start; i < end + 1 ; i++)
	{
		tmp += *(uchar *)(data + i);
	}
	return tmp;
}



int stringToInt(QString data)
{
	int tmp = 0;				//长度域字节数
	if(data == IEC_SINGLE)
	{
		tmp = 1;
	}
	else if(data == IEC_DOUBLESAME)
	{
		tmp = 2;
	}
	else if(data == IEC_DOUBLEDIFF)
	{
		tmp = 2;
	}

	return tmp;

}

uint bcdTouint(const char *bcd, int len)
{
	uchar *mbcd = (uchar *)bcd;
	return bcdTouint(mbcd, len);
}

uint bcdTouint(uchar *bcd, int len)
{
	uint tmp = charTouint(bcd, len);
	QString str = QString::number(tmp, 16);
	return str.toUInt();
}

void BaReverse(QByteArray& ba)
{
	QByteArray tmp;
	for(int i = 0; i < ba.size(); i++)
	{
		tmp += ba.at(ba.size() - i - 1);
	}
	ba = tmp;
}

ushort crc16(uchar *data, int start, int end)
{
	ushort i;
	ushort j;
	ushort c;
	ushort crc = 0xFFFF;   //设置crc寄存器为0xffff
	for(i = start; i < end + 1; i++)
	{
		c = *(data + i) & 0x00FF;
		crc ^= c;
		for(j = 0; j < 8; j++)
		{
			if(crc & 0x0001)
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else
			{
				crc >>= 1;
			}
		}
	}
	return(crc);
}

ushort crc16(uchar *data, ushort len)
{
	ushort i;
	ushort j;
	ushort c;
	ushort crc = 0xFFFF;   //设置crc寄存器为0xffff
	for(i = 0; i < len; i++)
	{
		c = *(data + i) & 0x00FF;
		crc ^= c;
		for(j = 0; j < 8; j++)
		{
			if(crc & 0x0001)
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else
			{
				crc >>= 1;
			}
		}
	}
	return(crc);
}

double charTodouble(const char *data, int model)
{
	char mdata[8] = {0};
	if(model == 0)
	{
		memcpy(mdata, data, 8);
	}
	else if(model == 1)
	{
		mdata[0] = data[7];
		mdata[1] = data[6];
		mdata[2] = data[5];
		mdata[3] = data[4];
		mdata[4] = data[3];
		mdata[5] = data[2];
		mdata[6] = data[1];
		mdata[7] = data[0];
	}
	else if(model == 2)
	{
		mdata[0] = data[1];
		mdata[1] = data[0];
		mdata[2] = data[3];
		mdata[3] = data[2];
		mdata[4] = data[5];
		mdata[5] = data[4];
		mdata[6] = data[7];
		mdata[7] = data[6];
	}
	else if(model == 3)
	{
		mdata[0] = data[6];
		mdata[1] = data[7];
		mdata[2] = data[4];
		mdata[3] = data[5];
		mdata[4] = data[2];
		mdata[5] = data[3];
		mdata[6] = data[0];
		mdata[7] = data[1];
	}
	return *(double *)mdata;
}

double charTodouble(uchar *data, int model)
{
	char *mdata = (char *)data;
	return charTodouble(mdata, model);
}
