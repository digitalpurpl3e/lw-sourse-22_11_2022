#pragma once
inline const char* AimType[] =
{
	"Hitbox",
	"Nearest hitbox"
};

inline const char* LegitHitbox[] =
{
	"Head",
	"Neck",
	"Pelvis",
	"Stomach",
	"Lower chest",
	"Chest",
	"Upper chest"
};

inline const char* LegitSelection[] =
{
	"Near crosshair",
	"Lowest health",
	"Highest damage",
	"Lowest distance"
};

inline std::vector<const char*> antiaim_type =
{
	"Rage",
	"Legit"
};

inline std::vector<const char*> movement_type =
{
	"Stand",
	"Slow walk",
	"Move",
	"Air"
};

inline std::vector<const char*> LegitFov =
{
	"Static",
	"Dynamic"
};

inline std::vector<const char*> LegitSmooth =
{
	"Static",
	"Humanized"
};

inline std::vector<const char*> RCSType =
{
	"Always on",
	"On target"
};

inline std::vector<const char*> selection =
{
	"Cycle",
	"Near crosshair",
	"Lowest distance",
	"Lowest health",
	"Highest damage"
};

inline const char* bodyaimlevel[] =
{
	"Low",
	"Medium",
	"High"
};

inline const char* bodyaim[] =
{
	"In air",
	"On high velocity",
	"On lethal",
	"On double tap",
	"If unresolved",
	"Prefer"
};

inline const char* autostop_modifiers[] =
{
	"Between shots",
	"On lethal",
	"Visible",
	"Center",
	"Force accuracy",
	"Predictive"
};

inline const char* hitboxes[] =
{
	"Head",
	"Upper chest",
	"Chest",
	"Lower chest",
	"Stomach",
	"Pelvis",
	"Arms",
	"Legs",
	"Feet"
};

inline std::vector<const char*> pitch =
{
	"None",
	"Down",
	"Up",
	"Zero",
	"Random",
	"Jitter",
	"Fake down",
	"Fake up",
	"Fake jitter"
};

inline std::vector<const char*> yaw =
{
	"Static",
	"Jitter",
	"Spin"
};

inline std::vector<const char*> baseangle =
{
	"Local view",
	"At targets"
};

inline std::vector<const char*> desync =
{
	"None",
	"Static",
	"Jitter"
};

inline std::vector<const char*> lby_type =
{
	"Normal",
	"Opposite",
	"Sway"
};

inline const char* proj_combo[] =
{
	"Icon",
	"Text",
	"Box",
	"Glow"
};

inline const char* weaponplayer[] =
{
	"Icon",
	"Text"
};

inline const char* weaponesp[] =
{
	"Icon",
	"Text",
	"Box",
	"Distance",
	"Glow",
	"Ammo"
};

inline const char* hitmarkers[] =
{
	"Crosshair",
	"World"
};

inline const char* glowtarget[] =
{
	"Enemy",
	"Teammate",
	"Local"
};


inline std::vector<const char*> glowtype =
{
	"Standard",
	"Pulse",
	"Inner"
};

inline std::vector<const char*> local_chams_type =
{
	"Real",
	"Desync"
};

inline const char* chamsvisact[] =
{
	"Visible",
	"Invisible"
};

inline const char* chamsvis[] =
{
	"Visible"
};

inline std::vector<const char*> chamstype =
{
	"Regular",
	"Mettalic",
	"Flat",
	"Pulse",
	"Crystal",
	"Glass",
	"Circuit",
	"Golden",
	"Glow"
};

inline const char* flags[] =
{
	"Money",
	"Armor",
	"Defuse kit",
	"Scoped",
	"Fakeducking",
	"Vulnerable",
	"Delay",
	"Bomb carrier"
};

inline const char* removals[] =
{
	"Scope",
	"Zoom",
	"Smoke",
	"Flash",
	"Recoil",
	"Landing bob",
	"Postprocessing",
	"Fog"
};

inline const char* indicators[] =
{
	"Fake",
	"Desync side",
	"Choke",
	"Damage override",
	"Safe points",
	"Body aim",
	"Double tap",
	"Hide shots"
};

inline std::vector<const char*> skybox =
{
	"None",
	"Tibet",
	"Baggage",
	"Italy",
	"Aztec",
	"Vertigo",
	"Daylight",
	"Daylight 2",
	"Clouds",
	"Clouds 2",
	"Gray",
	"Clear",
	"Canals",
	"Cobblestone",
	"Assault",
	"Clouds dark",
	"Night",
	"Night 2",
	"Night flat",
	"Dusty",
	"Rainy",
	"Custom"
};

inline std::vector<const char*> mainwep =
{
	"None",
	"Auto",
	"AWP",
	"SSG 08"
};

inline std::vector<const char*> secwep =
{
	"None",
	"Dual Berettas",
	"Deagle/Revolver"
};

inline std::vector<const char*> strafes =
{
	"None",
	"Legit",
	"Directional",
	"Rage"
};

inline const char* events_output[] =
{
	"Console",
	"Chat"
};

inline const char* events[] =
{
	"Player hits",
	"Items",
	"Bomb"
};

inline const char* grenades[] =
{
	"Grenades",
	"Armor",
	"Taser",
	"Defuser"
};

inline std::vector<const char*> fakelags =
{
	"Static",
	"Random",
	"Dynamic",
	"Fluctuate"
};

inline const char* lagstrigger[] =
{
	"Slow walk",
	"Move",
	"Air",
	"Peek"
};

inline std::vector<const char*> sounds =
{
	"None",
	"Mettalic",
	"Cod",
	"Bubble",
	"Stapler",
	"Bell",
	"Flick"
};

inline std::vector<const char*> player_model_t =
{
	"None",
	"Enforcer",
	"Soldier",
	"Ground Rebel",
	"Maximus",
	"Osiris",
	"Slingshot",
	"Dragomir",
	"Blackwolf",
	"Prof. Shahmat",
	"Rezan The Ready",
	"Doctor Romanov",
	"Mr. Muhlik"
};

inline std::vector<const char*> player_model_ct =
{
	"None",
	"Seal Team 6",
	"3rd Commando",
	"Operator FBI",
	"Squadron Officer",
	"Markus Delrow",
	"Buckshot",
	"McCoy",
	"Commander Ricksaw",
	"Agent Ava"
};