_killed = [-1, name (_this select 0)];
if (isPlayer (_this select 0)) then {
	_killed = [getPlayerUID (_this select 0), _killed select 1];
};

_killer = [-1, name (_this select 1)];
if (isPlayer (_this select 1)) then {
	_killer = [getPlayerUID (_this select 1), _killer select 1];
};

_suicide = false;
if ((_this select 0) == (_this select 1)) then {
	_suicide = true;
};

/*
	TODO: Fix TK detection
*/

_arr = [
	["type", "unit_killed"],
	["victim_uid", _killed select 0],
	["victim_name", _killed select 1],
	["victim_nid", netId (_this select 0)],
	//["victim_side", format["%1", side (_this select 0)]],
	["killer_uid", _killer select 0],
	["killer_name", _killer select 1],
	["killer_nid", netId (_this select 1)],
	["killer_side", format["%1", side (_this select 1)]],
	["suicide", _suicide]
];

_arr call xea_fnc_sendEvent;
