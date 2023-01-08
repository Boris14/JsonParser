#include "JsonParser.h"
#include <fstream>

void JsonParser::open(string inFileName)
{
	inFileName.append(".json");
	ifstream in(inFileName);
	if (in.is_open() == false)
	{
		throw "Invalid Json File.";
	}
	in >> object;
	in.close();

	fileName = inFileName;
}

void JsonParser::write(string inFileName)
{
	inFileName.append(".json");
	ofstream out(inFileName);
	if (out.is_open() == false)
	{
		throw "Unknown while trying to write to file";
	}
	out << object;
	out.close();
}

vector<Value*> JsonParser::find(string key)
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

string getNextWord(string &line)
{
	string result;
	size_t i = 0;
	for (char letter : line)
	{
		if (iswspace(letter) && !result.empty())
		{
			break;
		}
		else if(!iswspace(letter))
		{
			result.push_back(letter);
		}
		++i;
	}
	line.erase(0, i);
	return result;
}

void JsonParser::handleInput()
{
	string line;
	if (!fileName.empty())
	{
		cout << fileName << ' ';
	}
	cout << "> ";
	getline(cin, line);

	string word = getNextWord(line);
	if (word.compare("open") == 0)
	{
		word = getNextWord(line);
		if (word.empty())
		{
			throw "File Name not given";
		}
		open(word);
	}
	else if (word.compare("find") == 0)
	{
		word = getNextWord(line);
		if (word.empty())
		{
			throw "Key not given.";
		}
		vector<Value*> foundValues = find(word);
		for (Value* val : foundValues)
		{
			cout << *val << endl;
		}
		if (foundValues.empty())
		{
			throw "No key matches the given one.";
		}
	}
	else if (word.compare("change") == 0)
	{
		word = getNextWord(line);
		while (iswspace(line[0]))
		{
			line.erase(0, 1);
		}
		change(word, line);
	}
	else if (word.compare("add") == 0)
	{
		cout << "Command not implemented yet :c" << endl << endl;
	}
	else if (word.compare("info") == 0)
	{
		cout << endl << "commands:\n"
			"\topen\t*file name without .json extension* - opens a Json file from the directory of the solution\n"
			"\tfind\t*key* - finds all the values associated with the given key\n"
			"\tchange\t*path to key*\t*value* - changes the value associated with the exact path to the key\n"
			"\tadd\t*path to key*\t*value* - creates a new key-value pair with the given path for the key\n"
			"\twrite\t*file name* - writes the modified Json to a file \n"
			"\texit - quits the program" << endl << endl;
	}
	else if (word.compare("write") == 0)
	{
		if (fileName.empty())
		{
			throw "There is not an open Json file.";
		}
		word = getNextWord(line);
		if (word.empty())
		{
			throw "File Name not given";
		}
		write(word);
	}
	else if (word.compare("exit") == 0)
	{
		isActive = false;
	}
	else if (!word.empty())
	{
		throw "Invalid command";
	}
}