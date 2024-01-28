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
	{"0", {"TriggerType0:d", "TriggerName0:s"}},

	{"3", {"TriggerType0:d", "TriggerName0:s",  "Volume0:g",    "Character0:g", "TriggersOnce0:d",
	"AllNPCs0:d",    "StaysTrue0:d",    "TriggeredOnTrue0:d"}}
};
std::map<std::string, std::vector<std::string>> LinksTypeArray = {
	{"0", { "LinkRepeats0:d", "LinkState0:d" ,"LogicType0:d", "LinkTriggerCount0:d",   "LinkActionCount0:d" }},
	{"1",  { "LinkRepeats0:d", "LinkState0:d" ,"LogicType0:d", "LinkTriggerCount0:d",  "LinkTriggerIndex0-", "LinkActionCount0:d", "LinkActionIndex0-"}}
};
std::map<std::string, std::string>  DefaultValues = {
	{"LinkRepeats0:d", "0"},
	{"LinkState0:d", "0"},
	{"LogicType0:d", "0"},
	{"LinkTriggerCount0:d", "1"},
	{"LinkTriggerIndex0-", "0"},
	{"LinkActionCount0:d", "1"},
	{"LinkActionIndex0-0:d", "0"},
	{"TriggerName0:s", "\"DefaultName\""},
	{"Volume0:g", "00000000_00000000"},
	{"Character0:g", "00000000_00000000"},
	{"TriggersOnce0:d", "0"},
	{"AllNPCs0:d", "0"},
	{"StaysTrue0:d", "0"},
	{"TriggeredOnTrue0:d", "0"},
	{"ActionName0:s", "\"DefaultName\""},
	{"Action0ExecuteDelay:f", "0.000000"},
	{"Action0ExecuteImmediately:d", "0"},
	{"Action0SwitchGuid:g", "00000000_00000000"},
	{"Action0CharacterGuid:g", "00000000_00000000"},
	{"Action0DialogName:s", "\"DialogName\""},
	{"Action0SwitchOn:d", "0"},
	{"Action0Toggle:d", "0"},
	{"Action0AIStateName:s", "\"Idle\""},
	{"Action0Team:d", "0"},
	{"Action0GoalListName:s", "\"Idle\""},
	{"Action0OverrideCinematicAnimation:d", "0"},
	{"Action0Speaker:g", "00000000_00000000"},
	{"Action0AtLocation:d", "0"},
	{"Action0BilboDialog:d", "0"},
};
