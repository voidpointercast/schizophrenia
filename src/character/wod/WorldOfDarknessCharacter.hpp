/*
 * WorldOfDarknessCharacter.hpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#ifndef WORLDOFDARKNESSCHARACTER_HPP_
#define WORLDOFDARKNESSCHARACTER_HPP_

#include<type_traits>
#include<character/Character.hpp>
#include<character/wod/Merit.hpp>
#include<character/wod/Skill.hpp>
#include<character/wod/Attribute.hpp>
#include<character/wod/Characteristic.hpp>
#include<character/wod/Species.hpp>

namespace schizophrenia {
namespace wod {
class WorldOfDarknessCharacter: public schizophrenia::Character {
    public:
        typedef typename std::vector<wod::Attribute>::const_iterator            ConstAttributeIterator;
        typedef typename std::vector<wod::Merit>::const_iterator                ConstMeritIterator;
        typedef typename std::vector<wod::Skill>::const_iterator                ConstSkillIterator;
        typedef typename std::vector<schizophrenia::BasicTrait>::const_iterator BasicTraitIterator;
        typedef typename std::vector<wod::Characteristic>::const_iterator       ConstCharacteristicIterator;


        WorldOfDarknessCharacter ( void );
        virtual ~WorldOfDarknessCharacter();

        void addMerit ( const wod::Merit& merit );
        void addAttribute ( const wod::Attribute& attribute );
        void addSkill ( const wod::Skill& skill );
        void addCharacteristic( const wod::Characteristic& c);

        std::tuple<bool,std::string> setValue ( const Skill& skill,           const typename Skill::ValueType& value );
        std::tuple<bool,std::string> setValue ( const Merit& skill,           const typename Merit::ValueType& value );
        std::tuple<bool,std::string> setValue ( const wod::Attribute& skill,  const typename wod::Attribute::ValueType& value );
        std::tuple<bool,std::string> setValue ( const wod::Characteristic& c, const typename wod::Characteristic::ValueType& value);

        template<class TraitType>
        std::tuple<bool,std::string> setValueByID ( const std::string& id, const typename TraitType::ValueType& value );

        void removeMerit ( const wod::Merit& merit );
        void removeSkill ( const wod::Skill& skill );

        ConstAttributeIterator beginAttributes ( void ) const;
        ConstAttributeIterator endAttributes ( void ) const;
        ConstMeritIterator     beginMerits ( void ) const;
        ConstMeritIterator     endMerits ( void ) const;
        ConstSkillIterator     beginSkills ( void ) const;
        ConstSkillIterator     endSkills ( void ) const;
        ConstCharacteristicIterator beginCharacteristics (void) const;
        ConstCharacteristicIterator endCharacteristics (void) const;

        template<class Category>
        typename std::vector<Category>::const_iterator beginCategory() const;

        template<class Category>
        typename std::vector<Category>::const_iterator endCategory() const;


        YAML::Node encode ( void ) const;
        bool decode ( const YAML::Node& node );


    protected:
        template<class Container>
        std::tuple<bool,std::string> setGenericValue ( const std::string& id, Container& collection, const typename Container::value_type::ValueType& value );

	Species                          Type;
        std::vector<wod::Attribute>      Attributes;
        std::vector<wod::Merit>          Merits;
        std::vector<wod::Skill>          Skills;
        std::vector<wod::Characteristic> Characteristics;

    };

template<class Container>
std::tuple<bool,std::string> WorldOfDarknessCharacter::setGenericValue ( const std::string& id, Container& collection, const typename Container::value_type::ValueType& value ) {
    auto trait = std::find_if ( std::begin ( collection ), std::end ( collection ), [&] ( typename Container::value_type& trait ) -> bool { return trait.ID == id; } );
    if ( trait == std::end ( collection ) ) {
        return std::make_tuple ( false, "trait with id=" + id + " not found" );
        }
    std::string encValue = boost::lexical_cast<std::string> ( value );
    auto check = this->setValueCheck ( *trait,encValue );
    if ( ! std::get<0> ( check ) ) {
        return check;
        }
    trait->Value = encValue;
    return std::make_tuple ( true,"Success" );
    }



template<class TraitType>
std::tuple<bool,std::string> WorldOfDarknessCharacter::setValueByID ( const std::string& id, const typename TraitType::ValueType& value ) {
    //static_assert ( false,"Unknown TraitType in setValueByID" );
    throw(std::runtime_error("WorldOfDarknessCharacter::setValueByID: unknown TraitType"));
    return std::make_tuple ( false,"Unknown TraitType" );
    }


template<>
inline std::tuple<bool,std::string> WorldOfDarknessCharacter::setValueByID<Skill> ( const std::string& id, const Skill::ValueType& value ) {
    return this->setGenericValue ( id,this->Skills,value );
    }

template<>
inline std::tuple<bool,std::string> WorldOfDarknessCharacter::setValueByID<Merit> ( const std::string& id, const Merit::ValueType& value ) {
    return this->setGenericValue ( id,this->Merits,value );
    }

template<>
inline std::tuple<bool,std::string> WorldOfDarknessCharacter::setValueByID<wod::Attribute> ( const std::string& id, const wod::Attribute::ValueType& value ) {
    return this->setGenericValue ( id,this->Attributes,value );
    }

template<>
inline std::tuple<bool,std::string> WorldOfDarknessCharacter::setValueByID<wod::Characteristic> ( const std::string& id, const wod::Characteristic::ValueType& value ) {
    return this->setGenericValue ( id,this->Characteristics,value );
    }

   
    

template<class Category>
typename std::vector<Category>::const_iterator WorldOfDarknessCharacter::beginCategory() const {
  throw(std::runtime_error("WorldOfDarknessCharacter::beginCategory: unknown Category"));
  return std::vector<Category>().begin();
    }

template<class Category>
typename std::vector<Category>::const_iterator WorldOfDarknessCharacter::endCategory() const {
  throw(std::runtime_error("WorldOfDarknessCharacter::endCategory: unknown Category"));
  return std::vector<Category>().end();
    }

template<>
inline typename std::vector<Skill>::const_iterator WorldOfDarknessCharacter::beginCategory<Skill>() const {
  return this->Skills.begin();
    }

template<>
inline typename std::vector<Skill>::const_iterator WorldOfDarknessCharacter::endCategory<Skill>() const {
  return this->Skills.end();
    }

template<>
inline typename std::vector<wod::Attribute>::const_iterator WorldOfDarknessCharacter::beginCategory<wod::Attribute>() const {
  return this->Attributes.begin();
    }

template<>
inline typename std::vector<wod::Attribute>::const_iterator WorldOfDarknessCharacter::endCategory<wod::Attribute>() const {
  return this->Attributes.end();
    }

template<>
inline typename std::vector<Merit>::const_iterator WorldOfDarknessCharacter::beginCategory<Merit>() const {
  return this->Merits.begin();
    }

template<>
inline typename std::vector<Merit>::const_iterator WorldOfDarknessCharacter::endCategory<Merit>() const {
  return this->Merits.end();
    }

template<>
inline typename std::vector<Characteristic>::const_iterator WorldOfDarknessCharacter::beginCategory<Characteristic>() const {
  return this->Characteristics.begin();
    }

template<>
inline typename std::vector<Characteristic>::const_iterator WorldOfDarknessCharacter::endCategory<Characteristic>() const {
  return this->Characteristics.end();
    }

}
}

namespace YAML {
template<>
struct convert<schizophrenia::wod::WorldOfDarknessCharacter> {
    static Node encode ( const schizophrenia::wod::WorldOfDarknessCharacter& character ) {
        return character.encode();
        }

    static bool decode ( const Node& node, schizophrenia::wod::WorldOfDarknessCharacter& character ) {
        return character.decode ( node );
        }
    };
}


#endif
