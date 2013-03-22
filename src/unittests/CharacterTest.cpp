#include<iostream>
#include<stdexcept>
#include<tuple>
#include<sstream>
#include<character/Character.hpp>
#include<unittests/Unittest.hpp>
using namespace schizophrenia;
using namespace unittest;

int main ( void ) {
    beginTest ( "Character default constructor test" );
    Character original;
    endTest ( true );
    beginTest ( "Character add Trait test" );
    original.addTrait ( BasicTrait ( "Wits","4" ) );
    original.addTrait ( BasicTrait ( "Strength","5" ) );
    auto trait = original.getTraits().back();
    endTest ( trait.Value == "5" && trait.Name == "Strength" );
    beginTest ( "Bidirectional Character to YAML test" );
    original.addAttribute ( original.getTraits().back(),Attribute ( "Bonus","1" ) );
    Character copy;
    copy.decode ( original.encode() );
    endTest ( copy == original,"Character and copy do not match" );
    return 0;
    }
