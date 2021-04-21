#include "managermtmaster.h"

ConfigMTMaster::ConfigMTMaster()
{

}

ConfigMTMaster::~ConfigMTMaster()
{

}

ManagerMTMaster::ManagerMTMaster(const MyConfig& Config): protocolShow(Config), myPro(Config)
{
	noDataTimes = 0;
	pseq = 0;
	fcb = 0;
}

ManagerMTMaster::~ManagerMTMaster()
{

}

void ManagerMTMaster::timerRcv()
{
	if(!isRun)
	{
		return;
	}
	while(!rcvData.isEmpty())
	{
		if(myPro.init(rcvData))
		{
			MyLog log;
			log.type = MyLog::RECVDATA;
			log.text = myPro.mRecvData.toHex(' ') + "\r\n" + myPro.showToText();
			emit toLog(log);
			noDataTimes = 0;
			if(myPro.asdu.afn == 0)
			{
				flag = STATE_NODATA;
			}
			fcbchange();
			mutexRD.lock();
			rcvData.remove(0, myPro.mLen);
			mutexRD.unlock();
		}
		else if(rcvData.size() < 6)
		{
			break;
		}
		else if(*rcvData.data() == 0x68 && *(rcvData.data() + 5) == 0x68)
		{
			if(charToint(rcvData.data() + 1, 2) == charToint(rcvData.data() + 3, 2))
			{
				if(charToint(rcvData.data() + 1, 2) + 6 > rcvData.size())
				{
					break;
				}
				else
				{
					MyLog log;
					log.type = MyLog::ERRORLOG;
					log.text = "未识别的报文: " + rcvData.toHex(' ') + "\r\n" + myPro.mError;
					emit toLog(log);
				}
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
	noDataTimes++;
}

void ManagerMTMaster::timerSnd()
{
	if(!isRun)
	{
		return;
	}

	if(!sndDatas.isEmpty())
	{
		mutexSD.lock();
		QByteArray Ba = sndDatas.takeFirst();
		mutexSD.unlock();
		SendAFN(Ba);
	}
	else if(flag == STATE_INIT)
	{
		static int i = 0;
		i++;
		if(i > 10)
		{
			i = 0;
			addSndData(afn2Create(0));
		}
	}
	else if(noDataTimes > 20)
	{
		flag = STATE_TESTACT;
		noDataTimes = 0;
	}
}

void ManagerMTMaster::initProConfig(ConfigMTMaster *config)
{
	proConfig = *config;
}

QByteArray ManagerMTMaster::SendAFN(const QByteArray& data)
{
	if(data.size() > 16383 || data.size() < 1)
	{
		return NULL;
	}
	ushort length = data.size() + 8;
	QByteArray ba;
	ba += 0x68;
	ba += uintToBa(length, 2);
	ba += uintToBa(length, 2);
	ba += 0x68;
	ba += createCode(*(uchar *)data.data());
	ba += uintToBa(proConfig.A1, 3);
	ba += uintToBa(proConfig.A2, 3);
	ba += uintToBa(proConfig.A3, 1);
	ba += data;

	uchar *mdata = (uchar *)ba.data();
	mdata[15] |= (pseq++ & 0x0f);

	ba += crcsum(ba.data(), 6, data.size() + 13);
	ba += 0x16;
	emit Send(ba);
	return ba;
}

uchar ManagerMTMaster::createCode(uchar afn)
{
	uchar code = 0;
	uchar fcv = 0;
	switch(afn)
	{
	case 1:
		code = 1;
		break;
	case 2:
		code = 9;
		break;
	case 4:
		code = 10;
		fcv = 0x10;
		break;
	case 6:
	case 10:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 18:
	case 19:
	case 20:
	case 21:
		code = 11;
		fcv = 0x10;
		break;
	default:
		break;
	}
	if(fcv)
	{
		code += fcv | fcb;	//帧计数有效位FCV
	}

	code += 0x40;	//启动标志位PRM
	return code;
}

QByteArray ManagerMTMaster::afn2Create(uchar DI0)
{
	QByteArray ba;
	ba += 0x02;
	ba += 0x70;
	ba += uintToBa(0, 2);
	ba += DI0;
	ba += uintToBa(0xe00010, 3);
	return ba;
}

void ManagerMTMaster::fcbchange()
{
	if(fcb)
	{
		fcb = 0;
	}
	else
	{
		fcb = 0x20;
	}
}


