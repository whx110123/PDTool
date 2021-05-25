#ifndef IEC61850DEFINE_H
#define IEC61850DEFINE_H

class TypeInteger
{
public:
	enum
	{
		NoDefine,
		basicObjectClass,
		csObjectClass,
		DataAccessError,
		vmd_state,
		application_reference,
		definition,
		resource,
		service,
		service_preempt,
		time_resolution,
		access,
		initiate,
		conclude,
		cancel,
		file,
		rejectReason_confirmed_requestPDU,
		rejectReason_confirmed_responsePDU,
		rejectReason_confirmed_errorPDU,
		rejectReason_unconfirmedPDU,
		rejectReason_pdu_error,
		rejectReason_cancel_requestPDU,
		rejectReason_cancel_responsePDU,
		rejectReason_cancel_errorPDU,
		rejectReason_conclude_requestPDU,
		rejectReason_conclude_responsePDU,
		rejectReason_conclude_errorPDU,
	};
};


class TypeBitString
{
public:
	enum
	{
		NoDefine,
		ParameterSupportOptions,
		ServiceSupportOptions,
		AdditionalSupportOptions,
		AdditionalCBBOptions,
	};
};

#endif // IEC61850DEFINE_H
