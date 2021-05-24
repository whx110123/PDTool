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
