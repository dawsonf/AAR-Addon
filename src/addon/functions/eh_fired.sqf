_unit = [-1, "AI"];
if (isPlayer (_this select 0)) then {
	_unit = [getPlayerUID (_this select 0), name (_this select 0)];
};

_arr = [
	["type", "weapon_fired"],
	["weapon", _this select 1],
	["ammo", _this select 4],
	["id", _unit select 0],
	["name", _unit select 1]
];

_arr call xea_fnc_event;