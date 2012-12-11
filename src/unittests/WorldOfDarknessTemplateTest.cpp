#include<stdexcept>
#include<tuple>
#include<character/wod/WorldOfDarknessCharacter.hpp>
#include<unittests/Unittest.hpp>
using namespace schizohrenia;
using namespace unittest;

int main(void) {
	beginTest("WorldOfDarknessCharacter default constructor test");
	WorldOfDarknessCharacter testchar;
	endTest(true);
	beginTest("WorldOfDarknessCharacter add Trait test");
	testchar.addTrait(BasicTrait("Strength","5"));
	auto trait = testchar.getTraits().back();
	endTest(trait.Value == "5" && trait.Name == "Strength");
	beginTest("PowerStatCheck raise value reject test");
	endTest(! std::get<0>(testchar.setValue(trait,"6")));
	beginTest("PowerStatCheck add trait reject test");
	endTest(! std::get<0>(testchar.addTrait(BasicTrait("Dexterity","6"))));
	beginTest("PowerStatCheck add second powerstat reject test");
	testchar.addTrait(BasicTrait("powerstat","4"));
	endTest(! std::get<0>(testchar.addTrait(BasicTrait("powerstat","5"))));
	return 0;
}
