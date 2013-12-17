#ifndef CHARACTER_WOD_ADVANTAGE_HPP
#define CHARACTER_WOD_ADVANTAGE_HPP
#include <character/BasicTrait.hpp>

namespace schizophrenia {
namespace wod {

class Advantage : public BasicTrait {
public:
   typedef unsigned short ValueType;
    static const std::string Category;

    Advantage ( void ) = default;

    virtual ~Advantage(void);

    Advantage (const std::string& id, const std::string& name, const std::string& value );

    bool operator==(const Advantage& other) const;

    bool IsDisadvantage;
    
    YAML::Node encode(void) const;
    
    bool decode(const YAML::Node& node);


};


}
}

namespace YAML {
template<>
struct convert<schizophrenia::wod::Advantage> {
    static Node encode ( const schizophrenia::wod::Advantage& advantage ) {
        return advantage.encode();
    }

    static bool decode ( const Node& node, schizophrenia::wod::Advantage& advantage ) {
        return advantage.decode ( node );
    }
};
}


#endif
