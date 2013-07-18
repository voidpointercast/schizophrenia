#ifndef SCHIZOPHRENIA_CHARACTER_WOD_ATTRIBUTE_HPP
#define SCHIZOPHRENIA_CHARACTER_WOD_ATTRIBUTE_HPP
#include<character/BasicTrait.hpp>
namespace schizophrenia {
namespace wod {
class Attribute : public BasicTrait {
    public:
        typedef unsigned short ValueType;
        Attribute ( void ) = default;
        Attribute ( const std::string& name, const ValueType& value );
        Attribute ( const std::string& id, const std::string& name, const ValueType& value );
        Attribute ( const std::string& id, const std::string& name, const ValueType& value, const std::string& category );
        template<class InputIterator>
        Attribute ( const std::string& name, const ValueType& value, InputIterator begin, InputIterator end );
        template<class InputIterator>
        Attribute ( const std::string& id, const std::string& name, const ValueType& value, InputIterator begin, InputIterator end );



    };

template<class InputIterator>
wod::Attribute::Attribute ( const std::string& name, const Attribute::ValueType& value, InputIterator begin, InputIterator end )
    : BasicTrait ( name,boost::lexical_cast<std::string>(value),begin,end ) {

    }

template<class InputIterator>
wod::Attribute::Attribute ( const std::string& id, const std::string& name, const Attribute::ValueType& value, InputIterator begin, InputIterator end )
    : BasicTrait ( id,name,boost::lexical_cast<std::string>(value),begin,end ) {

    }





}
}

namespace YAML {
template<>
struct convert<schizophrenia::wod::Attribute> {
    static Node encode ( const schizophrenia::wod::Attribute& attr ) {
        return attr.encode();
        }

    static bool decode ( const Node& node, schizophrenia::wod::Attribute& attr ) {
        return attr.decode ( node );
        }
    };
}

#endif
