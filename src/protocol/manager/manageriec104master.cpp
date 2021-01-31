#include "manageriec104master.h"
#include "QtDebug"

ManagerIEC104Master::ManagerIEC104Master(const MyConfig& Config): protocolShow(Config), my104(Config)
{
	sSend = false;
	isMaster = true;
	mConfig = Config;
	asduAddr = 0;
	noDataTimes = 0;
}

ManagerIEC104Master::~ManagerIEC104Master()
{

}

void ManagerIEC104Master::timerRcv()
{
	if(!isRun)
	{
		return;
	}
	while(!rcvData.isEmpty())
	{
		if(my104.init(rcvData))
		{
			emit toText(my104.mRecvData.toHex(' ') + "\r\n" + my104.showToText(), 0);
			noDataTimes = 0;
			if(my104.apci.control.type == UTYPE)
			{
				if(my104.apci.control.code == 0x0b)
				{
					addSndData(asdu100Create());
					flag = STATE_CALLALL;
				}
				else if(my104.apci.control.code == 0x43)
				{
					flag = STATE_TESTCONFIRM;
				}
				else if(my104.apci.control.code == 0x83)
				{
					flag = STATE_TESTACT;
				}
			}
			else if(my104.apci.control.type == STYPE)
			{
				if(sndNo >= my104.apci.control.remoteRecvNo)
				{
					k = sndNo - my104.apci.control.remoteRecvNo;
				}
				else
				{
					k = 0;
				}
			}
			else if(my104.apci.control.type == ITYPE)
			{
				rcvNo = my104.apci.control.remoteSendNo + 1;
				w++;
				if(sndNo >= my104.apci.control.remoteRecvNo)
				{
					k = sndNo - my104.apci.control.remoteRecvNo;
				}
				else
				{
					k = 0;
				}
				if(w >= 8)
				{
					flag = STATE_NORMAL;
				}
				sSend = true;
			}
			rcvData.remove(0, my104.len);
		}
		else if(*rcvData.data() == 0x68 && (rcvData.size() == 1 || *(uchar *)(rcvData.data() + 1) + 2 > rcvData.size()))
		{
			break;
		}
		else
		{
			if(*rcvData.data() == 0x68 &&  *(uchar *)(rcvData.data() + 1) + 2 <= rcvData.size())
			{
				emit toLog("未识别的报文: " + rcvData.toHex(' '));
			}
			rcvData.remove(0, 1);
		}
	}
	noDataTimes++;
}

void ManagerIEC104Master::timerSnd()
{
	if(!isRun)
	{
		return;
	}
	if(flag == STATE_INIT)
	{
		static int i = 0;
		i++;
		if(i > 10)
		{
			i = 0;
			SendU(0x07);
		}
	}
	else if(flag == STATE_NORMAL || (sSend == true && noDataTimes > 10))
	{
		SendS();
		flag = STATE_NODATA;
		w = 0;
		sSend = false;
	}
	else if(flag == STATE_TESTACT)
	{
		SendU(0x43);
		flag = STATE_NODATA;
	}
	else if(flag == STATE_TESTCONFIRM)
	{
		SendU(0x83);
		flag = STATE_NODATA;
	}
	else if(!sndDatas.isEmpty())
	{
		if(k < 12)
		{
			SendI(sndDatas.takeFirst());
			k++;
			sndNo++;
			w = 0;
		}
	}
	else if(noDataTimes > 20)
	{
		flag = STATE_TESTACT;
		noDataTimes = 0;
	}
}

void ManagerIEC104Master::setAsduAddr(uint addr)
{
	asduAddr = addr;
}

QByteArray ManagerIEC104Master::SendU(uchar ch)
{
	QByteArray ba;
	ba += 0x68;
	ba += 0x04;
	ba += ch;
	ba += '\0';
	ba += '\0';
	ba += '\0';
	emit Send(ba);
	return ba;
}

QByteArray ManagerIEC104Master::SendS()
{
	QByteArray ba;
	ba += 0x68;
	ba += 0x04;
	ba += 0x01;
	ba += '\0';
	ba += uintToBa(rcvNo * 2, 2);
	emit Send(ba);
	return ba;
}

QByteArray ManagerIEC104Master::SendI(const QByteArray& data)
{
	if(data.size() > 249)
	{
		return NULL;
	}
	QByteArray ba;
	ba += 0x68;
	ba += data.size() + 4;
	ba += uintToBa(sndNo * 2, 2);
	ba += uintToBa(rcvNo * 2, 2);
	ba += data;
	emit Send(ba);
	return ba;
}

QByteArray ManagerIEC104Master::asdu100Create()
{
	QByteArray ba;
	ba += 0x64;
	ba += 0x01;
	ba += 0x06;
	ba += '\0';
	ba += uintToBa(asduAddr, 2);
	ba += '\0';
	ba += '\0';
	ba += '\0';
	ba += 0x14;
	return ba;
}
