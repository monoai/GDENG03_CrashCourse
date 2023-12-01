#include "TextureManager.h"
#include "Texture.h"
#include <filesystem>

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::initialize()
{
	sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
	delete sharedInstance;
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

// Temporarily this is modified to use relative path despite being made for absolute
// I assume actually using an absolutepath would give weird paths
// so make a new function instead
Texture* TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	std::wstring fullPath = std::filesystem::absolute(filePath);

	if (this->resourceMap[fullPath] == NULL) {
		std::cout << " null .." << std::endl;
		std::wcout << "Path given is: " << fullPath << std::endl;
		// converting back to fullPath
		const wchar_t* wcs = fullPath.c_str();
		this->resourceMap[fullPath] = this->convertToResource(wcs);
	}

	return (Texture*)this->resourceMap[fullPath];
}

TextureManager::TextureManager() :AResourceManager()
{

}

TextureManager::~TextureManager()
{
	if (this->resourceMap.size() != 0) {
		this->resourceMap.clear();
	}
}

Resource* TextureManager::convertToResource(const wchar_t* filePath)
{
	Texture* tex = NULL;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...)
	{

	}

	return (Resource*)tex;
}