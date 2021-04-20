#include "iec104asdu116data.h"

IEC104Asdu116Data::IEC104Asdu116Data(const MyConfig& Config): IEC101AsduData(Config)
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC104Asdu116Data::~IEC104Asdu116Data()
{

}

bool IEC104Asdu116Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	dataType = *(buff.data() + mLen);
	switch(dataType)
	{
	case 1:
		mText.append(CharToHexStr(buff.data() + mLen) + "\t附加数据包类型: 程序化操作\r\n");
		mLen++;
		break;
	case 2:
		mText.append(CharToHexStr(buff.data() + mLen) + "\t附加数据包类型: 文件传输\r\n");
		mLen++;
		opFlag = *(buff.data() + mLen);
		switch(opFlag)
		{
		case 3:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 3 读文件激活\r\n");
			mLen++;
			fileNameSize = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			mLen++;
			QByteArray ba(buff.data() + mLen, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			mLen += fileNameSize;
			break;
		}
		case 4:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 4 读文件激活确认\r\n");
			mLen++;
			result = *(buff.data() + mLen) & 0x01;
			mText.append(CharToHexStr(buff.data() + mLen) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			mLen++;
			fileNameSize = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			mLen++;
			QByteArray ba(buff.data() + mLen, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			mLen += fileNameSize;
			fileID = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			mLen += 4;
			fileSize = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
			mLen += 4;
			break;
		}
		case 5:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 5 读文件数据响应\r\n");
			mLen++;
			fileID = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			mLen += 4;
			dataIndex = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			mLen += 4;
			isLast = *(buff.data() + mLen) & 0x01;
			mText.append(CharToHexStr(buff.data() + mLen) + "\t后续标志: " + QString(isLast ? "1 有后续" : "0 无后续") + "\r\n");
			mLen++;
			fileSize = buff.length() - mLen - 1;
			QByteArray ba(buff.data() + mLen, fileSize);
			fileData = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, fileSize) + "\t文件数据:  " + fileData + "\r\n");
			mLen += fileSize;

			crc = *(buff.data() + mLen);
			uchar sum = crcsum(buff.data(), mLen - fileSize, mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t校验码: " + QString(crc == sum ? "计算结果正确" : "计算结果错误") + "\r\n");
			mLen++;
			break;
		}
		case 6:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 6 读文件数据的传输确认\r\n");
			mLen++;
			fileID = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			mLen += 4;
			dataIndex = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			mLen += 4;
			result = *(buff.data() + mLen) & 0x01;
			mText.append(CharToHexStr(buff.data() + mLen) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			mLen++;
			break;
		}
		case 7:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 7 写文件激活\r\n");
			mLen++;
			fileNameSize = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			mLen++;
			QByteArray ba(buff.data() + mLen, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			mLen += fileNameSize;
			fileID = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			mLen += 4;
			fileSize = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
			mLen += 4;
			break;
		}
		case 8:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 8 写文件激活确认\r\n");
			mLen++;
			result = *(buff.data() + mLen) & 0x01;
			mText.append(CharToHexStr(buff.data() + mLen) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			mLen++;
			fileNameSize = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t文件名长度: " + QString::number(fileNameSize) + "\r\n");
			mLen++;
			QByteArray ba(buff.data() + mLen, fileNameSize);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, fileNameSize) + "\t文件名: " + fileName + "\r\n");
			mLen += fileNameSize;
			fileID = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			mLen += 4;
			fileSize = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
			mLen += 4;
			break;
		}
		case 9:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 9 写文件数据\r\n");
			mLen++;
			fileID = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			mLen += 4;
			dataIndex = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			mLen += 4;
			isLast = *(buff.data() + mLen) & 0x01;
			mText.append(CharToHexStr(buff.data() + mLen) + "\t后续标志: " + QString(isLast ? "1 有后续" : "0 无后续") + "\r\n");
			mLen++;
			fileSize = buff.length() - mLen - 1;
			QByteArray ba(buff.data() + mLen, fileSize);
			fileData = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, fileSize) + "\t文件数据:  " + fileData + "\r\n");
			mLen += fileSize;

			crc = *(buff.data() + mLen);
			uchar sum = crcsum(buff.data(), mLen - fileSize, mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t校验码: " + QString(crc == sum ? "计算结果正确" : "计算结果错误") + "\r\n");
			mLen++;
			break;
		}
		case 10:
		{
			mText.append(CharToHexStr(buff.data() + mLen) + "\t操作标识: 10 写文件数据的传输确认\r\n");
			mLen++;
			fileID = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件名ID: " + QString::number(fileID) + "\r\n");
			mLen += 4;
			dataIndex = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t数据段号(文件偏移): " + QString::number(dataIndex) + "\r\n");
			mLen += 4;
			result = *(buff.data() + mLen) & 0x01;
			mText.append(CharToHexStr(buff.data() + mLen) + "\t结果描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
			mLen++;
			break;
		}
		default:
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的文件传输标识");
			return false;
			break;
		}
		break;
	case 3:
		mText.append(CharToHexStr(buff.data() + mLen) + "\t附加数据包类型: IEC103通用分类服务数据\r\n");
		mLen++;
		break;
	case 4:
		mText.append(CharToHexStr(buff.data() + mLen) + "\t附加数据包类型: IEC102\r\n");
		mLen++;
		break;
	case 5:
		mText.append(CharToHexStr(buff.data() + mLen) + "\t附加数据包类型: 源端维护\r\n");
		mLen++;
		opFlag = *(buff.data() + mLen);
		switch(opFlag)
		{
		case 1:
			if(mLen + 1 == buff.length())
			{
				mText.append(CharToHexStr(buff.data() + mLen) + "\t命令标识: 1 四遥数据传输激活\r\n");
				mLen++;
			}
			else
			{
				mText.append(CharToHexStr(buff.data() + mLen) + "\t状态标识: 1 MAP文件校验\r\n");
				mLen++;
				result = *(buff.data() + mLen) & 0x01;
				mText.append(CharToHexStr(buff.data() + mLen) + "\t状态描述字: " + QString(result ? "1 失败" : "0 成功") + "\r\n");
				mLen++;
			}
			break;
		case 2:
			mText.append(CharToHexStr(buff.data() + mLen) + "\t命令标识: 2 四遥数据传输激活确认\r\n");
			mLen++;
			result = *(buff.data() + mLen) & 0x01;
			mText.append(CharToHexStr(buff.data() + mLen) + "\t结果描述字: " + QString(result ? "1 否定" : "0 肯定") + "\r\n");
			mLen++;
			break;
		default:
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的源端维护标识");
			return false;
			break;
		}
		break;
	default:
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的附加数据包类型");
		return false;
		break;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

