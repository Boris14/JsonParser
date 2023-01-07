#include <iostream>
#include "JsonParser.h"

using namespace std;

int main()
{
	try
	{
		JsonParser parser{ "TestFile" };
		parser.change("pockets/left", "wallet");
		parser.write("TestWrite");
		auto result = parser.find("name");
		for (auto elem : result)
		{
			cout << elem << endl;
		}
	}
	catch (const char* error)
	{
		cout << error << endl;
	}

	return 0;
}