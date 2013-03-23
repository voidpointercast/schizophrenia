#include<stdexcept>
#include<tuple>
#include<character/wod/WorldOfDarknessCharacter.hpp>
#include<unittests/Unittest.hpp>
using namespace schizophrenia;
using namespace schizophrenia::wod;
using namespace unittest;

int main ( void ) {
    beginTest ( "WorldOfDarknessCharacter default constructor test" );
    WorldOfDarknessCharacter testchar;
    endTest ( true );
    beginTest ( "WorldOfDarknessCharacter add Trait test" );
    testchar.addTrait ( BasicTrait ( "Strength","5" ) );
    auto trait = testchar.getTraits().back();
    endTest ( trait.Value == "5" && trait.Name == "Strength" );
    beginTest ( "PowerStatCheck raise value reject test" );
    endTest ( ! std::get<0> ( static_cast<Character>(testchar).setValue ( trait,"6" ) ) );
    beginTest ( "PowerStatCheck add trait reject test" );
    endTest ( ! std::get<0> ( testchar.addTrait ( BasicTrait ( "Dexterity","6" ) ) ) );
    beginTest ( "PowerStatCheck add second powerstat reject test" );
    testchar.addTrait ( BasicTrait ( "powerstat","4" ) );
    endTest ( ! std::get<0> ( testchar.addTrait ( BasicTrait ( "powerstat","5" ) ) ) );
    beginTest ( "setWODValue<Skill> test on nonexisting skill" );
    endTest ( !std::get<0> ( testchar.setValue ( Skill ( "nonexisting",0 ),5 )),"could set value of nonexisting skill" );
              beginTest ( "addSkill test" );
              Skill skill ( "skill",5u );
              testchar.addSkill ( skill );
              endTest ( true );
              beginTest ( "setWODValue<Skill> test" );
    if ( !std::get<0> ( testchar.setValue ( skill,4 ) ) ) {
    endTest ( false );
        }
    auto search = std::find ( testchar.beginSkills(),testchar.endSkills(),skill );
    if ( search == testchar.endSkills() ) {
    endTest ( false,"Could not find skill" );
        }
    else {
        endTest ( search->Value == "4","value mismatch" );
        }
    return 0;
    }
