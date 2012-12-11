/*
 * BasicTraitYamlTest.cpp
 *
 *  Created on: Dec 7, 2012
 *      Author: voidpointercast
 */

#include<iostream>
#include<sstream>
#include<character/BasicTrait.hpp>
#include<unittests/Unittest.hpp>
using namespace schizohrenia;
using namespace unittest;

int main(void) {
	{
		beginTest("BasicTrait to YAML translation test");
		std::string expectedResult {"name: TraitName\nvalue: Value\nattributes:\n  - name: A1\n    value: V\n  - name: A2\n    value: V"};
		BasicTrait trait{"TraitName","Value"};
		trait.Attributes.push_back(Attribute{"A1","V"});
		trait.Attributes.push_back(Attribute{"A2","V"});
		YAML::Emitter out;
		out << trait;
		endTest(out.c_str() == expectedResult);

	}
	{
		beginTest("YAML to BasicTrait translation test");
		BasicTrait trait{"TraitName","Value"};
		trait.Attributes.push_back(Attribute{"A1","V"});
		trait.Attributes.push_back(Attribute{"A2","V"});
		YAML::Emitter out;
		out << YAML::BeginSeq << trait << YAML::EndSeq;
		std::stringstream stream{out.c_str()};
		BasicTrait trait2;
		YAML::Node node;
		YAML::Parser parser;
		parser.Load(stream);
		if(!std::cerr << parser.operator bool()) {
			endTest(false, "Parser not ready");
		}
		if(! parser.GetNextDocument(node)) {
			endTest(false,"No document found");
		}
		node.begin() >> trait2;
		endTest(trait2 == trait);
	}
}


