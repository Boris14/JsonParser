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

	/*Returns all values associated with the given key*/
	vector<Value> find(string key);

	/*Change a key's value from a given full path to it*/
	void change(string path, string value);

private:
	JsonObject object;
};