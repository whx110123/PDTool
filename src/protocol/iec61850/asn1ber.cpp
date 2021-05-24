#include "asn1ber.h"
#include "iec61850value_bitstring.h"
#include "iec61850value_boolean.h"
#include "iec61850value_integer.h"
#include "iec61850value_null.h"
#include "iec61850value_octetstring.h"
#include "iec61850value_timeofday.h"
#include "iec61850value_utctime.h"
#include "iec61850value_utf8string.h"

ASN1BER::ASN1BER(const MyConfig& Config): MyBase(Config)
{
	myValue = NULL;
}

ASN1BER::~ASN1BER()
{
	qDeleteAll(myList);
	myList.clear();
	if(myValue)
	{
		delete myValue;
		myValue = NULL;
	}
}

bool ASN1BER::init(const QByteArray& buff)
{
	setDefault(buff);
	qDeleteAll(myList);
	myList.clear();
	initMap();

	if(!getTagNo(buff, myTag, myTagNoLen, myTagNo))
	{
		return false;
	}
	switch(myGroup.type)
	{
	case Choice:
	{
		mText.append("\t" + myGroup.des + "\r\n");
		ASN1BER *pBER = CreateBER(myTagNo, myTag, 0);
		if(!pBER)
		{
			return false;
		}
		myList.append(pBER);
		if(!pBER->init(buff.mid(mLen)))
		{
			mText.append(pBER->showToText());
			return false;
		}
		mText.append(pBER->showToText());
		mLen += pBER->mLen;
		break;
	}
	case ChoiceWithTag:
	case Sequence:
	{
		mText.append(CharToHexStr(buff.data() + mLen, 1 + myTagNoLen) + "\t" + tagNoToText(myTagNo) + "  " + tagToText(myTag)  + "\r\n");
		mLen += 1 + myTagNoLen;
		if(!getLength(buff, myLengthType, myLengthLen, myLength))
		{
			return false;
		}
		int curLen = mLen;
		uint index = 0;
		while(mLen < (int)myLength + curLen)
		{
			if(!getTagNo(buff, myTag, myTagNoLen, myTagNo))
			{
				return false;
			}
			ASN1BER *pBER = CreateBER(myTagNo, myTag, index);
			if(!pBER)
			{
				return false;
			}
			myList.append(pBER);
			if(!pBER->init(buff.mid(mLen)))
			{
				mText.append(pBER->showToText());
				return false;
			}
			mText.append(pBER->showToText());
			mLen += pBER->mLen;
			index++;
		}
		break;
	}
	default:
	{
		mText.append(CharToHexStr(buff.data() + mLen, 1 + myTagNoLen) + "\t" + tagNoToText(myTagNo) + "  " + tagToText(myTag)  + "\r\n");
		mLen += 1 + myTagNoLen;
		if(!getLength(buff, myLengthType, myLengthLen, myLength))
		{
			return false;
		}
		if(!myValue)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
					 .arg(QString("出错！未知的数据类型"));
			return false;
		}
		if(!myValue->init(buff.mid(mLen, myLength)))
		{
			mText.append(myValue->showToText());
			return false;
		}
		mText.append(myValue->showToText());
		mLen += myValue->mLen;
		break;
	}
	}

	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

void ASN1BER::initMap()
{
	myTagNoMap.clear();
}

ASN1BER *ASN1BER::CreateBER(uint tagNo, uchar tag, uint index)
{
	ASN1BER *ber = NULL;
	switch(tag >> 6)
	{
	case 0:
		ber = CreateUniversalBER(tagNo, index);
		break;
	case 2:
		ber = CreateContextBER(tagNo, index);
		break;
	default:
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！创建tag=%1的BER失败").arg(tag));
		break;
	}
	return ber;
}

ASN1BER *ASN1BER::CreateUniversalBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(!myIndexMap.isEmpty())
	{
		ber = CreateBERByType(tagNo);
		if(ber)
		{
			BERGroup g;
			if(myIndexMap.contains(index))
			{
				g = myIndexMap[index];
			}
			else
			{
				g = myIndexMap.last();
			}
			ber->myGroup = g;
			if(ber->myValue)
			{
				ber->myValue->myGroup = g;
			}
		}
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建UniversalBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}

ASN1BER *ASN1BER::CreateBERByType(uint type, uint index)
{
	ASN1BER *ber = NULL;
	switch(type)
	{
	case ASN1BER::Boolean:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_Boolean(mConfig);
		break;
	case ASN1BER::Integer:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_Integer(mConfig);
		break;
	case ASN1BER::BitString:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_BitString(mConfig);
		break;
	case ASN1BER::OctetString:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_OctetString(mConfig);
		break;
	case ASN1BER::Null:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_Null(mConfig);
		break;
	case ASN1BER::UTF8String:
	case ASN1BER::VisibleString:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_UTF8String(mConfig);
		break;
	case ASN1BER::Sequence:
		ber = CreateSequenceBER(index);
		break;
	case ASN1BER::UtcTime:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_UtcTime(mConfig);
		break;
	case ASN1BER::TimeOfDay:
		ber = new ASN1BER(mConfig);
		ber->myValue = new IEC61850Value_TimeOfDay(mConfig);
		break;
	default:
		break;
	}
	return ber;
}

ASN1BER *ASN1BER::CreateContextBER(uint tagNo, uint index)
{
	mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
			 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	return NULL;
	/*
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		ber = CreateBERByTagNo(tagNo);
		if(!ber)
		{
			ber = CreateBERByType(myTagNoMap[tagNo].type, index);
		}
		if(ber)
		{
			ber->myGroup = myTagNoMap[tagNo];
			if(ber->myValue)
			{
				ber->myValue->myGroup = myTagNoMap[tagNo];
			}
		}
	}
	else
	{
		ber = CreateBERByIndex(index);
		if(ber)
		{
			ber->myGroup = myIndexMap[index];
			if(ber->myValue)
			{
				ber->myValue->myGroup = myIndexMap[index];
			}
		}
	}
	return ber;
	*/
}

ASN1BER *ASN1BER::CreateSequenceBER(uint index)
{
	return NULL;
}

void ASN1BER::setBERGroup(ASN1BER *ber, const BERGroup group)
{
	if(ber)
	{
		ber->myGroup = group;
		if(ber->myValue)
		{
			ber->myValue->myGroup = group;
		}
	}
}

//ASN1BER *ASN1BER::CreateBERByTagNo(uint tagNo)
//{
//	return NULL;
//}

//ASN1BER *ASN1BER::CreateBERByIndex(uint& index)
//{
//	return NULL;
//}

QString ASN1BER::tagNoToText(uint tagNo)
{
	QString text;
	text.append(QString("%1  ").arg(tagNo) + myGroup.des);
	return text;
}

QString ASN1BER::tagToText(uchar tag)
{
	QString text;
	text.append("标识Tag: 关键字(bit7-8): " + QString::number(tag & 0xc0, 16).toUpper() + " ");
	switch(tag >> 6)
	{
	case 0:
		text.append("Universal 通用类");
		break;
	case 1:
		text.append("Application 应用程序类");
		break;
	case 2:
		text.append("Context 上下文有关类");
		break;
	case 3:
		text.append("Private 私有类");
		break;
	default:
		break;
	}
	text.append("   P/C位(bit6):" + QString::number(tag & 0x20, 16).toUpper() + " ");
	text.append(tag & 0x20 ? QString("结构类型") : QString("简单类型"));
	return text;
}

bool ASN1BER::getTagNo(const QByteArray& buff, uchar& tag, uchar& tagNoLen, uint& tagNo)
{
	tag = *(buff.data() + mLen);
	tagNo = tag & 0x1f;
	tagNoLen = 0;
	if(tagNo == 0x1f)
	{
		uchar tmp = *(buff.data() + mLen + (++tagNoLen));
		tagNo = tmp & 0x7f;
		while(tmp & 0x80)
		{
			tmp = *(buff.data() + mLen + (++tagNoLen));
			tagNo = (tagNo << 7) + tmp & 0x7f;
		}
	}
	return true;
}

bool ASN1BER::getLength(const QByteArray& buff, uchar& lengthType, uchar& lengthLen, uint& length)
{
	lengthType = *(buff.data() + mLen);
	if(lengthType == 0x80)
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + "长度不确定形式\r\n");
		mLen++;
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！未解析此长度类型报文"));
		return false;
	}
	else if(lengthType & 0x80)
	{
		lengthLen = lengthType & 0x7f;
		mText.append(CharToHexStr(buff.data() + mLen) + "\t"  + QString::number(lengthLen) + "  长形式长度字节数" + "\r\n");
		mLen++;
		length = charTouint(buff.data() + mLen, lengthLen, 1);
		mText.append(CharToHexStr(buff.data() + mLen, lengthLen) + "\t"  + QString::number(length) + "  长形式长度" + "\r\n");
		mLen += lengthLen;
	}
	else if(lengthType == 0)
	{
		length = lengthType;
		mText.append(CharToHexStr(buff.data() + mLen) + "\t"  + QString::number(length) + "  NULL" + "\r\n");
		mLen++;
	}
	else
	{
		length = lengthType;
		mText.append(CharToHexStr(buff.data() + mLen) + "\t"  + QString::number(length) + "  长度" + "\r\n");
		mLen++;
	}
	return true;
}

