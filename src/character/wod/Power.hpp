#ifndef CHARACTER_WOD_POWER_HPP
#define CHARACTER_WOD_POWER_HPP
#include<character/BasicTrait.hpp>
namespace schizophrenia {
namespace wod {
class Power : public BasicTrait {
    public:
        Power ( void ) = default;
        Power ( const std::string& id, const std::string& name, const std::string& value );


    };

}
}

namespace YAML {
template<>
struct convert<schizophrenia::wod::Power> {
    static Node encode ( const schizophrenia::wod::Power& power ) {
        return static_cast<const schizophrenia::BasicTrait&> ( power ).encode();
        }

    static bool decode ( const Node& node, schizophrenia::wod::Power& power ) {
        return static_cast<schizophrenia::BasicTrait&> ( power ).decode ( node );
        }
    };
}

#endif
