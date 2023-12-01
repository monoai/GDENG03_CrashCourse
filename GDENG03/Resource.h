#pragma once
#include <string>

class AResource
{
public:
	AResource(const wchar_t* fullPath);
	virtual ~AResource();
protected:
	std::wstring fullPath;
};