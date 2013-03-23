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
    std::shared_ptr<Check<Character>> powercheck ( new PowerStatCheck ( *this ) );
    this->CharacterChecks.push_back ( powercheck );



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


YAML::Node WorldOfDarknessCharacter::encode ( void ) const {
    YAML::Node node = static_cast<const Character*> ( this )->encode();
    YAML::Node skills =     node["skills"];
    YAML::Node merits =     node["merits"];
    YAML::Node attributes = node["attributes"];
    std::for_each ( this->Skills.begin(),     this->Skills.end(),    [&] ( const wod::Skill& skill )->   void { skills.push_back ( skill );} );
    std::for_each ( this->Merits.begin(),     this->Merits.end(),    [&] ( const wod::Merit& merit )->   void { merits.push_back ( merit );} );
    std::for_each ( this->Attributes.begin(), this->Attributes.end(),[&] ( const wod::Attribute& attr )->void { attributes.push_back ( attr );} );
    return node;
    }

bool WorldOfDarknessCharacter::decode ( const YAML::Node& node ) {
    static_cast<Character*>(this)->decode(node);
    const YAML::Node skills =     node["skills"];
    const YAML::Node merits =     node["merits"];
    const YAML::Node attributes = node["attributes"];
    for(auto i=skills.begin(); i!=skills.end(); ++i) {
      this->Skills.push_back(i->as<wod::Skill>());
    }
    for(auto i=merits.begin(); i!=merits.end(); ++i) {
      this->Merits.push_back(i->as<wod::Merit>());
    }
    for(auto i=attributes.begin(); i!=attributes.end(); i++) {
        this->Attributes.push_back(i->as<wod::Attribute>());
    }
    return true;
    }


std::tuple<bool,std::string> WorldOfDarknessCharacter::setValue(const Skill& skill, const Skill::ValueType& value) {
  auto pos = std::find(this->Skills.begin(), this->Skills.end(),skill);
  if(pos == this->Skills.end()) {
    return std::make_tuple(false,"Could not set value of skill with id=" + skill.ID + ". Skill not found.");
  }
  std::string encValue = boost::lexical_cast<std::string>(value);
  auto check = this->setValueCheck(*pos,encValue);
  if(std::get<0>(check)) {
      pos->Value = encValue;
      return std::make_tuple(true,"");
  } else {
      return std::make_tuple(false,"Could not set value of skill with id=" + skill.ID + ". " + std::get<1>(check));
  }
}

std::tuple<bool,std::string> WorldOfDarknessCharacter::setValue(const Merit& merit, const Merit::ValueType& value) {
  auto pos = std::find(this->Merits.begin(), this->Merits.end(),merit);
  if(pos == this->Merits.end()) {
    return std::make_tuple(false,"Could not set value of skill with id=" + merit.ID + ". Skill not found.");
  }
  std::string encValue = boost::lexical_cast<std::string>(value);
  auto check = this->setValueCheck(*pos,encValue);
  if(std::get<0>(check)) {
      pos->Value = encValue;
      return std::make_tuple(true,"");
  } else {
      return std::make_tuple(false,"Could not set value of skill with id=" + merit.ID + ". " + std::get<1>(check));
  }
}

std::tuple<bool,std::string> WorldOfDarknessCharacter::setValue(const wod::Attribute& attr, const wod::Attribute::ValueType& value) {
  auto pos = std::find(this->Attributes.begin(), this->Attributes.end(),attr);
  if(pos == this->Attributes.end()) {
    return std::make_tuple(false,"Could not set value of skill with id=" + attr.ID + ". Skill not found.");
  }
  std::string encValue = boost::lexical_cast<std::string>(value);
  auto check = this->setValueCheck(*pos,encValue);
  if(std::get<0>(check)) {
      pos->Value = encValue;
      return std::make_tuple(true,"");
  } else {
      return std::make_tuple(false,"Could not set value of skill with id=" + attr.ID + ". " + std::get<1>(check));
  }
}

    
    
    



}
} /* namespace schizohrenia */
