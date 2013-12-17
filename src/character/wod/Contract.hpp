#ifndef CHARACTER_WOD_POWER_HPP
#define CHARACTER_WOD_POWER_HPP
#include<character/BasicTrait.hpp>
namespace schizophrenia {
namespace wod {


class Clause : public BasicTrait {
public:
  Clause (void) = default;
  Clause (const std::string& id, const std::string& name, const std::string& value);
  
  YAML::Node encode(void) const;
  bool       decode(const YAML::Node& node);
  
private:
  std::string Effect;
  std::string Roll;
  std::string Cost;
  std::string Catch;
};


class Contract : public BasicTrait {
public:
    Power ( void ) = default;
    Power ( const std::string& id, const std::string& name, const std::string& value );

    




};

}
}

namespace YAML {

template<>
struct convert<schizophrenia::wod::PowerSpecification> {
  static Node encode (const schizophrenia::wod::Clause& clause) {
      return clause.encode();
  }
  
  static bool decode (const Node& node, schizophrenia::wod::Clause& clause) {
      return clause.decode(node);
  }
  
};
  
template<>
struct convert<schizophrenia::wod::Power> {
    static Node encode ( const schizophrenia::wod::Contract& contract ) {
        return contract.encode();
    }

    static bool decode ( const Node& node, schizophrenia::wod::Contract& contract ) {
        return contract.decode(node);
    }
};
}

#endif
