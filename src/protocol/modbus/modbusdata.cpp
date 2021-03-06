﻿#include "modbusdata.h"

ModbusData::ModbusData(const MyConfig& Config): MyBase(Config)
{

}

ModbusData::~ModbusData()
{

}

bool ModbusData::initData(const QByteArray& buff, ModbusDataGroup *group)
{
	setDefault(buff);
	if(mIndex <  group->analysis.length())
	{
		mcode = group->analysis.at(mIndex);
	}
	else
	{
		mcode = group->analysis.back();
	}
	mtype = group->type;
	int mod = 0;
	if(mtype == YC)
	{
		switch(mcode.unicode())
		{
		case '0':
			if(group->sort == SORT1 || group->sort == SORT2)
			{
				mod = 1;
			}
			datashort = charToint(buff.data() + mLen, 2, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "有符号整数:" + QString::number(datashort) + "\r\n");
			mLen += 2;
			break;
		case '1':
			if(group->sort == SORT1 || group->sort == SORT2)
			{
				mod = 1;
			}
			dataushort = charTouint(buff.data() + mLen, 2, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "无符号整数:" + QString::number(dataushort) + "\r\n");
			mLen += 2;
			break;
		case '2':
			if(group->sort == SORT1 || group->sort == SORT2)
			{
				mod = 1;
			}
			dataushort = charTouint(buff.data() + mLen, 2, mod);
			if(dataushort & 0x8000)
			{
				datashort = (dataushort & 0x7fff) * (-1);
			}
			else
			{
				datashort = dataushort;
			}
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "原码表示的有符号整数:" + QString::number(datashort) + "\r\n");
			mLen += 2;
			break;
		case '3':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			dataint = charToint(buff.data() + mLen, 4, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "有符号整数:" + QString::number(dataint) + "\r\n");
			mLen += 4;
			break;
		case '4':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datauint = charTouint(buff.data() + mLen, 4, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "无符号整数:" + QString::number(datauint) + "\r\n");
			mLen += 4;
			break;
		case '5':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datafloat = charTofloat(buff.data() + mLen, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "浮点数:" + QString::number(datafloat, 'g', 10) + "\r\n");
			mLen += 4;
			break;
		case '6':
			datachar = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "有符号整数:" + QString::number(datachar) + "\r\n");
			mLen++;
			break;
		case '7':
			datauchar = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "无符号整数:" + QString::number(datauchar) + "\r\n");
			mLen++;
			break;
		case 'A':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datadouble = charTodouble(buff.data() + mLen, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 8) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "双精度浮点数:" + QString::number(datadouble, 'g', 20) + "\r\n");
			mLen += 8;
			break;
		case 'F':
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t忽略两个字节\r\n");
			mLen += 2;
			break;
		default:
			mError = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的解析码").arg(mcode);
			return false;
			break;
		}
	}
	else if(mtype == YX)
	{
		switch(mcode.unicode())
		{
		case '0':
			datauchar = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen));
			for(int i = 0; i < 8; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(mIndex + 1).arg(i + 1));
				mText.append((datauchar >> i) & 0x01 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			mLen++;
			break;
		case '1':
			dataushort = charTouint(buff.data() + mLen, 2, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 2));
			for(int i = 0; i < 16; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(mIndex + 1).arg(i + 1));
				mText.append((dataushort >> i) & 0x01 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			mLen += 2;
			break;
		case '2':
			datauint = charTouint(buff.data() + mLen, 4, 1);
			mText.append(CharToHexStr(buff.data() + mLen, 4));
			for(int i = 0; i < 32; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(mIndex + 1).arg(i + 1));
				mText.append((datauint >> i) & 0x01 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			mLen += 4;
			break;
		case '3':
			datauchar = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen));
			for(int i = 0; i < 8; i++)
			{
				mText.append(QString("\t第%1组 第%2个遥信: ").arg(mIndex + 1).arg(i + 1));
				mText.append((datauchar << i) & 0x80 ? "1 合位" : "0 分位");
				mText.append("\r\n");
			}
			mLen++;
			break;
		case 'F':
			mText.append(CharToHexStr(buff.data() + mLen) + "\t忽略一个字节\r\n");
			mLen++;
			break;
		default:
			mError = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的解析码").arg(mcode);
			return false;
			break;
		}
	}
	else if(mtype == YM)
	{
		switch(mcode.unicode())
		{
		case '0':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datauint = charTouint(buff.data() + mLen, 4, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "无符号整数:" + QString::number(datauint) + "\r\n");
			mLen += 4;
			break;
		case '1':
			if(group->sort == SORT1)
			{
				mod = 1;
			}
			else if(group->sort == SORT2)
			{
				mod = 2;
			}
			else if(group->sort == SORT3)
			{
				mod = 3;
			}
			else if(group->sort == SORT4)
			{
				mod = 0;
			}
			datafloat = charTofloat(buff.data() + mLen, mod);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t" + QString("第%1个数据  ").arg(mIndex + 1) + "浮点数:" + QString::number(datafloat, 'g', 10) + "\r\n");
			mLen += 4;
			break;
		case 'F':
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t忽略四个字节\r\n");
			mLen += 4;
			break;
		default:
			mError = QString("\"%1\" %2 [%3行]\r\n%4:%5\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的解析码").arg(mcode);
			return false;
			break;
		}
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未知类型");
		return false;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

