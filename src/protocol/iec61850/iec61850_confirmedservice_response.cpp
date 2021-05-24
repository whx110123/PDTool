#include "iec61850_additionalservice_response.h"
#include "iec61850_confirmedservice_response.h"
#include "iec61850_getnamedvariablelistattributes_response.h"
#include "iec61850_getnamelist_response.h"
#include "iec61850_getvariableaccessattributes_response.h"
#include "iec61850_read_response.h"
#include "iec61850_write_response.h"

IEC61850_ConfirmedService_Response::IEC61850_ConfirmedService_Response(const MyConfig& Config): ASN1BER(Config)
{
	myGroup.type = ASN1BER::Choice;
}

IEC61850_ConfirmedService_Response::~IEC61850_ConfirmedService_Response()
{

}

void IEC61850_ConfirmedService_Response::initMap()
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
	group.typeDes = "IMPLICIT Status-Response";
	group.des = "Status-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 1;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetNameList-Response";
	group.des = "GetNameList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 2;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Identify-Response";
	group.des = "Identify-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 3;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Rename-Response";
	group.des = "Rename-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 4;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Read-Response";
	group.des = "Read-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 5;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Write-Response";
	group.des = "Write-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 6;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetVariableAccessAttributes-Response";
	group.des = "GetVariableAccessAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 7;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineNamedVariable-Response";
	group.des = "DefineNamedVariable-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 8;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineScatteredAccess-Response";
	group.des = "DefineScatteredAccess-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 9;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetScatteredAccessAttributes-Response";
	group.des = "GetScatteredAccessAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 10;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteVariableAccess-Response";
	group.des = "DeleteVariableAccess-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 11;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineNamedVariableList-Response";
	group.des = "DefineNamedVariableList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 12;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetNamedVariableListAttributes-Response";
	group.des = "GetNamedVariableListAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 13;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteNamedVariableList-Response";
	group.des = "DeleteNamedVariableList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 14;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineNamedType-Response";
	group.des = "DefineNamedType-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 15;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetNamedTypeAttributes-Response";
	group.des = "GetNamedTypeAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 16;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteNamedType-Response";
	group.des = "DeleteNamedType-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 17;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Input-Response";
	group.des = "Input-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 18;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Output-Response";
	group.des = "Output-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 19;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TakeControl-Response";
	group.des = "TakeControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 20;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RelinquishControl-Response";
	group.des = "RelinquishControl-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 21;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineSemaphore-Response";
	group.des = "DefineSemaphore-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 22;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteSemaphore-Response";
	group.des = "DeleteSemaphore-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 23;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportSemaphoreStatus-Response";
	group.des = "ReportSemaphoreStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 24;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportPoolSemaphoreStatus-Response";
	group.des = "ReportPoolSemaphoreStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 25;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportSemaphoreEntryStatus-Response";
	group.des = "ReportSemaphoreEntryStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 26;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitiateDownloadSequence-Response";
	group.des = "InitiateDownloadSequence-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 27;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DownloadSegment-Response";
	group.des = "DownloadSegment-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 28;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TerminateDownloadSequence-Response";
	group.des = "TerminateDownloadSequence-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 29;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitiateUploadSequence-Response";
	group.des = "InitiateUploadSequence-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 30;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT UploadSegment-Response";
	group.des = "UploadSegment-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 31;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TerminateUploadSequence-Response";
	group.des = "TerminateUploadSequence-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 32;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RequestDomainDownload-Response";
	group.des = "RequestDomainDownload-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 33;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT RequestDomainUpload-Response";
	group.des = "RequestDomainUpload-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 34;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT LoadDomainContent-Response";
	group.des = "LoadDomainContent-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 35;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT StoreDomainContent-Response";
	group.des = "StoreDomainContent-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 36;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteDomain-Response";
	group.des = "DeleteDomain-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 37;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetDomainAttributes-Response";
	group.des = "GetDomainAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 38;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CreateProgramInvocation-Response";
	group.des = "CreateProgramInvocation-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 39;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteProgramInvocation-Response";
	group.des = "DeleteProgramInvocation-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 40;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Start-Response";
	group.des = "Start-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 41;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Stop-Response";
	group.des = "Stop-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 42;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Resume-Response";
	group.des = "Resume-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 43;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Reset-Response";
	group.des = "Reset-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 44;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT Kill-Response";
	group.des = "Kill-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 45;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetProgramInvocationAttributes-Response";
	group.des = "GetProgramInvocationAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 46;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ObtainFile-Response";
	group.des = "ObtainFile-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 47;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventCondition-Response";
	group.des = "DefineEventCondition-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 48;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventCondition-Response";
	group.des = "DeleteEventCondition-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 49;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventConditionAttributes-Response";
	group.des = "GetEventConditionAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 50;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventConditionStatus-Response";
	group.des = "ReportEventConditionStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 51;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterEventConditionMonitoring-Response";
	group.des = "AlterEventConditionMonitoring-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 52;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT TriggerEvent-Response";
	group.des = "TriggerEvent-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 53;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventAction-Response";
	group.des = "DefineEventAction-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 54;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventAction-Response";
	group.des = "DeleteEventAction-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 55;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventActionAttributes-Response";
	group.des = "GetEventActionAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 56;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventActionStatus-Response";
	group.des = "ReportEventActionStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 57;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineEventEnrollment-Response";
	group.des = "DefineEventEnrollment-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 58;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteEventEnrollment-Response";
	group.des = "DeleteEventEnrollment-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 59;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AlterEventEnrollment-Response";
	group.des = "AlterEventEnrollment-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 60;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportEventEnrollmentStatus-Response";
	group.des = "ReportEventEnrollmentStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 61;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetEventEnrollmentAttributes-Response";
	group.des = "GetEventEnrollmentAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 62;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT AcknowledgeEventNotification-Response";
	group.des = "AcknowledgeEventNotification-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 63;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetAlarmSummary-Response";
	group.des = "GetAlarmSummary-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 64;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetAlarmEnrollmentSummary-Response";
	group.des = "GetAlarmEnrollmentSummary-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 65;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReadJournal-Response";
	group.des = "ReadJournal-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 66;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT WriteJournal-Response";
	group.des = "WriteJournal-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 67;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT InitializeJournal-Response";
	group.des = "InitializeJournal-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 68;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportJournalStatus-Response";
	group.des = "ReportJournalStatus-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 69;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT CreateJournal-Response";
	group.des = "CreateJournal-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 70;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteJournal-Response";
	group.des = "DeleteJournal-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 71;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetCapabilityList-Response";
	group.des = "GetCapabilityList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 72;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileOpen-Response";
	group.des = "FileOpen-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 73;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileRead-Response";
	group.des = "FileRead-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 74;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileClose-Response";
	group.des = "FileClose-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 75;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileRename-Response";
	group.des = "FileRename-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 76;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileDelete-Response";
	group.des = "FileDelete-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 77;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT FileDirectory-Response";
	group.des = "FileDirectory-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 78;
	group.type = ASN1BER::ChoiceWithTag;
	group.typeDes = "IMPLICIT AdditionalService-Response";
	group.des = "AdditionalService-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 79;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT reserved";
	group.des = "reserved";
	myTagNoMap.insert(tagNo, group);

	tagNo = 80;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetDataExchangeAttributes-Response";
	group.des = "GetDataExchangeAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 81;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ExchangeData-Response";
	group.des = "ExchangeData-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 82;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DefineAccessControlList-Response";
	group.des = "DefineAccessControlList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 83;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT GetAccessControlListAttributes-Response";
	group.des = "GetAccessControlListAttributes-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 84;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ReportAccessControlledObjects-Response";
	group.des = "ReportAccessControlledObjects-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 85;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT DeleteAccessControlList-Response";
	group.des = "DeleteAccessControlList-Response";
	myTagNoMap.insert(tagNo, group);

	tagNo = 86;
	group.type = ASN1BER::Sequence;
	group.typeDes = "IMPLICIT ChangeAccessControl-Response";
	group.des = "ChangeAccessControl-Response";
	myTagNoMap.insert(tagNo, group);
}

ASN1BER *IEC61850_ConfirmedService_Response::CreateContextBER(uint tagNo, uint index)
{
	ASN1BER *ber = NULL;
	if(myTagNoMap.contains(tagNo))
	{
		switch(tagNo)
		{
		case 1:
			ber = new IEC61850_GetNameList_Response(mConfig);
			break;
		case 4:
			ber = new IEC61850_Read_Response(mConfig);
			break;
		case 5:
			ber = new IEC61850_Write_Response(mConfig);
			break;
		case 6:
			ber = new IEC61850_GetVariableAccessAttributes_Response(mConfig);
			break;
		case 12:
			ber = new IEC61850_GetNamedVariableListAttributes_Response(mConfig);
			break;
		case 78:
			ber = new IEC61850_AdditionalService_Response(mConfig);
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

