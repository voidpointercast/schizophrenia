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


int main ( void ) {
        {
        beginTest ( "Bidirectional BasicTrait to YAML translation test" );
        std::stringstream buffer;
        BasicTrait original {"TraitName","Value"};
        BasicTrait copy;
        original.Attributes.push_back ( Attribute {"A1","V"} );
        original.Attributes.push_back ( Attribute {"A2","V"} );
        YAML::Emitter out;
        copy.decode(original.encode());
        endTest (original == copy);
        }
    }


