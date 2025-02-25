#pragma once
#include <map>
#include <string>
#include <vector>

#ifndef ActivityTypeArray_H
#define ActivityTypeArray_H


extern std::map<std::string, std::vector<std::string>> ActivityTypeArray;

extern std::map<std::string, std::vector<std::string>> TriggersTypeArray;
extern std::map<std::string, std::vector<std::string>> LinksTypeArray;

extern std::map <std::string, std::string> tipsTriggersENG;
extern std::map <std::string, std::string> tipsTriggersRUS;

extern std::map <std::string, std::string> tipsActionsENG;
extern std::map <std::string, std::string> tipsActionsRUS;


extern std::map<std::string, std::string>  DefaultValues;
#endif 