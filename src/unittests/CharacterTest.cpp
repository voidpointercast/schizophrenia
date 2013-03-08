#include<iostream>
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
	endTest(yaml.length() == 309);
	beginTest("YAML to Character test");
	std::stringstream stream{yaml};
	YAML::Parser parser;
	YAML::Node	 node;
	parser.Load(stream);
	bool validDocument 	= static_cast<bool>(parser);
	bool fetchableDoc		= parser.GetNextDocument(node);
	if(validDocument && fetchableDoc) {
		YAML::Emitter outCopy;
		Character copy;
		node.begin() >> copy;
		outCopy << copy;
		endTest(outCopy.c_str() == yaml,"Character and copy do not match");
	} else {
		if(!validDocument) {
			endTest(false,"Invalid document format");
		} else {
			endTest(false,"Invalid document");
		}
	}

	
	
	
	return 0;
}
