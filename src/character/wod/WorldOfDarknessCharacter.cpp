/*
 * WorldOfDarknessCharacter.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */


#include "WorldOfDarknessCharacter.hpp"
#include<character/wod/checks/PowerStatCheck.hpp>

namespace schizohrenia {

WorldOfDarknessCharacter::WorldOfDarknessCharacter(void)
: Character("whitewolf.nwod.vampire"){
	std::shared_ptr<Check<Character>> powercheck(new PowerStatCheck(*this));
	this->CharacterChecks.push_back(powercheck);
}

WorldOfDarknessCharacter::~WorldOfDarknessCharacter() {
	// TODO Auto-generated destructor stub
}

} /* namespace schizohrenia */
