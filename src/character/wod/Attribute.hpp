#ifndef SCHIZOPHRENIA_CHARACTER_WOD_ATTRIBUTE_HPP
#define SCHIZOPHRENIA_CHARACTER_WOD_ATTRIBUTE_HPP
#include<character/BasicTrait.hpp>
namespace schizophrenia {
namespace wod {
class Attribute : public BasicTrait {

    };
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
