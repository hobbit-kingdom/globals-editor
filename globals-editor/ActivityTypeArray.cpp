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
	"Action0Speaker:g", "Action0AtLocation:d", "Action0BilboDialog:d" }},

	{"8",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0DialogSelectionMethod:d", "Action0DialogCount:d", "Action0DialogName0:s", "Action0Speaker:g", "Action0AtLocation:d", "Action0BilboDialog:d" } },

	{"9",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Item:s", "Action0Add:d", "Action0Amount:d", "Action0SourceGuid:g" }},

	{"10",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0LoadLayerGuid:g" }},

	{"11",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0SpawnCount:d", "Action0NPCGuid0:g", "Action0LocationGuid0:g", "Action0FacingGuid0:g", "Action0Animation0:s" }},

	{"12",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Link:s", "Action0LinkState:d" }},

	{"13",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0State:s", "Action0NPC:g" }},

	{"14",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Trigger:g" }},

	{"15",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Object:g", "Action0Volume:g", "Action0Facing:g" }},

	{"16",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0NPCCount:d", "Action0NPCGuid0:g", "Action0Health:d" } },

	{"17",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Object:g", "Action0Amount:d" }},

	{"18",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0StringID:s", "Action0Scroll:d", "Action0DelayTime:f" }},

	{"19",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d" }},

	{"20",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0cinemaCount:d", "Action0cinemaSelect:d", "Action0cinema0Guid:g" }},

	{"21",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0NPCGuid:g", "Action0CinemaCount:d", "Action0SelectionMethod:d", "Action0Cinema0:g" }},

	{"22",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0QuestID:s", "Action0Required:d" }},

	{"23",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0IdleAnim:s", "Action0NPC:g" }},

	{"25",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0DoStateController:d", "Action0NPC:g" }},

	{"28",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0DoRender:d", "Action0NPCCount:d", "Action0NPCGuid0:g" }},

	{"29",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0QuestID:s" }},

	{"30",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Fadeout:d", "Action0Color:dddd", "Action0Duration:f" }},

	{"33",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0InstanceCount:d", "Action0RigidInstance0:g", "Action0AnimIndex:d", "Action0Loops:d" }},

	{"34",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0QuestID:s" }},

	{"35",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0RopeCount:d", "Action0RopeGuid0:g", "Action0RopeLength0:f" }},

	{"36",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Object:g", "Action0Collides:d", "Action0BilboCollides:d", "Action0NPCCollides:d" }},

	{"37",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0InvulnGuid:g", "Action0InvulnOn:d" } },

	{"40",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0MusicTrigger:g" }},

	{"41",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0DoRootToPosition:d", "Action0ResetRootPosition:d", "Action0NPC:g" }},

	{"43",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Enable:d", "Action0MaterialName:s" }},

	{"44",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d" }},

	{"45",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0AmbientAudioTrigger:g" }},

	{"48",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0Amp:f", "Action0Time:f" }},

	{"49",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0RigidInstance:g", "Action0Hidden:d" }},

	{"50",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0DoRunAI:d", "Action0NPC:g" }},

	{"51",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0DoRenderProp:d", "Action0NPC:g" }},

	{"52",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d", "Action0RigidInstance:g", "Action0Hoistable:d" }}

};
std::map<std::string, std::vector<std::string>> TriggersTypeArray = {
	{"0", {"TriggerType0:d", "TriggerName0:s"}},

	{"3", {"TriggerType0:d", "TriggerName0:s",  "Volume0:g",    "Character0:g", "TriggersOnce0:d",
	"AllNPCs0:d",    "StaysTrue0:d",    "TriggeredOnTrue0:d"}},

	{"5", { "TriggerType0:d", "TriggerName0:s", "CheckTime0:f", "RandomPercent0:d", "StaysTrue0:d", "TriggeredOnTrue0:d"}},

	{"6", { "TriggerType0:d", "TriggerName0:s", "NPC0:g", "AttackType0:d", "StaysTrue0:d", "TriggeredOnTrue0:d"}},

	{"7",  { "TriggerType0:d", "TriggerName0:s", "NPCCount0:d", "Trigger0NPC0:g", "ExitState0:d", "EnterState0:d", "StaysTrue0:d", "TriggeredOnTrue0:d"}},

	{"8", { "TriggerType0:d", "TriggerName0:s", "NPC0:g", "ActionName0:s", "StaysTrue0:d", "TriggeredOnTrue0:d"}},

	{"9", { "TriggerType0:d", "TriggerName0:s", "Item0:s", "Amount0:d", "StaysTrue0:d", "TriggeredOnTrue0:d"}},

	{"11",{ "TriggerType0:d", "TriggerName0:s", "NPCCount0:d", "Trigger0NPC0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" } },

	{"12",{ "TriggerType0:d", "TriggerName0:s", "Web0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"15",{ "TriggerType0:d", "TriggerName0:s", "Character0:g", "AnimationName0:s", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"16",{ "TriggerType0:d", "TriggerName0:s", "And0:d", "Count0:d", "Trigger0NPC0:g", "Trigger0State0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"17",{ "TriggerType0:d", "TriggerName0:s", "NPC0:g", "GoalListName0:s", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"18",{ "TriggerType0:d", "TriggerName0:s", "Trigger0:g", "TriggerToggle0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"19",{ "TriggerType0:d", "TriggerName0:s", "Cinema0:g", "TriggerOnce0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"20",{ "TriggerType0:d", "TriggerName0:s", "Damager0:g", "Damaged0:g", "PainType0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"21",{ "TriggerType0:d", "TriggerName0:s", "Cinema0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"22",{ "TriggerType0:d", "TriggerName0:s", "StaysTrue0:d", "TriggeredOnTrue0:d" } },

	{"23",{ "TriggerType0:d", "TriggerName0:s", "Switch0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"24",{ "TriggerType0:d", "TriggerName0:s", "QuestName0:s", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"25",{ "TriggerType0:d", "TriggerName0:s", "Volume0:g", "Object0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"26",{ "TriggerType0:d", "TriggerName0:s", "NPCSensing0:g", "CharacterSensed0:g", "Senses0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"29",{ "TriggerType0:d", "TriggerName0:s", "RigidInstance0:g", "Animation0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"30",{ "TriggerType0:d", "TriggerName0:s", "RigidInstance0:g", "Animation0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"31",{ "TriggerType0:d", "TriggerName0:s", "Item0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"32",{ "TriggerType0:d", "TriggerName0:s", "Vine0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"34",{ "TriggerType0:d", "TriggerName0:s", "RigidInstance0:g", "Animation0:d", "StaysTrue0:d", "TriggeredOnTrue0:d" }}

};
std::map<std::string, std::vector<std::string>> LinksTypeArray = {
	{"0", { "LinkRepeats0:d", "LinkState0:d" ,"LogicType0:d", "LinkTriggerCount0:d",   "LinkActionCount0:d" }},
	{"1",  { "LinkRepeats0:d", "LinkState0:d" ,"LogicType0:d", "LinkTriggerCount0:d",  "LinkTriggerIndex0-", "LinkActionCount0:d", "LinkActionIndex0-"}}
};

std::map <std::string, std::string> tipsTriggersENG = {
	{ "3", "Npc enters Volume" },
	{ "5", "Activates after a certain amount of time with some kind of chance" },
	{ "6", "Stone hits a npc" },
	{ "7", "Npc changes states" },
	{ "8", "Npc does an activity" },
	{ "9", "Bilbo has an item" },
	{ "11", "Npc dies" },
	{ "12", "Web is torn" },
	{ "15", "Npc does some animation" },
	{ "16", "State is activated on a npc" },
	{ "17", "Npcs' Goal list state activated" },
	{ "18", "Another trigger is activated" },
	{ "19", "Cutscene ends" },
	{ "20", "Someone damages someone with some type of damage" },
	{ "21", "Cutscene starts" },
	{ "22", "Something about Lightning" },
	{ "23", "Switch is activated" },
	{ "24", "Quest is completed" },
	{ "25", "Object is in Volume" },
	{ "26", "Npc has some feeling activated because of npc" },
	{ "29", "RigidInstance starts playing an animation" },
	{ "30", "RigidInstance animation ends" },
	{ "31", "Bilbo has a certain item" },
	{ "32", "When Bilbo jumped on the rope" },
	{ "34", "RigidInstance has no animation activated" }
};

std::map <std::string, std::string> tipsTriggersRUS = {
	{ "3",  (const char*)u8"Нпс заходит в волум" } ,
	{ "5",  (const char*)u8"Срабатывает через какое-то время с каким-то шансом" } ,
	{ "6",  (const char*)u8"По нпс попадает камень" } ,
	{ "7",  (const char*)u8"Нпс выходит из одного состояния и входит в другое" } ,
	{ "8",  (const char*)u8"Нпс делает активность" }
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
