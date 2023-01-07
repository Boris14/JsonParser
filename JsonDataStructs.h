#pragma once

#include <map>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Value
{
	enum class ValueType
	{
		STRING,
		NUMBER,
		OBJECT,
		ARRAY,
		BOOL,
		EMPTY
	};
	
	float number = 0;
	string name;
	bool flag = false;
	struct JsonObject *obj = nullptr;
	struct JsonArray *arr = nullptr;
	ValueType type = ValueType::EMPTY;

	~Value()
	{
		if (obj != nullptr)
		{
			delete obj;
		}
		if (arr != nullptr)
		{
			delete arr;
		}
		type = ValueType::EMPTY;
	}
};

struct JsonObject
{
	map<string, Value*> keyValueMap;

	~JsonObject()
	{
		for (pair<string, Value*> keyValuePair : keyValueMap)
		{
			if (keyValuePair.second != nullptr)
			{
				delete keyValuePair.second;
			}
		}
	}
};

struct JsonArray
{
	vector<Value*> values;

	~JsonArray()
	{
		for (Value* value : values)
		{
			if (value != nullptr)
			{
				delete value;
			}
		}
	}
};

istream& operator>>(istream& in, Value& val);
istream& operator>>(istream& in, JsonObject& obj);
istream& operator>>(istream& in, JsonArray& arr);

ostream& operator<<(ostream& out, Value& val);
ostream& operator<<(ostream& out, JsonObject& obj);
ostream& operator<<(ostream& out, JsonArray& arr);