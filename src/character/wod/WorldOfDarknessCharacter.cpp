/*
 * WorldOfDarknessCharacter.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */


#include "WorldOfDarknessCharacter.hpp"
#include<character/wod/checks/PowerStatCheck.hpp>

namespace schizophrenia {
namespace wod {
WorldOfDarknessCharacter::WorldOfDarknessCharacter ( void )
    : Character ( "whitewolf.nwod.vampire" ) {
/*    std::shared_ptr<Check<Character>> powercheck ( new PowerStatCheck ( *this ) );
    this->CharacterChecks.push_back ( powercheck );*/



    }

WorldOfDarknessCharacter::~WorldOfDarknessCharacter() {
    // TODO Auto-generated destructor stub
    }

WorldOfDarknessCharacter::ConstAttributeIterator WorldOfDarknessCharacter::beginAttributes ( void ) const {
    return this->Attributes.begin();
    }

WorldOfDarknessCharacter::ConstAttributeIterator WorldOfDarknessCharacter::endAttributes ( void ) const {
    return this->Attributes.end();
    }

WorldOfDarknessCharacter::ConstMeritIterator WorldOfDarknessCharacter::beginMerits ( void ) const {
    return this->Merits.begin();
    }

WorldOfDarknessCharacter::ConstMeritIterator WorldOfDarknessCharacter::endMerits ( void ) const {
    return this->Merits.end();
    }

WorldOfDarknessCharacter::ConstSkillIterator WorldOfDarknessCharacter::beginSkills ( void ) const {
    return this->Skills.begin();
    }

WorldOfDarknessCharacter::ConstSkillIterator WorldOfDarknessCharacter::endSkills ( void ) const {
    return this->Skills.end();
    }

WorldOfDarknessCharacter::ConstCharacteristicIterator WorldOfDarknessCharacter::beginCharacteristics ( void ) const {
    return this->Characteristics.begin();
    }
    
WorldOfDarknessCharacter::ConstCharacteristicIterator WorldOfDarknessCharacter::endCharacteristics ( void ) const {
    return this->Characteristics.end();
    }

WorldOfDarknessCharacter::ConstPowerIterator WorldOfDarknessCharacter::beginPowers ( void ) const {
    return this->Powers.begin();
    }
    
WorldOfDarknessCharacter::ConstPowerIterator WorldOfDarknessCharacter::endPowers ( void ) const {
    return this->Powers.end();
    }
        
    
    
  
void WorldOfDarknessCharacter::addMerit ( const Merit& merit ) {
    auto check = this->addTraitCheck ( merit );
    if ( ! std::get<0> ( check ) ) {
        throw ( std::runtime_error ( "Could not add merit to character: " + std::get<1> ( check ) ) );
        }
    this->Merits.push_back ( merit );
    }

void WorldOfDarknessCharacter::addSkill ( const Skill& skill ) {
    auto check = this->addTraitCheck ( skill );
    if ( ! std::get<0> ( check ) ) {
        throw ( std::runtime_error ( "Could not add skill to character: " + std::get<1> ( check ) ) );
        }
    this->Skills.push_back ( skill );
    }

void WorldOfDarknessCharacter::addAttribute ( const wod::Attribute& attribute ) {
    auto check = this->addTraitCheck ( attribute );
    if ( ! std::get<0> ( check ) ) {
        throw ( std::runtime_error ( "Could not add attribute to character: " + std::get<1> ( check ) ) );
        }
    this->Attributes.push_back ( attribute );
    }

void WorldOfDarknessCharacter::addCharacteristic ( const Characteristic& c ) {
    auto check = this->addTraitCheck(c);
    if( ! std::get<0> (check)) {
        throw (std::runtime_error ("Could not add characteristic to character: " + std::get<1>(check)));
    }
    this->Characteristics.push_back(c);
    }

void WorldOfDarknessCharacter::addPower ( const Power& power ) {
    auto check = this->addTraitCheck(power);
    if( ! std::get<0> (check)) {
        throw (std::runtime_error ("Could not add power to character: " + std::get<1>(check)));
    }
    this->Powers.push_back(power);
    }
    
    
    
    

YAML::Node WorldOfDarknessCharacter::encode ( void ) const {
    YAML::Node node = Character::encode();
    YAML::Node skills =     node["skills"];
    std::for_each ( this->Skills.begin(),     this->Skills.end(),    [&] ( const wod::Skill& skill )->   void { skills.push_back ( skill );} );
    YAML::Node merits =     node["merits"];
    std::for_each ( this->Merits.begin(),     this->Merits.end(),    [&] ( const wod::Merit& merit )->   void { merits.push_back ( merit );} );
    YAML::Node attributes = node["attributes"];
    std::for_each ( this->Attributes.begin(), this->Attributes.end(),[&] ( const wod::Attribute& attr )->void { attributes.push_back ( attr );} );
    YAML::Node info = node["characteristics"];
    std::for_each ( this->Characteristics.begin(), this->Characteristics.end(),[&] ( const wod::Characteristic& c )->void { info.push_back (c );} );
    return node;
    }

bool WorldOfDarknessCharacter::decode ( const YAML::Node& node ) {
    Character::decode(node);
    const YAML::Node skills =     node["skills"];
    const YAML::Node merits =     node["merits"];
    const YAML::Node attributes = node["attributes"];
    const YAML::Node info       = node["characteristics"];
    this->Skills.clear();
    for ( auto i=skills.begin(); i!=skills.end(); ++i ) {
        this->Skills.push_back ( i->as<wod::Skill>() );
        }
    this->Merits.clear();
    for ( auto i=merits.begin(); i!=merits.end(); ++i ) {
        this->Merits.push_back ( i->as<wod::Merit>() );
        }
    this->Attributes.clear();
    for ( auto i=attributes.begin(); i!=attributes.end(); ++i ) {
        this->Attributes.push_back ( i->as<wod::Attribute>() );
        }
    this->Characteristics.clear();
    for( auto i=info.begin(); i != info.end(); ++i) {
        this->Characteristics.push_back(i->as<wod::Characteristic>());
    }
    return true;
    }


std::tuple<bool,std::string> WorldOfDarknessCharacter::setValue ( const Skill& skill, const Skill::ValueType& value ) {
    auto pos = std::find ( this->Skills.begin(), this->Skills.end(),skill );
    if ( pos == this->Skills.end() ) {
        return std::make_tuple ( false,"Could not set value of skill with id=" + skill.ID + ". Skill not found." );
        }
    std::string encValue = boost::lexical_cast<std::string> ( value );
    auto check = this->setValueCheck ( *pos,encValue );
    if ( std::get<0> ( check ) ) {
        pos->Value = encValue;
        return std::make_tuple ( true,"" );
        }
    else {
        return std::make_tuple ( false,"Could not set value of skill with id=" + skill.ID + ". " + std::get<1> ( check ) );
        }
    }

std::tuple<bool,std::string> WorldOfDarknessCharacter::setValue ( const Merit& merit, const Merit::ValueType& value ) {
    auto pos = std::find ( this->Merits.begin(), this->Merits.end(),merit );
    if ( pos == this->Merits.end() ) {
        return std::make_tuple ( false,"Could not set value of merit with id=" + merit.ID + ". Merit not found." );
        }
    std::string encValue = boost::lexical_cast<std::string> ( value );
    auto check = this->setValueCheck ( *pos,encValue );
    if ( std::get<0> ( check ) ) {
        pos->Value = encValue;
        return std::make_tuple ( true,"" );
        }
    else {
        return std::make_tuple ( false,"Could not set value of merit with id=" + merit.ID + ". " + std::get<1> ( check ) );
        }
    }

std::tuple<bool,std::string> WorldOfDarknessCharacter::setValue ( const wod::Attribute& attr, const wod::Attribute::ValueType& value ) {
    auto pos = std::find ( this->Attributes.begin(), this->Attributes.end(),attr );
    if ( pos == this->Attributes.end() ) {
        return std::make_tuple ( false,"Could not set value of attribute with id=" + attr.ID + ". Attribute not found." );
        }
    std::string encValue = boost::lexical_cast<std::string> ( value );
    auto check = this->setValueCheck ( *pos,encValue );
    if ( std::get<0> ( check ) ) {
        pos->Value = encValue;
        return std::make_tuple ( true,"" );
        }
    else {
        return std::make_tuple ( false,"Could not set value of attribute with id=" + attr.ID + ". " + std::get<1> ( check ) );
        }
    }

std::tuple<bool,std::string> WorldOfDarknessCharacter::setValue ( const wod::Characteristic& c, const wod::Characteristic::ValueType& value ) {
    auto pos = std::find ( this->Characteristics.begin(), this->Characteristics.end(),c );
    if ( pos == this->Characteristics.end() ) {
        return std::make_tuple ( false,"Could not set value of characteristic with id=" + c.ID + ". Characteristic not found." );
        }
    std::string encValue = boost::lexical_cast<std::string> ( value );
    auto check = this->setValueCheck ( *pos,encValue );
    if ( std::get<0> ( check ) ) {
        pos->Value = encValue;
        return std::make_tuple ( true,"" );
        }
    else {
        return std::make_tuple ( false,"Could not set value of characteristic with id=" + c.ID + ". " + std::get<1> ( check ) );
        }
    }

    

//SPECIALISATIONS




}
} /* namespace schizohrenia */
