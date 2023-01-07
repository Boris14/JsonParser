#include "JsonParser.h"
#include <fstream>

JsonParser::JsonParser(string fileName)
{
	fileName.append(".json");
	ifstream in(fileName);
	if (in.is_open() == false)
	{
		throw "Invalid Json File. Try not adding the extension in the name (.json).";
	}
	in >> object;
	in.close();
}

void JsonParser::write(string fileName)
{
	fileName.append(".json");
	ofstream out(fileName);
	if (out.is_open() == false)
	{
		throw "Error while trying to write on file";
	}
	out << object;
	out.close();
}