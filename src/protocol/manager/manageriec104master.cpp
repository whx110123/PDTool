#include "manageriec104master.h"
#include "QtDebug"

#include <iec101asdu100data.h>
#include <iec101asdu103data.h>


ConfigIEC104Master::ConfigIEC104Master()
{

}

ConfigIEC104Master::~ConfigIEC104Master()
{

}

ManagerIEC104Master::ManagerIEC104Master(const MyConfig& Config): protocolShow(Config), myPro(Config)
{
	sSend = false;
	isMaster = true;
	mConfig = Config;
	asduAddr = 0;
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
			emit toText(myPro.mRecvData.toHex(' ') + "\r\n" + myPro.showToText(), 0);
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
				if(w >= 8)
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
			mutexSD.lock();
			QByteArray Ba = sndDatas.takeFirst();
			mutexSD.unlock();

			SendI(Ba);
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

void ManagerIEC104Master::initMyConfig(ManagerConfig *config)
{
	ConfigIEC104Master *myConfig = (ConfigIEC104Master *)config;
	asduAddr = myConfig->asduAddr;
}

QByteArray ManagerIEC104Master::SendU(uchar ch)
{
	MyData sendData;
	IEC104Apci c104(mConfig);
//	c104.first = 0x68;
//	c104.length = 0x04;
	c104.control.type = UTYPE;
	c104.control.code = ch;
	if(c104.createData(sendData))
	{
		emit Send(sendData.data);
	}
	return sendData.data;

//	QByteArray ba;
//	ba += 0x68;
//	ba += 0x04;
//	ba += ch;
//	ba += '\0';
//	ba += '\0';
//	ba += '\0';
//	emit Send(ba);
//	return ba;

}

QByteArray ManagerIEC104Master::SendS()
{
	MyData sendData;
	IEC104Apci apci(mConfig);
//	apci.first = 0x68;
//	apci.length = 0x04;
	apci.control.type = STYPE;
	apci.control.localRecvNo = rcvNo;
	if(apci.createData(sendData))
	{
		emit Send(sendData.data);
	}
	return sendData.data;

//	QByteArray ba;
//	ba += 0x68;
//	ba += 0x04;
//	ba += 0x01;
//	ba += '\0';
//	ba += uintToBa(rcvNo * 2, 2);
//	emit Send(ba);
//	return ba;
}

QByteArray ManagerIEC104Master::SendI(const QByteArray& data)
{
	if(data.size() > 249)
	{
		return NULL;
	}
	MyData sendData;
	sendData.data += data;
	IEC104Apci apci(mConfig);
//	apci.first = 0x68;
//	apci.length = 0x04 + data.size();
	apci.control.type = ITYPE;
	apci.control.localSendNo = sndNo;
	apci.control.localRecvNo = rcvNo;
	sendData.reverse = true;
	if(apci.createData(sendData))
	{
		emit Send(sendData.data);
	}
	return sendData.data;

//	QByteArray ba;
//	ba += 0x68;
//	ba += data.size() + 4;
//	ba += uintToBa(sndNo * 2, 2);
//	ba += uintToBa(rcvNo * 2, 2);
//	ba += data;
//	emit Send(ba);
//	return ba;
}

QByteArray ManagerIEC104Master::asdu100Create()
{
	MyData sendData;
	IEC101Asdu asdu(mConfig);
	asdu.type = 0x64;
	asdu.vsq = 0x01;
	asdu.cot[0] = 0x06;
	asdu.commonaddr = asduAddr;

	IEC101Asdu100Data *asduData  = new IEC101Asdu100Data(mConfig);
	asdu.datalist.append(asduData);

	asduData->infaddr = 0;
	asduData->qoi = 0x14;

	asdu.createData(sendData);
	return sendData.data;

//	QByteArray ba;
//	ba += 0x64;
//	ba += 0x01;
//	ba += 0x06;
//	ba += '\0';
//	ba += uintToBa(asduAddr, 2);
//	ba += '\0';
//	ba += '\0';
//	ba += '\0';
//	ba += 0x14;
	//	return ba;
}

QByteArray ManagerIEC104Master::asdu103Create()
{
	MyData sendData;
	IEC101Asdu asdu(mConfig);
	asdu.type = 0x67;
	asdu.vsq = 0x01;
	asdu.cot[0] = 0x06;
	asdu.commonaddr = asduAddr;

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

