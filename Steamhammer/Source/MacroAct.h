#pragma once

#include "Common.h"
#include "MacroCommand.h"

namespace UAlbertaBot
{

enum class MacroLocation
	{ Anywhere     // default location
	, Macro        // macro hatchery
	, Expo         // gas expansion hatchery
	, MinOnly      // any expansion hatchery (mineral-only or gas, whatever's next)
	, Hidden       // gas expansion hatchery far from both main bases
	, Main         // current main base
	, Natural      // "natural" first expansion base
	, Center       // middle of the map
	};

namespace MacroActs
{
    enum {Unit, Tech, Upgrade, Command, Default};
}

class MacroAct 
{
	size_t				_type;
    BWAPI::Race			_race;

	BWAPI::UnitType		_unitType;
	BWAPI::TechType		_techType;
	BWAPI::UpgradeType	_upgradeType;
	MacroCommand		_macroCommandType;

	MacroLocation		_macroLocation;

	MacroLocation		getMacroLocationFromString(std::string & s);

public:

	MacroAct();
    MacroAct(const std::string & name);
	MacroAct(BWAPI::UnitType t);
	MacroAct(BWAPI::UnitType t, MacroLocation loc);
	MacroAct(BWAPI::TechType t);
	MacroAct(BWAPI::UpgradeType t);
	MacroAct(MacroCommandType t);
	MacroAct(MacroCommandType t, int amount);

	bool    isUnit()		const;
	bool    isTech()		const;
	bool    isUpgrade()	    const;
	bool    isCommand()	    const;
	bool    isBuilding()	const;
	bool    isRefinery()	const;
	bool	isSupply()		const;
    
    const size_t & type() const;
    const BWAPI::Race & getRace() const;

    const BWAPI::UnitType & getUnitType() const;
    const BWAPI::TechType & getTechType() const;
    const BWAPI::UpgradeType & getUpgradeType() const;
	const MacroCommand getCommandType() const;
	const MacroLocation getMacroLocation() const;

	int supplyRequired() const;
	int mineralPrice()   const;
	int gasPrice()       const;

	BWAPI::UnitType whatBuilds() const;
	std::string getName() const;

	friend std::ostream& operator << (std::ostream& out, const MacroAct& m)
	{
		if (m.isUnit())
		{
			out << m.getUnitType();
			if (m.isBuilding() && m.hasReservedPosition())
				out << "@" << m.getReservedPosition();
		}
		else if (m.isTech())
			out << m.getTechType();
		else if (m.isUpgrade())
			out << m.getUpgradeType();
		else if (m.isCommand())
			out << m.getCommandType().getName();

		return out;
	};
};
}