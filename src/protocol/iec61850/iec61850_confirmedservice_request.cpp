#include "iec61850_additionalservice_request.h"
#include "iec61850_confirmedservice_request.h"
#include "iec61850_getnamelist_request.h"
#include "iec61850_getvariableaccessattributes_request.h"
#include "iec61850_objectname.h"
#include "iec61850_read_request.h"
#include "iec61850_write_request.h"

IEC61850_ConfirmedService_Request::IEC61850_ConfirmedService_Request(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ConfirmedService_Request::~IEC61850_ConfirmedService_Request()
{

}

void IEC61850_ConfirmedService_Request::initMap()
{
	BERGroup group;

	myTagNoMap.clear();

	/*
		uint tagNo = 0;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 1;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 2;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 3;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 4;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 5;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 6;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 7;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 8;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);

		tagNo = 9;
		group.type = ASN1BER::Sequence;
		group.typeDes = "IMPLICIT ";
		group.des = "";
		myTagNoMap.insert(tagNo, group);
	*/
	uint tagNo = 0;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Status-Request";
	group.des = "Status-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetNameList-Request";
	group.des = "GetNameList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Identify-Request";
	group.des = "Identify-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Rename-Request";
	group.des = "Rename-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Read-Request";
	group.des = "Read-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Write-Request";
	group.des = "Write-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "IMPLICIT GetVariableAccessAttributes-Request";
	group.des = "GetVariableAccessAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineNamedVariable-Request";
	group.des = "DefineNamedVariable-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineScatteredAccess-Request";
	group.des = "DefineScatteredAccess-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetScatteredAccessAttributes-Request";
	group.des = "GetScatteredAccessAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteVariableAccess-Request";
	group.des = "DeleteVariableAccess-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineNamedVariableList-Request";
	group.des = "DefineNamedVariableList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "IMPLICIT GetNamedVariableListAttributes-Request";
	group.des = "GetNamedVariableListAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 13;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteNamedVariableList-Request";
	group.des = "DeleteNamedVariableList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 14;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineNamedType-Request";
	group.des = "DefineNamedType-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 15;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetNamedTypeAttributes-Request";
	group.des = "GetNamedTypeAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 16;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteNamedType-Request";
	group.des = "DeleteNamedType-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 17;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Input-Request";
	group.des = "Input-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 18;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Output-Request";
	group.des = "Output-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 19;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TakeControl-Request";
	group.des = "TakeControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 20;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RelinquishControl-Request";
	group.des = "RelinquishControl-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 21;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineSemaphore-Request";
	group.des = "DefineSemaphore-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 22;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteSemaphore-Request";
	group.des = "DeleteSemaphore-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 23;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportSemaphoreStatus-Request";
	group.des = "ReportSemaphoreStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 24;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportPoolSemaphoreStatus-Request";
	group.des = "ReportPoolSemaphoreStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 25;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportSemaphoreEntryStatus-Request";
	group.des = "ReportSemaphoreEntryStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 26;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitiateDownloadSequence-Request";
	group.des = "InitiateDownloadSequence-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 27;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DownloadSegment-Request";
	group.des = "DownloadSegment-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 28;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TerminateDownloadSequence-Request";
	group.des = "TerminateDownloadSequence-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 29;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitiateUploadSequence-Request";
	group.des = "InitiateUploadSequence-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 30;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT UploadSegment-Request";
	group.des = "UploadSegment-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 31;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TerminateUploadSequence-Request";
	group.des = "TerminateUploadSequence-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 32;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RequestDomainDownload-Request";
	group.des = "RequestDomainDownload-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 33;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RequestDomainUpload-Request";
	group.des = "RequestDomainUpload-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 34;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT LoadDomainContent-Request";
	group.des = "LoadDomainContent-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 35;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StoreDomainContent-Request";
	group.des = "StoreDomainContent-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 36;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteDomain-Request";
	group.des = "DeleteDomain-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 37;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetDomainAttributes-Request";
	group.des = "GetDomainAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 38;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CreateProgramInvocation-Request";
	group.des = "CreateProgramInvocation-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 39;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteProgramInvocation-Request";
	group.des = "DeleteProgramInvocation-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 40;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Start-Request";
	group.des = "Start-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 41;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Stop-Request";
	group.des = "Stop-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 42;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Resume-Request";
	group.des = "Resume-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 43;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Reset-Request";
	group.des = "Reset-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 44;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Kill-Request";
	group.des = "Kill-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 45;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetProgramInvocationAttributes-Request";
	group.des = "GetProgramInvocationAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 46;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ObtainFile-Request";
	group.des = "ObtainFile-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 47;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventCondition-Request";
	group.des = "DefineEventCondition-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 48;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventCondition-Request";
	group.des = "DeleteEventCondition-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 49;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventConditionAttributes-Request";
	group.des = "GetEventConditionAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 50;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventConditionStatus-Request";
	group.des = "ReportEventConditionStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 51;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterEventConditionMonitoring-Request";
	group.des = "AlterEventConditionMonitoring-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 52;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TriggerEvent-Request";
	group.des = "TriggerEvent-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 53;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventAction-Request";
	group.des = "DefineEventAction-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 54;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventAction-Request";
	group.des = "DeleteEventAction-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 55;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventActionAttributes-Request";
	group.des = "GetEventActionAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 56;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventActionStatus-Request";
	group.des = "ReportEventActionStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 57;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventEnrollment-Request";
	group.des = "DefineEventEnrollment-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 58;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventEnrollment-Request";
	group.des = "DeleteEventEnrollment-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 59;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterEventEnrollment-Request";
	group.des = "AlterEventEnrollment-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 60;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventEnrollmentStatus-Request";
	group.des = "ReportEventEnrollmentStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 61;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventEnrollmentAttributes-Request";
	group.des = "GetEventEnrollmentAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 62;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AcknowledgeEventNotification-Request";
	group.des = "AcknowledgeEventNotification-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 63;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetAlarmSummary-Request";
	group.des = "GetAlarmSummary-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 64;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetAlarmEnrollmentSummary-Request";
	group.des = "GetAlarmEnrollmentSummary-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 65;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReadJournal-Request";
	group.des = "ReadJournal-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 66;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT WriteJournal-Request";
	group.des = "WriteJournal-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 67;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitializeJournal-Request";
	group.des = "InitializeJournal-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 68;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportJournalStatus-Request";
	group.des = "ReportJournalStatus-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 69;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CreateJournal-Request";
	group.des = "CreateJournal-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 70;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteJournal-Request";
	group.des = "DeleteJournal-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 71;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetCapabilityList-Request";
	group.des = "GetCapabilityList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 72;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileOpen-Request";
	group.des = "FileOpen-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 73;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileRead-Request";
	group.des = "FileRead-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 74;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileClose-Request";
	group.des = "FileClose-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 75;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileRename-Request";
	group.des = "FileRename-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 76;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileDelete-Request";
	group.des = "FileDelete-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 77;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileDirectory-Request";
	group.des = "FileDirectory-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 78;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "IMPLICIT AdditionalService-Request";
	group.des = "AdditionalService-Request";
	myTagNoMap.insert(tagNo, group);

//	tagNo = 79;
//	group.type = ASN1BER::Sequence;
//	group.typeDes = "IMPLICIT reserved";
//	group.des = "reserved";
//	myTagNoMap.insert(tagNo, group);

	tagNo = 80;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetDataExchangeAttributes-Request";
	group.des = "GetDataExchangeAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 81;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ExchangeData-Request";
	group.des = "ExchangeData-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 82;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineAccessControlList-Request";
	group.des = "DefineAccessControlList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 83;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetAccessControlListAttributes-Request";
	group.des = "GetAccessControlListAttributes-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 84;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportAccessControlledObjects-Request";
	group.des = "ReportAccessControlledObjects-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 85;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteAccessControlList-Request";
	group.des = "DeleteAccessControlList-Request";
	myTagNoMap.insert(tagNo, group);

	tagNo = 86;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ChangeAccessControl-Request";
	group.des = "ChangeAccessControl-Request";
	myTagNoMap.insert(tagNo, group);

}

ASN1BER *IEC61850_ConfirmedService_Request::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_GetNameList_Request(mConfig);
			break;
		case 4:
			ber = new IEC61850_Read_Request(mConfig);
			break;
		case 5:
			ber = new IEC61850_Write_Request(mConfig);
			break;
		case 6:
			ber = new IEC61850_GetVariableAccessAttributes_Request(mConfig);
			break;
		case 12:
			ber = new IEC61850_ObjectName(mConfig);
			break;
		case 78:
			ber = new IEC61850_AdditionalService_Request(mConfig);
			break;
		default:
			ber = CreateBERByType(myTagNoMap[tagNo].type);
			break;
		}
		setBERGroup(ber, myTagNoMap[tagNo]);
	}
	if(!ber)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
				 .arg(QString("出错！%1 创建ContextBER失败:tagNo=%2 index=%3").arg(myGroup.des).arg(tagNo).arg(index));
	}
	return ber;
}
