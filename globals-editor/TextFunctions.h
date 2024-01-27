#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

vector<string> compileAction(vector<string> parameters, int type, int actionNumber, string vibor);
vector<string> compileLink(vector<string> parameters, vector<string> parametersObj, int type, int objectNumber);
void insertText(string filename, int line_number, vector<string> insertText);
void replaceText(string filename, int start_line_number, vector<string> insertText);
