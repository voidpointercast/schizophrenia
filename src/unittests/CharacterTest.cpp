#include<stdexcept>
#include<tuple>
#include<sstream>
#include<character/Character.hpp>
#include<unittests/Unittest.hpp>
using namespace schizohrenia;
using namespace unittest;

int main(void) {
	beginTest("Character default constructor test");
	Character testchar;
	endTest(true);
	beginTest("Character add Trait test");
	testchar.addTrait(BasicTrait("Wits","4"));
	testchar.addTrait(BasicTrait("Strength","5"));
	auto trait = testchar.getTraits().back();
	endTest(trait.Value == "5" && trait.Name == "Strength");
	beginTest("Character to YAML test");
	testchar.addAttribute(testchar.getTraits().back(),Attribute("Bonus","1"));
	YAML::Emitter out;
	out << testchar;
	const std::string yaml = out.c_str();
	const std::string expectedAttrString = "- BasicTraits:\n    - name: Wits\n      value: 4\n      attributes:\n        []\n    - name: Strength\n      value: 5\n      attributes:\n        - name: Bonus\n          value: 1\n...";
	
	bool attrTestResult		= yaml.find(expectedAttrString) != std::string::npos;
	bool headerTestResult	= yaml.at(0) == '-' && yaml.length() >= 175;
	endTest(attrTestResult && headerTestResult);
	return 0;
}
