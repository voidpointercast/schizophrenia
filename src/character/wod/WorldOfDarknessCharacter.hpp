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

namespace schizophrenia {
namespace wod {
class WorldOfDarknessCharacter: public schizophrenia::Character {
    public:
        typedef typename std::vector<wod::Attribute>::const_iterator ConstAttributeIterator;
        typedef typename std::vector<wod::Merit>::const_iterator     ConstMeritIterator;
        typedef typename std::vector<wod::Skill>::const_iterator     ConstSkillIterator;

        WorldOfDarknessCharacter ( void );
        virtual ~WorldOfDarknessCharacter();

        void addMerit ( const wod::Merit& merit );
        void addSkill ( const wod::Skill& skill );
        
        std::tuple<bool,std::string> setValue(const Skill& skill,          const typename Skill::ValueType& value);
        std::tuple<bool,std::string> setValue(const Merit& skill,          const typename Merit::ValueType& value);
        std::tuple<bool,std::string> setValue(const wod::Attribute& skill, const typename wod::Attribute::ValueType& value);

        void removeMerit ( const wod::Merit& merit );
        void removeMerit ( const wod::Skill& skill );

        ConstAttributeIterator beginAttributes ( void ) const;
        ConstAttributeIterator endAttributes ( void ) const;
        ConstMeritIterator     beginMerits ( void ) const;
        ConstMeritIterator     endMerits ( void ) const;
        ConstSkillIterator     beginSkills ( void ) const;
        ConstSkillIterator     endSkills ( void ) const;

        YAML::Node encode ( void ) const;
        bool decode ( const YAML::Node& node );


    protected:



        std::vector<wod::Attribute> Attributes;
        std::vector<wod::Merit>     Merits;
        std::vector<wod::Skill>     Skills;


    };




}
}
#endif
