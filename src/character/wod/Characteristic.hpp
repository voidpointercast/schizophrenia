#include <character/BasicTrait.hpp>

namespace schizophrenia {
namespace wod {


class Characteristic : public BasicTrait {
public:
        Characteristic (void) = default;
        Characteristic ( const std::string& name, const std::string& value );
        Characteristic ( const std::string& id, const std::string& name, const std::string& value );

    };


}
}

namespace YAML {
template<>
struct convert<schizophrenia::wod::Characteristic> {
    static Node encode ( const schizophrenia::wod::Characteristic& c ) {
        return static_cast<const schizophrenia::BasicTrait&> ( c ).encode();
        }

    static bool decode ( const Node& node, schizophrenia::wod::Characteristic& c ) {
        return static_cast<schizophrenia::BasicTrait&> ( c ).decode ( node );
        }
    };
}
