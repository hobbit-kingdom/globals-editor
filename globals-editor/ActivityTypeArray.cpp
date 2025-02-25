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
	{ "0", "Empty Trigger" },
	{ "3", "Npc enters Volume" },
	{ "5", "Activates after a certain amount of time with some kind of chance" },
	{ "6", "Stone hits a npc" },
	{ "7", "Npc changes states" },
	{ "8", "Npc does an activity" },
	{ "9", "Bilbo has an item"},
	{ "11", "Npc dies" },
	{ "12", "Web is torn" },
	{ "15", "Npc does some animation" },
	{ "16", "State is activated on a npc" },
	{ "17", "Npcs' Goal list state activated" },
	{ "18", "Trigger is activated" },
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
	{ "0",  (const char*)u8"Пустой триггер" } ,
	{ "3",  (const char*)u8"Нпс заходит в волум" } ,
	{ "5",  (const char*)u8"Срабатывает через какое-то время с каким-то шансом" } ,
	{ "6",  (const char*)u8"По нпс попадает камень" } ,
	{ "7",  (const char*)u8"Нпс выходит из одного состояния и входит в другое" } ,
	{ "8",  (const char*)u8"Нпс делает активность" },
	{ "9",  (const char*)u8"У Бильбо есть предмет"},
	{ "11", (const char*)u8"Нпс умирает" },
	{ "12", (const char*)u8"Паутина рвьется" },
	{ "15", (const char*)u8"Нпс проигрывает анимацию" },
	{ "16", (const char*)u8"Активируется какое-то состояние у нпс" },
	{ "17", (const char*)u8"Нпс активирует гоал лист" },
	{ "18", (const char*)u8"Активируется триггер" },
	{ "19", (const char*)u8"Катсцена закончилась" },
	{ "20", (const char*)u8"Кто-то нанес кому-то урон каким-то типом" },
	{ "21", (const char*)u8"Катсцена началась" },
	{ "22", (const char*)u8"Что-то о молнии" },
	{ "23", (const char*)u8"Переключатель активирован" },
	{ "24", (const char*)u8"Квест выполнен" },
	{ "25", (const char*)u8"Объект вошел в волум" },
	{ "26", (const char*)u8"У нпс активируется чуство из-за нпс" },
	{ "29", (const char*)u8"RigidInstance начал проигрывать анимацию" },
	{ "30", (const char*)u8"RigidInstance закончил анимацию" },
	{ "31", (const char*)u8"У Бильбо есть определенный предмет" },
	{ "32", (const char*)u8"Бильбо прыгнул на веревку" },
	{ "34", (const char*)u8"RigidInstance не проигрывает анимацию" }
};

std::map <std::string, std::string> tipsActionsENG = {
	{ "0", "Empty activity" },
	{ "1", "Toggles the switch" },
	{ "2", "Replaces the npc`s team" },
	{ "4", "Replace the npc`s state and started goallist" },
	{ "7", "Launches a dialog" },
	{ "8", "Launches one of the dialog" },
	{ "9", "Sets the number of item"},
	{ "10", "Activates a load triggers" },
	{ "11", "Spawn an npc in some location looking at something with some kind of animation" },
	{ "12", "Turns On/Off a link" },
	{ "13", "Replace npc`s state" },
	{ "14", "Actvates a trigger" },
	{ "15", "Teleports an object to something and turns it" },
	{ "16", "Change HP of the npc" },
	{ "17", "Spawns x of some pickup" },
	{ "18", "Displays a window with the text" },
	{ "19", "Finishes a level" },
	{ "20", "Activates a cutscene" },
	{ "21", "Replaces a cutscene for the npc" },
	{ "22", "Starts a quest" },
	{ "23", "Sets the animation of the NPC when inactive" },
	{ "25", "Changes the DoStateControl of a npc" },
	{ "28", "Show/hide npcs" },
	{ "29", "Removes a quest" },
	{ "30", "Activates fade in" },
	{ "33", "Starts the animation of the RigidInstance object" },
	{ "34", "Removes the quest"},
	{ "35", "Change the lenght of the rope"},
	{ "36", "Changes the objects collision of Bilbo and the npcs"},
	{ "37", "Set/remove invul from npc"},
	{ "40", "Activate a music trigger"},
	{ "41", "Change the npc position binding"},
	{ "43", "Something about the name of the material"},
	{ "44", "Kill Bilbo"},
	{ "45", "Turns the audio trigger on/off"},
	{ "48", "Something about dream ripple"},
	{ "49", "Hide/show RigidInstance"},
	{ "50", "Disable the AI of the npc"},
	{ "51", "Hide/show objects that npc has"},
	{ "52", "Something about hoistable"}
};

std::map <std::string, std::string> tipsActionsRUS = {
	{ "0",  (const char*)u8"Пустая активность" } ,
	{ "1",  (const char*)u8"Переключает переключатель" } ,
	{ "2",  (const char*)u8"Заменяет команду нпс" } ,
	{ "4",  (const char*)u8"Заменяет состояниет нпс и стартует гоал лист" } ,
	{ "7",  (const char*)u8"Запускает диалог" } ,
	{ "8",  (const char*)u8"Запускает один из диалогов" },
	{ "9",  (const char*)u8"Устанавливает кол-во предметов"},
	{ "10", (const char*)u8"Запускает загрузочный триггер" },
	{ "11", (const char*)u8"Спавнит нпс в каком-то месте, смотрящего на что-то с анимацией" },
	{ "12", (const char*)u8"Вкл/выкл ссылку" },
	{ "13", (const char*)u8"Заменяет состояние нпс" },
	{ "14", (const char*)u8"Активирует триггер" },
	{ "15", (const char*)u8"Телепортирует объект на что-то и поворачивает его" },
	{ "16", (const char*)u8"Меняет ХП у нпс" },
	{ "17", (const char*)u8"Спавнит пикап в каком-то количестве" },
	{ "18", (const char*)u8"Показывает окно с текстом" },
	{ "19", (const char*)u8"Завершает уровень" },
	{ "20", (const char*)u8"Активирует катсцену" },
	{ "21", (const char*)u8"Заменяет катсцену у нпс" },
	{ "22", (const char*)u8"Выдает квест" },
	{ "23", (const char*)u8"Устанавливает анимацию при бездействии" },
	{ "25", (const char*)u8"Меняет DoStateControl у нпс" },
	{ "28", (const char*)u8"Показывает/прячет нпс" },
	{ "29", (const char*)u8"Убирает квест" },
	{ "30", (const char*)u8"Запускает затухание" },
	{ "33", (const char*)u8"Активирует анимацию у RigidInstance" },
	{ "34", (const char*)u8"Убирает квест"},
	{ "35", (const char*)u8"Меняет длинну веревки"},
	{ "36", (const char*)u8"Меняет коллизию объектов у Бильбо и нпс"},
	{ "37", (const char*)u8"Устанавливает/убирает бессмертие у нпс"},
	{ "40", (const char*)u8"Активирует музыкальный триггер"},
	{ "41", (const char*)u8"Меняет привязку к месту у нпс"},
	{ "43", (const char*)u8"Что-то о имени материала"},
	{ "44", (const char*)u8"Убивает Бильбо"},
	{ "45", (const char*)u8"Включает/выключает аудио триггер"},
	{ "48", (const char*)u8"Что-то о dream ripple"},
	{ "49", (const char*)u8"Прячет/показывает RigidInstance"},
	{ "50", (const char*)u8"Отключает ИИ у нпс"},
	{ "51", (const char*)u8"Прячет/показывает предметы у нпс"},
	{ "52", (const char*)u8"Что-то о hoistable"}
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
	{"TriggeredOnTrue0:d", "1"},
	{"CheckTime0:f", "0.000000"},
	{"RandomPercent0:d", "0"},
	{"NPC0:g", "00000000_00000000"},
	{"AttackType0:d", "0"},
	{"NPCCount0:d", "1"},
	{"Trigger0NPC0:g", "00000000_00000000"},
	{"ExitState0:d", "0"},
	{"EnterState0:d", "0"},
	{"Item0:s", "\"DefaultName\""},
	{"Amount0:d", "1"},
	{"Web0:g", "00000000_00000000"},
	{"AnimationName0:s", "\"DefaultName\""},
	{"And0:d", "0"},
	{"Count0:d", "1"},
	{"Trigger0State0:d", "0"},
	{"GoalListName0:s", "\"DefaultName\""},
	{"Trigger0:g", "00000000_00000000"},
	{"TriggerToggle0:d", "0"},
	{"Cinema0:g", "00000000_00000000"},
	{"TriggerOnce0:d", "0"},
	{"Damager0:g", "00000000_00000000"},
	{"Damaged0:g", "00000000_00000000"},
	{"PainType0:d", "0"},
	{"Switch0:g", "00000000_00000000"},
	{"QuestName0:s", "\"DefaultName\""},
	{"Object0:g", "00000000_00000000"},
	{"NPCSensing0:g", "00000000_00000000"},
	{"CharacterSensed0:g", "00000000_00000000"},
	{"Senses0:d", "0"},
	{"RigidInstance0:g", "00000000_00000000"},
	{"Animation0:d", "0"},
	{"Item0:s", "\"DefaultName\""},
	{"Vine0:g", "00000000_00000000"},
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
	{"Action0DialogSelectionMethod:d", "0"},
	{"Action0DialogCount:d", "1"},
	{"Action0DialogName0:s", "\"DefaultName\""},
	{"Action0Item:s", "\"DefaultName\""},
	{"Action0Add:d", "1"},
	{"Action0Amount:d", "0"},
	{"Action0SourceGuid:g", "00000000_00000000"},
	{"Action0LoadLayerGuid:g", "00000000_00000000"},
	{"Action0SpawnCount:d", "1"},
	{"Action0NPCGuid0:g", "00000000_00000000"},
	{"Action0LocationGuid0:g", "00000000_00000000"},
	{"Action0FacingGuid0:g", "00000000_00000000"},
	{"Action0Animation0:s", "\"DefaultName\""},
	{"Action0Link:s", "\"DefaultName\""},
	{"Action0LinkState:d", "0"},
	{"Action0State:s", "\"DefaultName\""},
	{"Action0NPC:g", "00000000_00000000"},
	{"Action0Trigger:g", "00000000_00000000"},
	{"Action0Object:g", "00000000_00000000"},
	{"Action0Volume:g", "00000000_00000000"},
	{"Action0Facing:g", "00000000_00000000"},
	{"Action0NPCCount:d", "1"},
	{"Action0Health:d", "0"},
	{"Action0StringID:s", "\"DefaultName\""},
	{"Action0Scroll:d", "0"},
	{"Action0DelayTime:f", "0.000000"},
	{"Action0cinemaCount:d", "1"},
	{"Action0cinemaSelect:d", "0"},
	{"Action0cinema0Guid:g", "00000000_00000000"},
	{"Action0NPCGuid:g", "00000000_00000000"},
	{"Action0CinemaCount:d", "1"},
	{"Action0SelectionMethod:d", "0"},
	{"Action0Cinema0:g", "00000000_00000000"},
	{"Action0QuestID:s", "\"DefaultName\""},
	{"Action0Required:d", "0"},
	{"Action0IdleAnim:s", "\"DefaultName\""},
	{"Action0DoStateController:d", "0"},
	{"Action0DoRender:d", "0"},
	{"Action0Fadeout:d", "0"},
	{"Action0Color:dddd", "0 0 0 0"},
	{"Action0Duration:f", "0.000000"},
	{"Action0InstanceCount:d", "1"},
	{"Action0RigidInstance0:g", "00000000_00000000"},
	{"Action0AnimIndex:d", "0"},
	{"Action0Loops:d", "0"},
	{"Action0RopeCount:d", "1"},
	{"Action0RopeGuid0:g", "00000000_00000000"},
	{"Action0RopeLength0:f", "0.000000"},
	{"Action0Collides:d", "0"},
	{"Action0BilboCollides:d", "0"},
	{"Action0NPCCollides:d", "0"},
	{"Action0InvulnGuid:g", "00000000_00000000"},
	{"Action0InvulnOn:d", "0"},
	{"Action0MusicTrigger:g", "00000000_00000000"},
	{"Action0DoRootToPosition:d", "0"},
	{"Action0ResetRootPosition:d", "0"},
	{"Action0Enable:d", "0"},
	{"Action0MaterialName:s", "\"DefaultName\""},
	{"Action0AmbientAudioTrigger:g", "00000000_00000000"},
	{"Action0Amp:f", "0.000000"},
	{"Action0Time:f", "0.000000"},
	{"Action0RigidInstance:g", "00000000_00000000"},
	{"Action0Hidden:d", "0"},
	{"Action0DoRunAI:d", "0"},
	{"Action0DoRenderProp:d", "0"},
	{"Action0Hoistable:d", "0"},
};
