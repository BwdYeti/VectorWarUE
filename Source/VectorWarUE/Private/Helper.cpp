// Copyright 2020 BwdYeti.


#include "Helper.h"
#include <intrin.h>
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformProperties.h"

FString UHelper::IntToHex(int32 Value)
{
	int32 Bytes = Value;
	// xxx: not actually sure if I should check this...
	//if (FGenericPlatformProperties::IsLittleEndian())
	{
		Bytes = _byteswap_ulong(Value);
	}
	return BytesToHex((uint8*)&Bytes, sizeof(int32));
}

FString UHelper::LongToHex(int64 Value)
{
	int64 Bytes = Value;
	// xxx: not actually sure if I should check this...
	//if (FGenericPlatformProperties::IsLittleEndian())
	{
		Bytes = _byteswap_uint64(Value);
	}
	return BytesToHex((uint8*)&Bytes, sizeof(int64));
}

