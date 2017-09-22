#include <iostream>
#include <fstream>
#include <string>

#include "InputFile.h"

bool InputFile::Read(std::string filename)
{
	_contents = "";
	bool x;

	std::ifstream readFile;
	readFile.open(filename);
	
	if (readFile.fail())
	{
		x = false;
		std::cerr << "Error al abrir archivo" << std::endl;
	}
	else
	{
		while (readFile.good())
		{
			_contents += readFile.get();
		}
		x = true;
	}

	readFile.close();

	return x;
}

std::string InputFile::GetContents()
{
	return _contents;
}
