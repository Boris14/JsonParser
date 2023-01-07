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
	string str;
	bool flag = false;
	struct JsonObject *obj = nullptr;
	struct JsonArray *arr = nullptr;
	ValueType type = ValueType::EMPTY;

	Value() {}
	Value(string str) : str(str) {}
	~Value();

	void changeValue(string newValue);

private:
	void destroy();
};

struct JsonObject
{
	map<string, Value*> keyValueMap;
	vector<Value> find(string key);
	~JsonObject();
};

struct JsonArray
{
	vector<Value*> values;
	vector<Value> find(string key);
	~JsonArray();
};

istream& operator>>(istream& in, Value& val);
istream& operator>>(istream& in, JsonObject& obj);
istream& operator>>(istream& in, JsonArray& arr);

ostream& operator<<(ostream& out, Value& val);
ostream& operator<<(ostream& out, JsonObject& obj);
ostream& operator<<(ostream& out, JsonArray& arr);