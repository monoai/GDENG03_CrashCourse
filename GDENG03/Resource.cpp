#include "Resource.h"
#include <iostream>
#include <filesystem>

AResource::AResource(const wchar_t* fullPath)
{
	std::wstring finalPath = std::filesystem::absolute(fullPath);
	this->fullPath = finalPath;
	//std::wcout << this->fullPath << std::endl;
	//std::wcout << finalPath << std::endl;
}

AResource::~AResource()
{
}