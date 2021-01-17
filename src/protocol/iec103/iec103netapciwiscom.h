#ifndef IEC103NETAPCIWISCOM_H
#define IEC103NETAPCIWISCOM_H


#include <iec104apci.h>

class IEC103NetApciWiscom  : public IEC104Apci
{
public:
	IEC103NetApciWiscom();
	~IEC103NetApciWiscom();
	virtual bool handle(const QByteArray& buff);				//单独处理多出来的数据
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar source_factory_addr;		//源厂站地址
	uchar source_dev_addr[2];		//源设备地址
	uchar destination_factory_addr;	//目的厂站地址
	uchar destination_dev_addr[2];	//目的设备地址
	uchar reserve[2];				//备用
};

#endif // IEC103NETAPCIWISCOM_H
