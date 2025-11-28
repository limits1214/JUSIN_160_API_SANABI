#pragma once

#include "pch.h"
#include "Define.h"

class CObjDbgText
{
public:
	CObjDbgText() = default;
	virtual ~CObjDbgText() = default;

public:
	virtual TCHAR* Dbg_Text() PURE;
};