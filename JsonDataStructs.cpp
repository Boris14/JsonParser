#include "JsonDataStructs.h"
#include <cassert>

using namespace std;

char peekNext(istream& in)
{
    char next = in.peek();
    if (next == EOF)
        throw "End of File reached";
    return next;
}

char getNext(istream& in)
{
    char next = in.get();
    if (next == EOF)
        throw "End of File reached";
    return next;
}

void consumeWhiteSpace(istream& in)
{
    char next = peekNext(in);
    while (iswspace(next))
    {
        in.get();
        next = peekNext(in);
    }
}

string consumeString(istream& in)
{
    string result;
    char next = peekNext(in);

    if (next != '\"')
        throw "Invalid Json String (should start with \")";
    in.get();

    next = getNext(in);

    bool closingQuote = false;
    while (next != '\"' || !closingQuote)
    {
        result.push_back(next);
        next = getNext(in);

        if (next != '\"')
        {
            closingQuote = next != '\\';
        }
    }

    return result;
}

istream& operator>>(istream& in, JsonArray& arr)
{
    char next = peekNext(in);

    if (next != '[')
        throw "Invalid JsonArray (maybe a missing opening par)";
    in.get();

    consumeWhiteSpace(in);
    next = peekNext(in);

    if (next != ']')
    {
        bool moreValues = true;
        while (moreValues)
        {
            Value* newVal = new Value;
            in >> *newVal;
            arr.values.push_back(newVal);
            next = getNext(in);
            moreValues = next == ',';
        }
    }

    if(next != ']')
        throw "Invalid JsonArray (maybe a missing closing par)";
    return in;
}

istream& operator>>(istream& in, Value& val)
{
    char next = peekNext(in);

    consumeWhiteSpace(in);
    next = peekNext(in);

    if (isdigit(next))
    {
        val.type = Value::ValueType::NUMBER;
        in >> val.number;
    }
    else
    {
        string valueString;
        switch (next)
        {
            case '\"':
                val.type = Value::ValueType::STRING;
                val.name = consumeString(in);
                break;
            case '{':
                val.type = Value::ValueType::OBJECT;
                val.obj = new JsonObject;
                in >> *val.obj;
                break;
            case '[':
                val.type = Value::ValueType::ARRAY;
                val.arr = new JsonArray;
                in >> *val.arr;
                break;
            case 't':
                val.type = Value::ValueType::BOOL;
                in >> valueString;
                if (valueString[valueString.length() - 1] == ',')    valueString.pop_back();
                if (valueString.compare("true") != 0)
                {
                    throw "Invalid Value (maybe you meant \"true\")";
                }
                val.flag = true;
                break;
            case 'f':
                val.type = Value::ValueType::BOOL;
                in >> valueString;
                if (valueString[valueString.length() - 1] == ',')    valueString.pop_back();
                if (valueString.compare("false") != 0)
                {
                    throw "Invalid Value (maybe you meant \"false\")";
                }
                val.flag = false;
                break;
            case 'n':
                val.type = Value::ValueType::EMPTY;
                in >> valueString;
                if (valueString[valueString.length() - 1] == ',')    valueString.pop_back();
                if (valueString.compare("null") != 0)
                {
                    throw "Invalid Value (maybe you meant \"null\")";
                }
                break;
        }   
    }
    consumeWhiteSpace(in);
    return in;
}

istream& operator>>(istream& in, JsonObject& obj)
{
    char next = peekNext(in);

    if (next != '{')
        throw "Invalid JsonObject (maybe a missing opening par)";
    in.get();

    next = peekNext(in);

    while (next == ',' || next != '}' && in && !in.eof())
    {   
        consumeWhiteSpace(in);
        next = peekNext(in);
        if (next == '\"')
        {
            string key;
            Value* value = new Value;
            key = consumeString(in);
            consumeWhiteSpace(in);
            next = getNext(in);
            if (next != ':')
                throw "Invalid JsonObject (maybe a missing \":\" between a key and a value)";
            in >> *value;
            obj.keyValueMap.insert(pair<string, Value*>(key, value));
            next = getNext(in);
        }
        else
        {
            getNext(in);
            break;
        }

        if (next != ',' && next != '}')
            throw "Invalid JsonObject (maybe a missing closing par or a missing comma)";
    }
    if(next != '}')
        throw "Invalid JsonObject (maybe a missing closing par)";
    return in;
}

ostream& operator<<(ostream& out, Value& val)
{
    out << ' ';

    switch (val.type)
    {
        case Value::ValueType::EMPTY:
            return out;

        case Value::ValueType::BOOL:
            out << val.flag ? "true" : "false";
            break;

        case Value::ValueType::NUMBER:
            out << val.number;
            break;

        case Value::ValueType::STRING:
            out << '\"' << val.name << '\"';
            break;

        case Value::ValueType::OBJECT:
            out << *val.obj;
            break;

        case Value::ValueType::ARRAY:
            out << *val.arr;
            break;

        default:
            break;
    }
    
    out << ' ';

    return out;
}

ostream& operator<<(ostream& out, JsonObject& obj)
{
    out << '{';

    int i = 0;
    for (pair<string, Value*> JsonPair : obj.keyValueMap)
    {
        out << endl << '\"' << JsonPair.first << "\" :" << *JsonPair.second;
        ++i;
        if (i < obj.keyValueMap.size())
        {
            out << ',';
        }
    }

    out << endl << '}';
    
    return out;
}

ostream& operator<<(ostream& out, JsonArray& arr)
{
    out << '[';

    int i = 0;
    for (Value* val : arr.values)
    {
        out << *val;
        ++i;
        if (i < arr.values.size())
        {
            out << ',';
        }
    }

    out << ']';

    return out;
}

