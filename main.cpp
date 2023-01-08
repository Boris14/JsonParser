#include <iostream>
#include "JsonParser.h"

using namespace std;

int main()
{
	JsonParser parser;
	cout << "Type \"info\" to see the available commands." << endl;
	while (parser.getIsActive())
	{
		try 
		{
			parser.handleInput();
		}
		catch (const char* error)
		{
			cout << "Error: " << error << endl << endl;
		}
	}

	return 0;
}