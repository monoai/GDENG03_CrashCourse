#pragma once
#include <string>
#include <vector>

class SceneReader
{
public:
	SceneReader(std::string directory);
	~SceneReader();

	std::vector<std::string> split(const std::string& s, char delim);
	void readFromFile();
	void u2lparser(std::string fileDir);
	

private:
	std::string directory;
};