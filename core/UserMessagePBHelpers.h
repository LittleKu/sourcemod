/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod
 * Copyright (C) 2013 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#ifndef _INCLUDE_SOURCEMOD_SMPBMESSAGE_H_
#define _INCLUDE_SOURCEMOD_SMPBMESSAGE_H_

#include <sh_list.h>
#include <google/protobuf/descriptor.h>

#define GETCHECK_FIELD() \
	const protobuf::FieldDescriptor *field = msg->GetDescriptor()->FindFieldByName(pszFieldName); \
	if (!field)       \
	{                 \
		return false; \
	}

#define CHECK_FIELD_TYPE(type) \
	if (field->cpp_type() != protobuf::FieldDescriptor::CPPTYPE_##type) \
	{                 \
		return false; \
	}

#define CHECK_FIELD_TYPE2(type1, type2) \
	protobuf::FieldDescriptor::CppType fieldType = field->cpp_type(); \
	if (fieldType != protobuf::FieldDescriptor::CPPTYPE_##type1       \
		&& fieldType != protobuf::FieldDescriptor::CPPTYPE_##type2) \
	{                 \
		return false; \
	}

#define CHECK_FIELD_REPEATED() \
	if (field->label() != protobuf::FieldDescriptor::LABEL_REPEATED) \
	{                 \
		return false; \
	}

#define CHECK_FIELD_NOT_REPEATED() \
	if (field->label() == protobuf::FieldDescriptor::LABEL_REPEATED) \
	{                 \
		return false; \
	}

#define CHECK_REPEATED_ELEMENT(idx) \
	int elemCount = msg->GetReflection()->FieldSize(*msg, field); \
	if (elemCount == 0 || idx >= elemCount || idx <= 0)       \
	{                                                         \
		return false;                                         \
	}

typedef List<Handle_t> PBHandleList;

class SMProtobufMessage
{
public:
	SMProtobufMessage( protobuf::Message *message )
	{
		msg = message;
	}

	~SMProtobufMessage()
	{
		PBHandleList::iterator iter = childHandles.begin();
		while (iter != childHandles.end())
		{
			Handle_t &hndl = (*iter);
			HandleSecurity sec;
			sec.pIdentity = g_pCoreIdent;
			g_HandleSys.FreeHandle(hndl, &sec);
			iter = childHandles.erase(iter);
		}
	}

	inline void AddChildHandle(Handle_t hndl)
	{
		childHandles.push_back(hndl);
	}

	inline protobuf::Message *GetProtobufMessage()
	{
		return msg;
	}

	inline bool GetInt32(const char *pszFieldName, int32 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT32);
		CHECK_FIELD_NOT_REPEATED();

		*out = msg->GetReflection()->GetInt32(*msg, field);
		return true;	
	}

	inline bool SetInt32(const char *pszFieldName, int32 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT32);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetInt32(msg, field, value);
		return true;
	}

	inline bool GetRepeatedInt32(const char *pszFieldName, int index, int32 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT32);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		*out = msg->GetReflection()->GetRepeatedInt32(*msg, field, index);
		return true;
	}

	inline bool AddInt32(const char *pszFieldName, int32 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT32);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddInt32(msg, field, value);
		return true;
	}

	inline bool GetInt64(const char *pszFieldName, int64 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT64);
		CHECK_FIELD_NOT_REPEATED();

		*out = msg->GetReflection()->GetInt64(*msg, field);
		return true;	
	}

	inline bool SetInt64(const char *pszFieldName, int64 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT64);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetInt64(msg, field, value);
		return true;
	}

	inline bool GetRepeatedInt64(const char *pszFieldName, int index, int64 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT64);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		*out = msg->GetReflection()->GetRepeatedInt64(*msg, field, index);
		return true;
	}

	inline bool AddInt64(const char *pszFieldName, int64 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(INT64);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddInt64(msg, field, value);
		return true;
	}

	inline bool GetUInt32(const char *pszFieldName, uint32 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT32);
		CHECK_FIELD_NOT_REPEATED();

		*out = msg->GetReflection()->GetUInt32(*msg, field);
		return true;	
	}

	inline bool SetUInt32(const char *pszFieldName, uint32 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT32);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetUInt32(msg, field, value);
		return true;
	}

	inline bool GetRepeatedUInt32(const char *pszFieldName, int index, uint32 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT32);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		*out = msg->GetReflection()->GetRepeatedUInt32(*msg, field, index);
		return true;
	}

	inline bool AddUInt32(const char *pszFieldName, uint32 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT32);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddUInt32(msg, field, value);
		return true;
	}

	inline bool GetUInt64(const char *pszFieldName, uint64 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT64);
		CHECK_FIELD_NOT_REPEATED();

		*out = msg->GetReflection()->GetUInt64(*msg, field);
		return true;	
	}

	inline bool SetUInt64(const char *pszFieldName, uint64 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT64);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetUInt64(msg, field, value);
		return true;
	}

	inline bool GetRepeatedUInt64(const char *pszFieldName, int index, uint64 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT64);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		*out = msg->GetReflection()->GetRepeatedUInt64(*msg, field, index);
		return true;
	}

	inline bool AddUInt64(const char *pszFieldName, uint64 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(UINT64);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddUInt32(msg, field, value);
		return true;
	}

	inline bool GetInt32OrUnsigned(const char *pszFieldName, int32 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(INT32, UINT32);
		CHECK_FIELD_NOT_REPEATED();

		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_UINT32)
			*out = (int32)msg->GetReflection()->GetUInt32(*msg, field);
		else
			*out = msg->GetReflection()->GetInt32(*msg, field);

		return true;	
	}

	inline bool SetInt32OrUnsigned(const char *pszFieldName, int32 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(INT32, UINT32);
		CHECK_FIELD_NOT_REPEATED();

		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_UINT32)
			msg->GetReflection()->SetUInt32(msg, field, (uint32)value);
		else
			msg->GetReflection()->SetInt32(msg, field, value);

		return true;
	}

	inline bool GetRepeatedInt32OrUnsigned(const char *pszFieldName, int index, int32 *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(INT32, UINT32);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_UINT32)
			*out = (int32)msg->GetReflection()->GetRepeatedUInt32(*msg, field, index);
		else
			*out = msg->GetReflection()->GetRepeatedInt32(*msg, field, index);

		return true;
	}

	inline bool AddInt32OrUnsigned(const char *pszFieldName, int32 value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(INT32, UINT32);
		CHECK_FIELD_REPEATED();

		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_UINT32)
			msg->GetReflection()->AddUInt32(msg, field, (uint32)value);
		else
			msg->GetReflection()->AddInt32(msg, field, value);

		return true;
	}

	inline bool GetBool(const char *pszFieldName, bool *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(BOOL);
		CHECK_FIELD_NOT_REPEATED();

		*out = msg->GetReflection()->GetBool(*msg, field);
		return true;	
	}

	inline bool SetBool(const char *pszFieldName, bool value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(BOOL);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetBool(msg, field, value);
		return true;
	}

	inline bool GetRepeatedBool(const char *pszFieldName, int index, bool *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(BOOL);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		*out = msg->GetReflection()->GetRepeatedBool(*msg, field, index);
		return true;
	}

	inline bool AddBool(const char *pszFieldName, bool value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(BOOL);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddBool(msg, field, value);
		return true;
	}

	inline bool GetFloat(const char *pszFieldName, float *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(FLOAT);
		CHECK_FIELD_NOT_REPEATED();

		*out = msg->GetReflection()->GetFloat(*msg, field);
		return true;	
	}

	inline bool SetFloat(const char *pszFieldName, float value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(FLOAT);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetFloat(msg, field, value);
		return true;
	}

	inline bool GetRepeatedFloat(const char *pszFieldName, int index, float *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(FLOAT);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		*out = msg->GetReflection()->GetRepeatedFloat(*msg, field, index);
		return true;
	}

	inline bool AddFloat(const char *pszFieldName, float value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(FLOAT);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddFloat(msg, field, value);
		return true;
	}

	inline bool GetDouble(const char *pszFieldName, double *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(DOUBLE);
		CHECK_FIELD_NOT_REPEATED();

		*out = msg->GetReflection()->GetDouble(*msg, field);
		return true;	
	}

	inline bool SetDouble(const char *pszFieldName, double value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(DOUBLE);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetDouble(msg, field, value);
		return true;
	}

	inline bool GetRepeatedDouble(const char *pszFieldName, int index, double *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(DOUBLE);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		*out = msg->GetReflection()->GetRepeatedDouble(*msg, field, index);
		return true;
	}

	inline bool AddDouble(const char *pszFieldName, double value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(DOUBLE);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddDouble(msg, field, value);
		return true;
	}

	inline bool GetFloatOrDouble(const char *pszFieldName, float *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(FLOAT, DOUBLE);
		CHECK_FIELD_NOT_REPEATED();

		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_DOUBLE)
			*out = (float)msg->GetReflection()->GetDouble(*msg, field);
		else
			*out = msg->GetReflection()->GetFloat(*msg, field);

		return true;	
	}

	inline bool SetFloatOrDouble(const char *pszFieldName, float value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(FLOAT, DOUBLE);
		CHECK_FIELD_NOT_REPEATED();

		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_DOUBLE)
			msg->GetReflection()->SetDouble(msg, field, (double)value);
		else
			msg->GetReflection()->SetFloat(msg, field, value);

		return true;
	}

	inline bool GetRepeatedFloatOrDouble(const char *pszFieldName, int index, float *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(FLOAT, DOUBLE);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_DOUBLE)
			*out = (float)msg->GetReflection()->GetRepeatedDouble(*msg, field, index);
		else
			*out = msg->GetReflection()->GetRepeatedFloat(*msg, field, index);

		return true;
	}

	inline bool AddFloatOrDouble(const char *pszFieldName, float value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE2(FLOAT, DOUBLE);
		CHECK_FIELD_REPEATED();

		if (fieldType == protobuf::FieldDescriptor::CPPTYPE_DOUBLE)
			msg->GetReflection()->AddDouble(msg, field, (double)value);
		else
			msg->GetReflection()->AddFloat(msg, field, value);

		return true;
	}

	inline bool GetString(const char *pszFieldName, char *out, int size)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(STRING);
		CHECK_FIELD_NOT_REPEATED();

		std::string scratch;
		strncopy(out, msg->GetReflection()->GetStringReference(*msg, field, &buffer).c_str(), size);

		return true;	
	}

	inline bool SetString(const char *pszFieldName, const char *value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(STRING);
		CHECK_FIELD_NOT_REPEATED();

		msg->GetReflection()->SetString(msg, field, value);
		return true;
	}

	inline bool GetRepeatedString(const char *pszFieldName, int index, char *out, int size)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(STRING);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);
		
		std::string scratch;
		strncopy(out, msg->GetReflection()->GetRepeatedStringReference(*msg, field, index, &scratch).c_str(), size);

		return true;
	}

	inline bool AddString(const char *pszFieldName, const char *value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(STRING);
		CHECK_FIELD_REPEATED();

		msg->GetReflection()->AddString(msg, field, value);
		return true;
	}

	inline bool GetColor(const char *pszFieldName, Color *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		const CMsgRGBA &msgRGBA = (const CMsgRGBA &)msg->GetReflection()->GetMessage(*msg, field);
		out->SetColor(
			msgRGBA.r(),
			msgRGBA.g(),
			msgRGBA.b(),
			msgRGBA.a()
			);

		return true;
	}

	inline bool SetColor(const char *pszFieldName, const Color &value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		CMsgRGBA *msgRGBA = (CMsgRGBA *)msg->GetReflection()->MutableMessage(msg, field);
		msgRGBA->set_r(value.r());
		msgRGBA->set_g(value.g());
		msgRGBA->set_b(value.b());
		msgRGBA->set_a(value.a());

		return true;
	}

	inline bool GetRepeatedColor(const char *pszFieldName, int index, Color *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);

		const CMsgRGBA &msgRGBA = (const CMsgRGBA &)msg->GetReflection()->GetRepeatedMessage(*msg, field, index);
		out->SetColor(
			msgRGBA.r(),
			msgRGBA.g(),
			msgRGBA.b(),
			msgRGBA.a()
			);

		return true;
	}

	inline bool AddColor(const char *pszFieldName, const Color &value)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();

		CMsgRGBA *msgRGBA = (CMsgRGBA *)msg->GetReflection()->AddMessage(msg, field);
		msgRGBA->set_r(value.r());
		msgRGBA->set_g(value.g());
		msgRGBA->set_b(value.b());
		msgRGBA->set_a(value.a());

		return true;
	}

	inline bool GetVector2D(const char *pszFieldName, Vector2D *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		const CMsgVector2D &msgVec2d = (const CMsgVector2D &)msg->GetReflection()->GetMessage(*msg, field);
		out->Init(
			msgVec2d.x(),
			msgVec2d.y()
			);

		return true;
	}

	inline bool SetVector2D(const char *pszFieldName, Vector2D &vec)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		CMsgVector2D *msgVec2d = (CMsgVector2D *)msg->GetReflection()->MutableMessage(msg, field);
		msgVec2d->set_x(vec.x);
		msgVec2d->set_y(vec.y);

		return true;
	}

	inline bool GetRepeatedVector2D(const char *pszFieldName, int index, Vector2D *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);

		const CMsgVector2D &msgVec2d = (const CMsgVector2D &)msg->GetReflection()->GetRepeatedMessage(*msg, field, index);
		out->Init(
			msgVec2d.x(),
			msgVec2d.y()
			);

		return true;
	}

	inline bool AddVector2D(const char *pszFieldName, Vector2D &vec)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();

		CMsgVector2D *msgVec2d = (CMsgVector2D *)msg->GetReflection()->AddMessage(msg, field);
		msgVec2d->set_x(vec.x);
		msgVec2d->set_y(vec.y);

		return true;
	}

	inline bool GetVector(const char *pszFieldName, Vector *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		const CMsgVector &msgVec = (const CMsgVector &)msg->GetReflection()->GetMessage(*msg, field);
		out->Init(
			msgVec.x(),
			msgVec.y(),
			msgVec.z()
			);

		return true;
	}

	inline bool SetVector(const char *pszFieldName, Vector &vec)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		CMsgVector *msgVec = (CMsgVector *)msg->GetReflection()->MutableMessage(msg, field);
		msgVec->set_x(vec.x);
		msgVec->set_y(vec.y);
		msgVec->set_z(vec.z);

		return true;
	}

	inline bool GetRepeatedVector(const char *pszFieldName, int index, Vector *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);

		const CMsgVector &msgVec = (const CMsgVector &)msg->GetReflection()->GetRepeatedMessage(*msg, field, index);
		out->Init(
			msgVec.x(),
			msgVec.y(),
			msgVec.z()
			);

		return true;
	}

	inline bool AddVector(const char *pszFieldName, Vector &vec)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();

		CMsgVector *msgVec = (CMsgVector *)msg->GetReflection()->AddMessage(msg, field);
		msgVec->set_x(vec.x);
		msgVec->set_y(vec.y);
		msgVec->set_z(vec.z);

		return true;
	}

	inline bool GetQAngle(const char *pszFieldName, QAngle *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		const CMsgQAngle &msgAng = (const CMsgQAngle &)msg->GetReflection()->GetMessage(*msg, field);
		out->Init(
			msgAng.x(),
			msgAng.y(),
			msgAng.z()
			);

		return true;
	}

	inline bool SetQAngle(const char *pszFieldName, QAngle &vec)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		CMsgQAngle *msgAng = (CMsgQAngle *)msg->GetReflection()->MutableMessage(msg, field);
		msgAng->set_x(vec.x);
		msgAng->set_y(vec.y);
		msgAng->set_z(vec.z);

		return true;
	}

	inline bool GetRepeatedQAngle(const char *pszFieldName, int index, QAngle *out)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);

		const CMsgQAngle &msgAng = (const CMsgQAngle &)msg->GetReflection()->GetRepeatedMessage(*msg, field, index);
		out->Init(
			msgAng.x(),
			msgAng.y(),
			msgAng.z()
			);

		return true;
	}

	inline bool AddQAngle(const char *pszFieldName, QAngle &vec)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();

		CMsgQAngle *msgAng = (CMsgQAngle *)msg->GetReflection()->AddMessage(msg, field);
		msgAng->set_x(vec.x);
		msgAng->set_y(vec.y);
		msgAng->set_z(vec.z);

		return true;
	}

	inline bool GetMessage(const char *pszFieldName, protobuf::Message **message)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_NOT_REPEATED();

		*message = msg->GetReflection()->MutableMessage(msg, field);

		return true;
	}

	inline bool GetRepeatedMessage(const char *pszFieldName, int index, const protobuf::Message **message)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();
		CHECK_REPEATED_ELEMENT(index);

		const protobuf::Message *m = &msg->GetReflection()->GetRepeatedMessage(*msg, field, index);
		*message = m;

		return true;
	}

	inline bool AddMessage(const char *pszFieldName, protobuf::Message **message)
	{
		GETCHECK_FIELD();
		CHECK_FIELD_TYPE(MESSAGE);
		CHECK_FIELD_REPEATED();

		*message = msg->GetReflection()->AddMessage(msg, field);

		return true;
	}

	inline int GetRepeatedFieldCount(const char *pszFieldName)
	{
		const protobuf::FieldDescriptor *field = msg->GetDescriptor()->FindFieldByName(pszFieldName); \
		if (!field)
			return -1;

		if (field->label() != protobuf::FieldDescriptor::LABEL_REPEATED)
			return -1;

		return msg->GetReflection()->FieldSize(*msg, field);
	}

private:
	protobuf::Message *msg;
	PBHandleList childHandles;
};

#endif // _INCLUDE_SOURCEMOD_SMPBMESSAGE_H_