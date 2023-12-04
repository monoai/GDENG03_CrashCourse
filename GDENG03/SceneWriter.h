#pragma once
#include <string>

class SceneWriter
{
public:
	SceneWriter(std::string directory);
	~SceneWriter();

	void writeToFile();

private:
	std::string directory;
};