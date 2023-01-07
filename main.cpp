#include <iostream>
#include "JsonParser.h"

using namespace std;

int main()
{
	try
	{
		JsonParser parser{ "TestFile" };
		parser.write("TestWrite");
	}
	catch (const char* error)
	{
		cout << error << endl;
	}

	return 0;
}