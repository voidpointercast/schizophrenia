/*
 * WorldOfDarknessCharacter.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */


#include "WorldOfDarknessCharacter.hpp"
#include<character/wod/checks/PowerStatCheck.hpp>
#include <serialization/yaml.hpp>

namespace schizophrenia {
namespace wod {
WorldOfDarknessCharacter::WorldOfDarknessCharacter ( void )
    : Character ( "whitewolf.nwod.human" ) {
}

WorldOfDarknessCharacter::~WorldOfDarknessCharacter() {
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

WorldOfDarknessCharacter::ConstAdvantageIterator WorldOfDarknessCharacter::beginAdvantages(void) const
{
    return this->Advantages.begin();
}

WorldOfDarknessCharacter::ConstAdvantageIterator WorldOfDarknessCharacter::endAdvantages(void) const
{
    return this->Advantages.end();
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

void WorldOfDarknessCharacter::addAdvantage(const Advantage& adv) {
  this->Advantages.push_back(adv);
}

void WorldOfDarknessCharacter::removeMerit(const Merit& merit)
{
  auto i = std::find(this->Merits.begin(),this->Merits.end(),merit);
  if(i != this->Merits.end()) {
    this->Merits.erase(i);
  }
}



YAML::Node WorldOfDarknessCharacter::encode ( void ) const {
    YAML::Node node = Character::encode();
    archive::encodeCategory(node["skills"],this->Skills);
    archive::encodeCategory(node["merits"],this->Merits);
    archive::encodeCategory(node["attributes"],this->Attributes);
    archive::encodeCategory(node["characteristics"],this->Characteristics);
    archive::encodeCategory(node["advantages"],this->Advantages);
    YAML::Node species = node["species"];
    species = this->Type.encode();
    return node;
}

bool WorldOfDarknessCharacter::decode ( const YAML::Node& node ) {
    Character::decode(node);
    archive::decodeCategory(node["skills"],this->Skills);
    archive::decodeCategory(node["merits"],this->Merits);
    archive::decodeCategory(node["attributes"],this->Attributes);
    archive::decodeCategory(node["characteristics"],this->Characteristics);   
    archive::decodeCategory(node["advantages"],this->Advantages);
    this->Type.decode(node["species"]);
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
