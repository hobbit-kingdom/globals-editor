#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "ActivityTypeArray.h"

using namespace std;

string replaceStr(string orig_str, const string& replace_string, const string& with_string) {
	size_t pos = orig_str.find(replace_string);

	if (pos != std::string::npos)
		orig_str.replace(pos, replace_string.length(), with_string);

	return orig_str;
}

vector<string> compileAction(vector<string> parameters, int type, int objectNumber, string vibor)
{
	vector<string> compiled;
	string typeRow = "{ ";
	string paramerRow = "";

	if (vibor == "Actions")
	{
		compiled.push_back("[ Action" + to_string(objectNumber) + " : 1 ]");

		string typeS = to_string(type);

		for (auto i : ActivityTypeArray[typeS]) {
			typeRow += replaceStr(i, "0", to_string(objectNumber)) + " ";
		}

		typeRow += "}";

		compiled.push_back(typeRow);

		for (auto i : parameters) {
			paramerRow += i + " ";
		}
	}
	else if (vibor == "Triggers")
	{
		compiled.push_back("[ Trigger" + to_string(objectNumber) + " : 1 ]");

		string typeS = to_string(type);

		for (auto i : TriggersTypeArray[typeS]) {
			typeRow += replaceStr(i, "0", to_string(objectNumber)) + " ";
		}

		typeRow += "}";

		compiled.push_back(typeRow);

		for (auto i : parameters) {
			paramerRow += i + " ";
		}
	}

	compiled.push_back(paramerRow);

	return compiled;
}
vector<string> parametersObj = { "LinkRepeats0:d", "LinkState0:d" ,"LogicType0:d", "LinkTriggerCount0:d",  "LinkTriggerIndex0-", "LinkActionCount0:d", "LinkActionIndex0-" };
vector<string> compileLink(vector<string> parameters, vector<string> triggers, vector<string> actions, int type, int objectNumber)
{
	vector<string> compiled;
	string typeRow = "{ ";
	string paramerRow = "";
	compiled.push_back("[ Link" + to_string(objectNumber) + " : 1 ]");

	string typeS = to_string(type);

	for (int i = 0; i < 7; i++) {
		cout << i << " ";

		if (i == 4)
		{
			for (int j = 0; j < triggers.size(); j++)
				typeRow += replaceStr("LinkTriggerIndex0-" + to_string(j) + ":d", "0", to_string(objectNumber)) + " ";
		}
		else if (i == 6)
		{
			for (int j = 0; j < actions.size(); j++)
				typeRow += replaceStr("LinkActionIndex0-" + to_string(j) + ":d", "0", to_string(objectNumber)) + " ";

		}
		else
			typeRow += replaceStr(parametersObj[i], "0", to_string(objectNumber)) + " ";
	}

	typeRow += "}";

	compiled.push_back(typeRow);

	for (int i = 0; i < parameters.size(); i++) {
		if (i != 4 && i != 6) paramerRow += parameters[i] + " ";
		if (i == 4)
		{
			for (auto j : triggers)
				paramerRow += j + " ";
		}
		else if (i == 6)
		{
			for (auto j : actions)
				paramerRow += j + " ";
		}
	}
	compiled.push_back(paramerRow);

	return compiled;
}


void insertText(string filename, int line_number, vector<string> insertText)
{
	std::ifstream input_file(filename);
	vector<string> lines;
	std::string line;

	while (std::getline(input_file, line)) {
		lines.push_back(line);
	}

	input_file.close();

	for (int i = 0; i < insertText.size(); i++)
		lines.insert(lines.begin() + line_number - 1 + i, insertText[i]);

	std::ofstream output_file(filename);

	for (const std::string& updated_line : lines) {
		output_file << updated_line << "\n";
	}

	output_file.close();

	std::cout << "Text inserted successfully at line " << line_number << std::endl;
}

void replaceText(string filename, int start_line_number, vector<string> insertText)
{
	std::ifstream input_file(filename);
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(input_file, line)) {
		lines.push_back(line);
	}

	input_file.close();

	for (int i = 0; i < insertText.size(); ++i)
	{
		if (start_line_number - 1 + i < lines.size()) lines[start_line_number - 1 + i] = insertText[i];
		else
		{
			std::cerr << "Error: Line " << start_line_number + i << " not found in the file." << std::endl;
			return;
		}
	}

	std::ofstream output_file(filename);

	for (const std::string& updated_line : lines) {
		output_file << updated_line << "\n";
	}

	output_file.close();

	std::cout << "Lines were replaced successfully." << std::endl;
}