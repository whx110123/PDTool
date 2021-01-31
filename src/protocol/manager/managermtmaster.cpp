#include "managermtmaster.h"

ManagerMTMaster::ManagerMTMaster(const MyConfig& Config): protocolShow(Config), myMT(Config)
{
	noDataTimes = 0;
	pseq = 0;
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
		if(myMT.init(rcvData))
		{
			emit toText(myMT.mRecvData.toHex(' ') + "\r\n" + myMT.showToText(), 0);
			noDataTimes = 0;
			rcvData.remove(0, myMT.len);
		}
		else if(*rcvData.data() == 0x68 && (rcvData.size() < 3 || charToint(rcvData.data() + 1, 2) + 4 > rcvData.size()))
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

void ManagerMTMaster::timerSnd()
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
//			SendU(0x07);
		}
	}
	else if(!sndDatas.isEmpty())
	{
		SendAFN(sndDatas.takeFirst());
	}
	else if(noDataTimes > 20)
	{
		flag = STATE_TESTACT;
		noDataTimes = 0;
	}
}

void ManagerMTMaster::setAddr(uint a1, uint a2, uchar a3)
{
	A1 = a1;
	A2 = a2;
	A3 = a3;
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
	ba += 0x68;
	ba += createCode(*(uchar *)data.data());
	ba += uintToBa(A1, 3);
	ba += uintToBa(A2, 3);
	ba += uintToBa(A3, 1);
	ba += data;
	ba += crcsum(ba.data(), 4, data.size() + 11);
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
		code += fcv;	//帧计数有效位FCV
		code |= fcb;
	}

	code += 0x40;	//启动标志位PRM
	return code;
}

QByteArray ManagerMTMaster::afn2Create()
{
	QByteArray ba;
	ba += 0x02;
	ba += 0x70 + pseq & 0x0f;

	return ba;
}
