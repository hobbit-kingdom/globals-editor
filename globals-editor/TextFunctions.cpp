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

vector<string> compileLink(vector<string> parameters, vector<string> parametersObj, int type, int objectNumber)
{
	vector<string> compiled;
	string typeRow = "{ ";
	string paramerRow = "";
	compiled.push_back("[ Link" + to_string(objectNumber) + " : 1 ]");

	string typeS = to_string(type);

	for (auto i : parametersObj) {
		typeRow += replaceStr(i, "0", to_string(objectNumber)) + " ";
	}

	typeRow += "}";

	compiled.push_back(typeRow);

	for (auto i : parameters) {
		paramerRow += i + " ";
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