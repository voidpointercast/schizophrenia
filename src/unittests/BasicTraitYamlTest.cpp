/*
 * BasicTraitYamlTest.cpp
 *
 *  Created on: Dec 7, 2012
 *      Author: voidpointercast
 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<character/BasicTrait.hpp>
#include<unittests/Unittest.hpp>
using namespace schizophrenia;
using namespace unittest;

const std::string expectedDataFile = "./data/testdata/BasicTraitYamlTest/expected.dat";

int main(void) {
	{
		beginTest("BasicTrait to YAML translation test");
		std::ifstream expectedFile{expectedDataFile.c_str()};
		if(! expectedFile) {
			endTest(false, "Cannot open expected.dat");
			return 1;
		}
		std::stringstream buffer;
		buffer << expectedFile.rdbuf();
		std::string expectedResult = buffer.str();
		BasicTrait trait{"TraitName","Value"};
		trait.Attributes.push_back(Attribute{"A1","V"});
		trait.Attributes.push_back(Attribute{"A2","V"});
		YAML::Emitter out;
		out <<  trait;
		endTest(std::string(out.c_str())+"\n" == expectedResult);

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


