#include "iec61850value_bitstring.h"

IEC61850Value_BitString::IEC61850Value_BitString(const MyConfig& Config): ASN1BERValue(Config)
{

}

IEC61850Value_BitString::~IEC61850Value_BitString()
{

}

bool IEC61850Value_BitString::init(const QByteArray& buff)
{
	setDefault(buff);
	uchar padding = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + QString::number(padding) + " 比特串填充数\r\n");
	mLen++;
	initValueMap();
	if(mLen < buff.length())
	{
		uint num = (buff.length() - 1) * 8 - padding;
		uchar tmp = 0;
		for(uint i = 0; i < num; i++)
		{
			if((i % 8) == 0)
			{
				tmp = *(buff.data() + mLen);
				mText.append(CharToHexStr(buff.data() + mLen));
				mLen++;
			}
			QString ret = (tmp << (i % 8)) & 0x80 ? "True " : "False";
			mText.append("\t" + ret + "   " + QString::number(i) + "  " + valueMap[i] + "\r\n");
		}
	}
	mText.append("----------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

void IEC61850Value_BitString::initValueMap()
{
	valueMap.clear();
	//初始化
	{
		valueMap.insert(0, "");
		valueMap.insert(1, "");
		valueMap.insert(2, "");
		valueMap.insert(3, "");
		valueMap.insert(4, "");
		valueMap.insert(5, "");
		valueMap.insert(6, "");
		valueMap.insert(7, "");
		valueMap.insert(8, "");
		valueMap.insert(9, "");
		valueMap.insert(10, "");
		valueMap.insert(11, "");
		valueMap.insert(12, "");
		valueMap.insert(13, "");
		valueMap.insert(14, "");
		valueMap.insert(15, "");
		valueMap.insert(16, "");
		valueMap.insert(17, "");
		valueMap.insert(18, "");
		valueMap.insert(19, "");
		valueMap.insert(20, "");
		valueMap.insert(21, "");
		valueMap.insert(22, "");
		valueMap.insert(23, "");
		valueMap.insert(24, "");
		valueMap.insert(25, "");
		valueMap.insert(26, "");
		valueMap.insert(27, "");
		valueMap.insert(28, "");
		valueMap.insert(29, "");
		valueMap.insert(30, "");
		valueMap.insert(31, "");
		valueMap.insert(32, "");
		valueMap.insert(33, "");
		valueMap.insert(34, "");
		valueMap.insert(35, "");
		valueMap.insert(36, "");
		valueMap.insert(37, "");
		valueMap.insert(38, "");
		valueMap.insert(39, "");
		valueMap.insert(40, "");
		valueMap.insert(41, "");
		valueMap.insert(42, "");
		valueMap.insert(43, "");
		valueMap.insert(44, "");
		valueMap.insert(45, "");
		valueMap.insert(46, "");
		valueMap.insert(47, "");
		valueMap.insert(48, "");
		valueMap.insert(49, "");
		valueMap.insert(50, "");
		valueMap.insert(51, "");
		valueMap.insert(52, "");
		valueMap.insert(53, "");
		valueMap.insert(54, "");
		valueMap.insert(55, "");
		valueMap.insert(56, "");
		valueMap.insert(57, "");
		valueMap.insert(58, "");
		valueMap.insert(59, "");
		valueMap.insert(60, "");
		valueMap.insert(61, "");
		valueMap.insert(62, "");
		valueMap.insert(63, "");
		valueMap.insert(64, "");
		valueMap.insert(65, "");
		valueMap.insert(66, "");
		valueMap.insert(67, "");
		valueMap.insert(68, "");
		valueMap.insert(69, "");
		valueMap.insert(70, "");
		valueMap.insert(71, "");
		valueMap.insert(72, "");
		valueMap.insert(73, "");
		valueMap.insert(74, "");
		valueMap.insert(75, "");
		valueMap.insert(76, "");
		valueMap.insert(77, "");
		valueMap.insert(78, "");
		valueMap.insert(79, "");
		valueMap.insert(80, "");
		valueMap.insert(81, "");
		valueMap.insert(82, "");
		valueMap.insert(83, "");
		valueMap.insert(84, "");
		valueMap.insert(85, "");
		valueMap.insert(86, "");
		valueMap.insert(87, "");
		valueMap.insert(88, "");
		valueMap.insert(89, "");
		valueMap.insert(90, "");
		valueMap.insert(91, "");
		valueMap.insert(92, "");
		valueMap.insert(93, "");
		valueMap.insert(94, "");
		valueMap.insert(95, "");
		valueMap.insert(96, "");
		valueMap.insert(97, "");
		valueMap.insert(98, "");
		valueMap.insert(99, "");
	}
	if(myGroup.typeDes.contains("ParameterSupportOptions"))
	{
		valueMap.insert(0, "str1");
		valueMap.insert(1, "str2");
		valueMap.insert(2, "vnam");
		valueMap.insert(3, "valt");
		valueMap.insert(4, "vadr");
		valueMap.insert(5, "vsca");
		valueMap.insert(6, "tpy");
		valueMap.insert(7, "vlis");
		valueMap.insert(8, "reserved");
		valueMap.insert(9, "reserved");
		valueMap.insert(10, "cei");
		valueMap.insert(11, "aco");
		valueMap.insert(12, "sem");
		valueMap.insert(13, "csr");
		valueMap.insert(14, "csnc");
		valueMap.insert(15, "csplc");
		valueMap.insert(16, "cspi");
		valueMap.insert(17, "char");
	}
	else if(myGroup.typeDes.contains("ServiceSupportOptions"))
	{
		valueMap.insert(0, "status");
		valueMap.insert(1, "getNameList");
		valueMap.insert(2, "identify");
		valueMap.insert(3, "rename");
		valueMap.insert(4, "read");
		valueMap.insert(5, "write");
		valueMap.insert(6, "getVariableAccessAttributes");
		valueMap.insert(7, "defineNamedVariable");
		valueMap.insert(8, "defineScatteredAccess");
		valueMap.insert(9, "getScatteredAccessAttributes");
		valueMap.insert(10, "deleteVariableAccess");
		valueMap.insert(11, "defineNamedVariableList");
		valueMap.insert(12, "getNamedVariableListAttributes");
		valueMap.insert(13, "deleteNamedVariableList");
		valueMap.insert(14, "defineNamedType");
		valueMap.insert(15, "getNamedTypeAttributes");
		valueMap.insert(16, "deleteNamedType");
		valueMap.insert(17, "input");
		valueMap.insert(18, "output");
		valueMap.insert(19, "takeControl");
		valueMap.insert(20, "relinquishControl");
		valueMap.insert(21, "defineSemaphore");
		valueMap.insert(22, "deleteSemaphore");
		valueMap.insert(23, "reportSemaphoreStatus");
		valueMap.insert(24, "reportPoolSemaphoreStatus");
		valueMap.insert(25, "reportSemaphoreEntryStatus");
		valueMap.insert(26, "initiateDownloadSequence");
		valueMap.insert(27, "downloadSegment");
		valueMap.insert(28, "terminateDownloadSequence");
		valueMap.insert(29, "initiateUploadSequence");
		valueMap.insert(30, "uploadSegment");
		valueMap.insert(31, "terminateUploadSequence");
		valueMap.insert(32, "requestDomainDownload");
		valueMap.insert(33, "requestDomainUpload");
		valueMap.insert(34, "loadDomainContent");
		valueMap.insert(35, "storeDomainContent");
		valueMap.insert(36, "deleteDomain");
		valueMap.insert(37, "getDomainAttributes");
		valueMap.insert(38, "createProgramInvocation");
		valueMap.insert(39, "deleteProgramInvocation");
		valueMap.insert(40, "start");
		valueMap.insert(41, "stop");
		valueMap.insert(42, "resume");
		valueMap.insert(43, "reset");
		valueMap.insert(44, "kill");
		valueMap.insert(45, "getProgramInvocationAttributes");
		valueMap.insert(46, "obtainFile");
		valueMap.insert(47, "defineEventCondition");
		valueMap.insert(48, "deleteEventCondition");
		valueMap.insert(49, "getEventConditionAttributes");
		valueMap.insert(50, "reportEventConditionStatus");
		valueMap.insert(51, "alterEventConditionMonitoring");
		valueMap.insert(52, "triggerEvent");
		valueMap.insert(53, "defineEventAction");
		valueMap.insert(54, "deleteEventAction");
		valueMap.insert(55, "getEventActionAttributes");
		valueMap.insert(56, "reportEventActionStatus");
		valueMap.insert(57, "defineEventEnrollment");
		valueMap.insert(58, "deleteEventEnrollment");
		valueMap.insert(59, "alterEventEnrollment");
		valueMap.insert(60, "reportEventEnrollmentStatus");
		valueMap.insert(61, "getEventEnrollmentAttributes");
		valueMap.insert(62, "acknowledgeEventNotification");
		valueMap.insert(63, "getAlarmSummary");
		valueMap.insert(64, "getAlarmEnrollmentSummary");
		valueMap.insert(65, "readJournal");
		valueMap.insert(66, "writeJournal");
		valueMap.insert(67, "initializeJournal");
		valueMap.insert(68, "reportJournalStatus");
		valueMap.insert(69, "createJournal");
		valueMap.insert(70, "deleteJournal");
		valueMap.insert(71, "getCapabilityList");
		valueMap.insert(72, "fileOpen");
		valueMap.insert(73, "fileRead");
		valueMap.insert(74, "fileClose");
		valueMap.insert(75, "fileRename");
		valueMap.insert(76, "fileDelete");
		valueMap.insert(77, "fileDirectory");
		valueMap.insert(78, "unsolicitedStatus");
		valueMap.insert(79, "informationReport");
		valueMap.insert(80, "eventNotification");
		valueMap.insert(81, "attachToEventCondition");
		valueMap.insert(82, "attachToSemaphore");
		valueMap.insert(83, "conclude");
		valueMap.insert(84, "cancel");
		valueMap.insert(85, "getDataExchangeAttributes");
		valueMap.insert(86, "exchangeData");
		valueMap.insert(87, "defineAccessControlList");
		valueMap.insert(88, "getAccessControlListAttributes");
		valueMap.insert(89, "reportAccessControlledObjects");
		valueMap.insert(90, "deleteAccessControlList");
		valueMap.insert(91, "alterAccessControl");
		valueMap.insert(92, "reconfigureProgramInvocation");
	}
	else if(myGroup.typeDes.contains("AdditionalSupportOptions"))
	{
		valueMap.insert(0, "vMDStop");
		valueMap.insert(1, "vMDReset");
		valueMap.insert(2, "select");
		valueMap.insert(3, "alterProgramInvocationAttributes");
		valueMap.insert(4, "initiateUnitControlLoad");
		valueMap.insert(5, "unitControlLoadSegment");
		valueMap.insert(6, "unitControlUpload");
		valueMap.insert(7, "startUnitControl");
		valueMap.insert(8, "stopUnitControl");
		valueMap.insert(9, "createUnitControl");
		valueMap.insert(10, "addToUnitControl");
		valueMap.insert(11, "removeFromUnitControl");
		valueMap.insert(12, "getUnitControlAttributes");
		valueMap.insert(13, "loadUnitControlFromFile");
		valueMap.insert(14, "storeUnitControlToFile");
		valueMap.insert(15, "deleteUnitControl");
		valueMap.insert(16, "defineEventConditionList");
		valueMap.insert(17, "deleteEventConditionList");
		valueMap.insert(18, "addEventConditionListReference");
		valueMap.insert(19, "removeEventConditionListReference");
		valueMap.insert(20, "getEventConditionListAttributes");
		valueMap.insert(21, "reportEventConditionListStatus");
		valueMap.insert(22, "alterEventConditionListMonitoring");
	}
	else if(myGroup.typeDes.contains("AdditionalCBBOptions"))
	{
		valueMap.insert(0, "des");
		valueMap.insert(1, "dei");
		valueMap.insert(2, "recl");
	}
}
