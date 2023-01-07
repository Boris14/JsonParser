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

vector<Value> JsonParser::find(string key)
{
	return object.find(key);
}

void JsonParser::change(string path, string value)
{
	string wrongPathErrorString = "Wrong path given when trying to change a value";
	vector<string> keys;
	while (path.find('/') != string::npos)
	{
		keys.insert(keys.begin(), path.substr(0, path.find('/')));
		path.erase(0, path.find('/') + 1);
	}
	keys.insert(keys.begin(), path);

	map<string, Value*>::iterator foundPair = object.keyValueMap.find(keys.back());
	if (foundPair == object.keyValueMap.end())
	{
		throw wrongPathErrorString;
	}
	Value* foundValue = foundPair->second;
	keys.pop_back();
	while (!keys.empty())
	{
		if (foundValue->type != Value::ValueType::OBJECT)
		{
			throw wrongPathErrorString;
		}
		foundPair = foundValue->obj->keyValueMap.find(keys.back());
		if (foundPair == foundValue->obj->keyValueMap.end())
		{
			throw wrongPathErrorString;
		}
		foundValue = foundPair->second;
		keys.pop_back();
	}

	foundValue->changeValue(value);
}