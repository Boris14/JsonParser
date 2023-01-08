#pragma once
#include "JsonDataStructs.h"

using namespace std;

class JsonParser
{
public:
	/*Opens a Json file to the object*/
	void open(string inFileName);

	/*Writes the Json on a file with the given name*/
	void write(string inFileName);

	/*Returns all values associated with the given key*/
	vector<Value*> find(string key);

	/*Change a key's value from a given full path to it*/
	void change(string path, string value);

	/*Handle a line of user input*/
	void handleInput();

	bool getIsActive() { return isActive; }

private:
	string fileName;
	JsonObject object;
	bool isActive = true;
};