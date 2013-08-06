#ifndef CHARACTER_WOD_CONTRACT_HPP
#define CHARACTER_WOD_CONTRACT_HPP
#include<vector>
#include<character/BasicTrait.hpp>
namespace schizophrenia {
namespace wod {
namespace lost {


class Clause : public BasicTrait {
public:
  static const std::string Category;
  
  Clause (void) = default;
  Clause (const std::string& id, const std::string& name, const std::string& value);
  
  
  YAML::Node encode(void) const;
  bool       decode(const YAML::Node& node);
  
  std::string Effect;
  std::string Roll;
  std::string Cost;
  std::string Catch;
};


class Contract : public BasicTrait {
public:
    typedef std::vector<Clause>::const_iterator ConstClauseIterator;
    typedef unsigned short ValueType;
    
    static const std::string Category;
    
    bool operator==(const Contract& other) const;
  
    Contract( void ) = default;
    Contract( const std::string& id, const std::string& name, const std::string& value );

    ConstClauseIterator begin(void) const;
    ConstClauseIterator end(void) const;
    
    YAML::Node encode(void) const;
    bool       decode(const YAML::Node& node);
    
protected:
    std::vector<Clause> Clauses;

};

}
}
}

namespace YAML {

template<>
struct convert<schizophrenia::wod::lost::Clause> {
  static Node encode (const schizophrenia::wod::lost::Clause& clause) {
      return clause.encode();
  }
  
  static bool decode (const Node& node, schizophrenia::wod::lost::Clause& clause) {
      return clause.decode(node);
  }
  
};
  
template<>
struct convert<schizophrenia::wod::lost::Contract> {
    static Node encode ( const schizophrenia::wod::lost::Contract& contract ) {
        return contract.encode();
    }

    static bool decode ( const Node& node, schizophrenia::wod::lost::Contract& contract ) {
        return contract.decode(node);
    }
};
}

#endif
