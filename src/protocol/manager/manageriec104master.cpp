#include "manageriec104master.h"
#include "QtDebug"

#include <iec101asdu100data.h>
#include <iec101asdu103data.h>


ConfigIEC104Master::ConfigIEC104Master()
{
	isMaster = true;
	asduAddr = 0;
	t1 = 15;
	t2 = 10;
	t3 = 20;
	kMax = 12;
	wMax = 8;
}

ConfigIEC104Master::~ConfigIEC104Master()
{

}

ManagerIEC104Master::ManagerIEC104Master(const MyConfig& Config): protocolShow(Config), myPro(Config)
{
	sSend = false;
	mConfig = Config;
	noDataTimes = 0;
	SecondTimer = new QTimer(this);
	connect(SecondTimer, &QTimer::timeout, this, &ManagerIEC104Master::update);
	SecondTimer->start(1000);
}

ManagerIEC104Master::~ManagerIEC104Master()
{

}

void ManagerIEC104Master::restoreDefaults()
{
	sndNo = 0;
	rcvNo = 0;
	k = 0;
	w = 0;
	noDataTimes = 0;
}

void ManagerIEC104Master::timerRcv()
{
	if(!isRun)
	{
		return;
	}
	while(!rcvData.isEmpty())
	{
		if(myPro.init(rcvData))
		{
			emit toText(myPro.mRecvData.toHex(' ') + "\r\n" + myPro.showToText());
			noDataTimes = 0;
			if(myPro.apci.control.type == UTYPE)
			{
				if(myPro.apci.control.code == 0x0b)
				{
					addSndData(asdu100Create());
					flag = STATE_CALLALL;
				}
				else if(myPro.apci.control.code == 0x43)
				{
					flag = STATE_TESTCONFIRM;
				}
				else if(myPro.apci.control.code == 0x83)
				{
					//flag = STATE_TESTACT;
					flag = STATE_NODATA;
				}
			}
			else if(myPro.apci.control.type == STYPE)
			{
				if(sndNo >= myPro.apci.control.remoteRecvNo)
				{
					k = sndNo - myPro.apci.control.remoteRecvNo;
				}
				else
				{
					k = 0;
				}
			}
			else if(myPro.apci.control.type == ITYPE)
			{
				rcvNo = myPro.apci.control.remoteSendNo + 1;
				w++;
				if(sndNo >= myPro.apci.control.remoteRecvNo)
				{
					k = sndNo - myPro.apci.control.remoteRecvNo;
				}
				else
				{
					k = 0;
				}
				flag = STATE_NODATA;
				if(w >= proConfig.wMax)
				{
					flag = STATE_NORMAL;
				}
				sSend = true;
			}
			mutexRD.lock();
			rcvData.remove(0, myPro.mLen);
			mutexRD.unlock();
		}
		else if(rcvData.size() < 6)
		{
			break;
		}
		else if(*rcvData.data() == 0x68)
		{
			if(*(uchar *)(rcvData.data() + 1) + 2 > rcvData.size())
			{
				break;
			}
			else
			{
				emit toLog("未识别的报文: " + rcvData.toHex(' ') + "\r\n" + myPro.mError);
			}
			mutexRD.lock();
			rcvData.remove(0, 1);
			mutexRD.unlock();
		}
		else
		{
			mutexRD.lock();
			rcvData.remove(0, 1);
			mutexRD.unlock();
		}

	}

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
	else if(flag == STATE_NORMAL || (sSend == true && noDataTimes > proConfig.t2))
	{
		SendS();
	}
	else if(flag == STATE_TESTACT)
	{
		SendU(0x43);
	}
	else if(flag == STATE_TESTCONFIRM)
	{
		SendU(0x83);
	}
	else if(!sndDatas.isEmpty() && k < proConfig.kMax)
	{
		mutexSD.lock();
		QByteArray Ba = sndDatas.takeFirst();
		mutexSD.unlock();

		SendI(Ba);
	}
	else if(noDataTimes > proConfig.t3)
	{
		flag = STATE_TESTACT;
		noDataTimes = 0;
	}
}

void ManagerIEC104Master::initProConfig(ConfigIEC104Master *config)
{
	proConfig = *config;
}

QByteArray ManagerIEC104Master::SendU(uchar ch)
{
	MyData sendData;
	IEC104Apci apci(mConfig);

	apci.control.type = UTYPE;
	apci.control.code = ch;
	if(apci.createData(sendData))
	{
		emit Send(sendData.data);
	}

	flag = STATE_NODATA;

	return sendData.data;
}

QByteArray ManagerIEC104Master::SendS()
{
	MyData sendData;
	IEC104Apci apci(mConfig);

	apci.control.type = STYPE;
	apci.control.localRecvNo = rcvNo;
	if(apci.createData(sendData))
	{
		emit Send(sendData.data);
	}

	w = 0;
	sSend = false;
	flag = STATE_NODATA;

	return sendData.data;
}

QByteArray ManagerIEC104Master::SendI(const QByteArray& data)
{
	if(data.isEmpty() || data.size() > 249)
	{
		return NULL;
	}
	MyData sendData;
	sendData.data += data;
	IEC104Apci apci(mConfig);

	apci.control.type = ITYPE;
	apci.control.localSendNo = sndNo;
	apci.control.localRecvNo = rcvNo;
	sendData.reverse = true;
	if(apci.createData(sendData))
	{
		emit Send(sendData.data);
	}

	k++;
	sndNo++;
	w = 0;

	return sendData.data;
}

QByteArray ManagerIEC104Master::asdu100Create()
{
	MyData sendData;
	IEC101Asdu asdu(mConfig);
	asdu.type = 0x64;
	asdu.vsq = 0x01;
	asdu.cot[0] = 0x06;
	asdu.commonaddr = proConfig.asduAddr;

	IEC101Asdu100Data *asduData  = new IEC101Asdu100Data(mConfig);
	asdu.datalist.append(asduData);

	asduData->infaddr = 0;
	asduData->qoi = 0x14;

	asdu.createData(sendData);
	return sendData.data;
}

QByteArray ManagerIEC104Master::asdu103Create()
{
	MyData sendData;
	IEC101Asdu asdu(mConfig);
	asdu.type = 0x67;
	asdu.vsq = 0x01;
	asdu.cot[0] = 0x06;
	asdu.commonaddr = proConfig.asduAddr;

	IEC101Asdu103Data *asduData  = new IEC101Asdu103Data(mConfig);
	asdu.datalist.append(asduData);

	asduData->infaddr = 0;
	asduData->datetime = QDateTime::currentDateTime();

	asdu.createData(sendData);
	return sendData.data;
}

void ManagerIEC104Master::update()
{
	noDataTimes++;
}

