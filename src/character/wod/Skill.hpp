#ifndef SCHIZOPHRENIA_CHARACTER_WOD_SKILL_HPP
#define SCHIZOPHRENIA_CHARACTER_WOD_SKILL_HPP
#include<boost/iterator/filter_iterator.hpp>
#include<character/BasicTrait.hpp>

namespace schizophrenia {
namespace wod { 
  class Skill : public BasicTrait {
  public:
    typedef unsigned short ValueType;
    typedef boost::filter_iterator<std::function<bool ( Attribute ) >,typename std::vector<Attribute>::const_iterator> ConstSpecializationIterator;
    typedef boost::filter_iterator<std::function<bool ( Attribute ) >,typename std::vector<Attribute>::iterator>       SpecializationIterator;
    
    Skill(const std::string& name, ValueType value);
    Skill(void)  = default;
    ~Skill(void) = default;
  
    ConstSpecializationIterator begin(void) const;
    ConstSpecializationIterator end(void)   const;
    
    SpecializationIterator begin(void);
    SpecializationIterator end(void);
  };
  
}
}

namespace YAML {
template<>
struct convert<schizophrenia::wod::Skill> {
    static Node encode ( const schizophrenia::wod::Skill& skill ) {
        return skill.encode();
        }

    static bool decode ( const Node& node, schizophrenia::wod::Skill& skill ) {
        return skill.decode ( node );
        }
    };
}


#endif