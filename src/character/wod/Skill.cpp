#include<character/wod/Skill.hpp>

namespace schizophrenia {
namespace wod {
  
Skill::Skill ( const std::string& name, Skill::ValueType value ) : BasicTrait(name, boost::lexical_cast<std::string>(value)) {

    }
  
  
Skill::ConstSpecializationIterator Skill::begin ( void ) const {
    return Skill::ConstSpecializationIterator ( [] ( const Attribute& a ) -> bool { return a.getCategory() == "specialization"; }, this->Attributes.begin(), this->Attributes.end() );
    }

Skill::ConstSpecializationIterator Skill::end ( void ) const {
    return Skill::ConstSpecializationIterator ( [] ( const Attribute& a ) -> bool { return a.getCategory() == "specialization"; }, this->Attributes.end(), this->Attributes.end() );
    }

Skill::SpecializationIterator Skill::begin ( void ) {
    return Skill::SpecializationIterator ( [] ( const Attribute& a ) -> bool { return a.getCategory() == "specialization"; }, this->Attributes.begin(), this->Attributes.end() );
    }

Skill::SpecializationIterator Skill::end ( void ) {
    return Skill::SpecializationIterator ( [] ( const Attribute& a ) -> bool { return a.getCategory() == "specialization"; }, this->Attributes.end(), this->Attributes.end() );
    }
}
}
