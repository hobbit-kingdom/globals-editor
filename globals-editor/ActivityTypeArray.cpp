#include "ActivityTypeArray.h"

// Define and initialize the map
std::map<std::string, std::vector<std::string>> ActivityTypeArray = {

	{"0", {"ActionType0:d", "ActionName0:s"}},

	{"1", {"ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d",
	"Action0SwitchGuid:g", "Action0SwitchOn:d", "Action0Toggle:d"}},

	{"2", {"ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d",
	"Action0CharacterGuid:g", "Action0Team:d"}},

	{"4", {"ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d",
	"Action0CharacterGuid:g", "Action0AIStateName:s", "Action0GoalListName:s", "Action0OverrideCinematicAnimation:d"}},

	{"7", {"ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0DialogName:s",
	"Action0Speaker:g", "Action0AtLocation:d", "Action0BilboDialog:d" }}
};
std::map<std::string, std::vector<std::string>> TriggersTypeArray = {
	{"3", {"TriggerType0:d", "TriggerName0:s",  "Volume0:g",    "Character0:g", "TriggersOnce0:d",
	"AllNPCs0:d",    "StaysTrue0:d",    "TriggeredOnTrue0:d"}}
};
std::map<std::string, std::string>  DefaultValues = {
	{"ActionName0:s", "DefaultName"},
	{"Action0ExecuteDelay:f", "0.000000"},
	{"Action0ExecuteImmediately:d", "0"},
	{"Action0SwitchGuid:g", "00000000_00000000"},
	{"Action0CharacterGuid:g", "00000000_00000000"},
	{"Action0DialogName:s", "DefaultName"},
	{"Action0SwitchOn:d", "0"},
	{"Action0Toggle:d", "0"},
	{"Action0AIStateName:s", "Idle"},
	{"Action0Team:d", "0"},
	{"Action0GoalListName:s", "Idle"},
	{"Action0OverrideCinematicAnimation:d", "0"},
	{"Action0Speaker:g", "00000000_00000000"},
	{"Action0AtLocation:d", "0"},
	{"Action0BilboDialog:d", "0"},
};
