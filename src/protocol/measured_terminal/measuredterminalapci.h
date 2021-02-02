#ifndef MEASUREDTERMINALAPCI_H
#define MEASUREDTERMINALAPCI_H

#include <iec101apci.h>


class MTApci : public MyBase
{
public:
	MTApci(const MyConfig& Config);
	~MTApci();
	virtual bool init(const QByteArray& buff);

public:
	uchar flag;				//启动字符
	ushort length;			//长度域
	IEC101Code code;		//功能码
	uint A1;				//省地市区县码
	uint A2;				//终端地址
	uchar A3;				//主站地址
private:
	QString A1ToText();
};

#endif // MEASUREDTERMINALAPCI_H
