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

	{"8",{ "ActionType162:d", "ActionName162:s", "Action162ExecuteDelay:f", "Action162ExecuteImmediately:d", "Action162DialogSelectionMethod:d", "Action162DialogCount:d", "Action162DialogName0:s", "Action162Speaker:g", "Action162AtLocation:d", "Action162BilboDialog:d" } },

	{"9",{ "ActionType143:d", "ActionName143:s", "Action143ExecuteDelay:f", "Action143ExecuteImmediately:d", "Action143Item:s", "Action143Add:d", "Action143Amount:d", "Action143SourceGuid:g" }},

	{"10",{ "ActionType3:d", "ActionName3:s", "Action3ExecuteDelay:f", "Action3ExecuteImmediately:d", "Action3LoadLayerGuid:g" }},

	{"11",{ "ActionType12:d", "ActionName12:s", "Action12ExecuteDelay:f", "Action12ExecuteImmediately:d", "Action12SpawnCount:d", "Action12NPCGuid0:g", "Action12LocationGuid0:g", "Action12FacingGuid0:g", "Action12Animation0:s" }},

	{"12",{ "ActionType3:d", "ActionName3:s", "Action3ExecuteDelay:f", "Action3ExecuteImmediately:d", "Action3Link:s", "Action3LinkState:d" }},

	{"13",{ "ActionType99:d", "ActionName99:s", "Action99ExecuteDelay:f", "Action99ExecuteImmediately:d", "Action99State:s", "Action99NPC:g" }},

	{"14",{ "ActionType148:d", "ActionName148:s", "Action148ExecuteDelay:f", "Action148ExecuteImmediately:d", "Action148Trigger:g" }},

	{"15",{ "ActionType47:d", "ActionName47:s", "Action47ExecuteDelay:f", "Action47ExecuteImmediately:d", "Action47Object:g", "Action47Volume:g", "Action47Facing:g" }},

	{"16",{ "ActionType132:d", "ActionName132:s", "Action132ExecuteDelay:f", "Action132ExecuteImmediately:d", "Action132NPCCount:d", "Action132NPCGuid0:g", "Action132Health:d" } },

	{"17",{ "ActionType238:d", "ActionName238:s", "Action238ExecuteDelay:f", "Action238ExecuteImmediately:d", "Action238Object:g", "Action238Amount:d" }},

	{"18",{ "ActionType70:d", "ActionName70:s", "Action70ExecuteDelay:f", "Action70ExecuteImmediately:d", "Action70StringID:s", "Action70Scroll:d", "Action70DelayTime:f" }},

	{"19",{ "ActionType0:d", "ActionName0:s", "Action0ExecuteDelay:f", "Action0ExecuteImmediately:d" }},

	{"20",{ "ActionType1:d", "ActionName1:s", "Action1ExecuteDelay:f", "Action1ExecuteImmediately:d", "Action1cinemaCount:d", "Action1cinemaSelect:d", "Action1cinema0Guid:g" }},

	{"21",{ "ActionType21:d", "ActionName21:s", "Action21ExecuteDelay:f", "Action21ExecuteImmediately:d", "Action21NPCGuid:g", "Action21CinemaCount:d", "Action21SelectionMethod:d", "Action21Cinema0:g" }},

	{"22",{ "ActionType48:d", "ActionName48:s", "Action48ExecuteDelay:f", "Action48ExecuteImmediately:d", "Action48QuestID:s", "Action48Required:d" }},

	{"23",{ "ActionType90:d", "ActionName90:s", "Action90ExecuteDelay:f", "Action90ExecuteImmediately:d", "Action90IdleAnim:s", "Action90NPC:g" }},

	{"25",{ "ActionType84:d", "ActionName84:s", "Action84ExecuteDelay:f", "Action84ExecuteImmediately:d", "Action84DoStateController:d", "Action84NPC:g" }},

	{"28",{ "ActionType87:d", "ActionName87:s", "Action87ExecuteDelay:f", "Action87ExecuteImmediately:d", "Action87DoRender:d", "Action87NPCCount:d", "Action87NPCGuid0:g" }},

	{"29",{ "ActionType51:d", "ActionName51:s", "Action51ExecuteDelay:f", "Action51ExecuteImmediately:d", "Action51QuestID:s" }},

	{"30",{ "ActionType65:d", "ActionName65:s", "Action65ExecuteDelay:f", "Action65ExecuteImmediately:d", "Action65Fadeout:d", "Action65Color:dddd", "Action65Duration:f" }},

	{"33",{ "ActionType4:d", "ActionName4:s", "Action4ExecuteDelay:f", "Action4ExecuteImmediately:d", "Action4InstanceCount:d", "Action4RigidInstance0:g", "Action4AnimIndex:d", "Action4Loops:d" }},

	{"34",{ "ActionType49:d", "ActionName49:s", "Action49ExecuteDelay:f", "Action49ExecuteImmediately:d", "Action49QuestID:s" }},

	{"35",{ "ActionType56:d", "ActionName56:s", "Action56ExecuteDelay:f", "Action56ExecuteImmediately:d", "Action56RopeCount:d", "Action56RopeGuid0:g", "Action56RopeLength0:f" }},

	{"36",{ "ActionType73:d", "ActionName73:s", "Action73ExecuteDelay:f", "Action73ExecuteImmediately:d", "Action73Object:g", "Action73Collides:d", "Action73BilboCollides:d", "Action73NPCCollides:d" }},

	{"37",{ "ActionType248:d", "ActionName248:s", "Action248ExecuteDelay:f", "Action248ExecuteImmediately:d", "Action248InvulnGuid:g", "Action248InvulnOn:d" } },

	{"40",{ "ActionType66:d", "ActionName66:s", "Action66ExecuteDelay:f", "Action66ExecuteImmediately:d", "Action66MusicTrigger:g" }},

	{"41",{ "ActionType9:d", "ActionName9:s", "Action9ExecuteDelay:f", "Action9ExecuteImmediately:d", "Action9DoRootToPosition:d", "Action9ResetRootPosition:d", "Action9NPC:g" }},

	{"43",{ "ActionType265:d", "ActionName265:s", "Action265ExecuteDelay:f", "Action265ExecuteImmediately:d", "Action265Enable:d", "Action265MaterialName:s" }},

	{"44",{ "ActionType258:d", "ActionName258:s", "Action258ExecuteDelay:f", "Action258ExecuteImmediately:d" }},

	{"45",{ "ActionType26:d", "ActionName26:s", "Action26ExecuteDelay:f", "Action26ExecuteImmediately:d", "Action26AmbientAudioTrigger:g" }},

	{"48",{ "ActionType28:d", "ActionName28:s", "Action28ExecuteDelay:f", "Action28ExecuteImmediately:d", "Action28Amp:f", "Action28Time:f" }},

	{"49",{ "ActionType36:d", "ActionName36:s", "Action36ExecuteDelay:f", "Action36ExecuteImmediately:d", "Action36RigidInstance:g", "Action36Hidden:d" }},

	{"50",{ "ActionType84:d", "ActionName84:s", "Action84ExecuteDelay:f", "Action84ExecuteImmediately:d", "Action84DoRunAI:d", "Action84NPC:g" }},

	{"51",{ "ActionType70:d", "ActionName70:s", "Action70ExecuteDelay:f", "Action70ExecuteImmediately:d", "Action70DoRenderProp:d", "Action70NPC:g" }},

	{"52",{ "ActionType269:d", "ActionName269:s", "Action269ExecuteDelay:f", "Action269ExecuteImmediately:d", "Action269RigidInstance:g", "Action269Hoistable:d" }}

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

	{"11",{ "TriggerType6:d", "TriggerName6:s", "NPCCount6:d", "Trigger6NPC0:g", "StaysTrue6:d", "TriggeredOnTrue6:d" } },

	{"12",{ "TriggerType9:d", "TriggerName9:s", "Web9:g", "StaysTrue9:d", "TriggeredOnTrue9:d" }},

	{"15",{ "TriggerType27:d", "TriggerName27:s", "Character27:g", "AnimationName27:s", "StaysTrue27:d", "TriggeredOnTrue27:d" }},

	{"16",{ "TriggerType1:d", "TriggerName1:s", "And1:d", "Count1:d", "Trigger1NPC0:g", "Trigger1State0:d", "StaysTrue1:d", "TriggeredOnTrue1:d" }},

	{"17",{ "TriggerType15:d", "TriggerName15:s", "NPC15:g", "GoalListName15:s", "StaysTrue15:d", "TriggeredOnTrue15:d" }},

	{"18",{ "TriggerType79:d", "TriggerName79:s", "Trigger79:g", "TriggerToggle79:d", "StaysTrue79:d", "TriggeredOnTrue79:d" }},

	{"19",{ "TriggerType2:d", "TriggerName2:s", "Cinema2:g", "TriggerOnce2:d", "StaysTrue2:d", "TriggeredOnTrue2:d" }},

	{"20",{ "TriggerType95:d", "TriggerName95:s", "Damager95:g", "Damaged95:g", "PainType95:d", "StaysTrue95:d", "TriggeredOnTrue95:d" }},

	{"21",{ "TriggerType90:d", "TriggerName90:s", "Cinema90:g", "StaysTrue90:d", "TriggeredOnTrue90:d" }},

	{"22",{ "TriggerType87:d", "TriggerName87:s", "StaysTrue87:d", "TriggeredOnTrue87:d" } },

	{"23",{ "TriggerType52:d", "TriggerName52:s", "Switch52:g", "StaysTrue52:d", "TriggeredOnTrue52:d" }},

	{"24",{ "TriggerType8:d", "TriggerName8:s", "QuestName8:s", "StaysTrue8:d", "TriggeredOnTrue8:d" }},

	{"25",{ "TriggerType113:d", "TriggerName113:s", "Volume113:g", "Object113:g", "StaysTrue113:d", "TriggeredOnTrue113:d" }},

	{"26",{ "TriggerType86:d", "TriggerName86:s", "NPCSensing86:g", "CharacterSensed86:g", "Senses86:d", "StaysTrue86:d", "TriggeredOnTrue86:d" }},

	{"29",{ "TriggerType57:d", "TriggerName57:s", "RigidInstance57:g", "Animation57:d", "StaysTrue57:d", "TriggeredOnTrue57:d" }},

	{"30",{ "TriggerType121:d", "TriggerName121:s", "RigidInstance121:g", "Animation121:d", "StaysTrue121:d", "TriggeredOnTrue121:d" }},

	{"31",{ "TriggerType36:d", "TriggerName36:s", "Item36:g", "StaysTrue36:d", "TriggeredOnTrue36:d" }},

	{"32",{ "TriggerType0:d", "TriggerName0:s", "Vine0:g", "StaysTrue0:d", "TriggeredOnTrue0:d" }},

	{"34",{ "TriggerType139:d", "TriggerName139:s", "RigidInstance139:g", "Animation139:d", "StaysTrue139:d", "TriggeredOnTrue139:d" }}

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
