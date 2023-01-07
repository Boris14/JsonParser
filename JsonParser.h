#pragma once
#include "JsonDataStructs.h"

using namespace std;

class JsonParser
{
public:
	/*Constructor from a given Json file name*/
	JsonParser(string fileName);

	/*Writes the Json on a file with the given name*/
	void write(string fileName);

private:
	JsonObject object;
};