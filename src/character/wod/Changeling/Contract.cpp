#include <character/wod/Changeling/Contract.hpp>

const std::string schizophrenia::wod::lost::Clause::Category   = std::string("clause");
const std::string schizophrenia::wod::lost::Contract::Category = std::string("contract");


schizophrenia::wod::lost::Clause::Clause(const std::string& id, const std::string& name, const std::string& value): BasicTrait(id, name, value, Clause::Category) {
}

bool schizophrenia::wod::lost::Contract::operator==(const schizophrenia::wod::lost::Contract& other) const
{
  return other.ID == this->ID;
}



bool schizophrenia::wod::lost::Clause::decode(const YAML::Node& node) {
  schizophrenia::BasicTrait::decode(node);
  this->Catch = node["catch"].as<std::string>();
  this->Roll  = node["roll"].as<std::string>();
  this->Effect= node["effect"].as<std::string>();
  this->Cost  = node["cost"].as<std::string>();
  return true;
}

YAML::Node schizophrenia::wod::lost::Clause::encode(void) const {
  YAML::Node node = schizophrenia::BasicTrait::encode();
  node["catch"] = this->Catch;
  node["roll"]  = this->Roll;
  node["effect"]= this->Effect;
  node["cost"]  = this->Cost;
  return node;
}



schizophrenia::wod::lost::Contract::Contract(const std::string& id, const std::string& name, const std::string& value): BasicTrait(id, name, value, Contract::Category){
}

bool schizophrenia::wod::lost::Contract::decode(const YAML::Node& node) {
  schizophrenia::BasicTrait::decode(node);
  auto clauses = node["clauses"];
  this->Clauses.clear();
  for(auto i=clauses.begin(); i != clauses.end(); ++i) {
    schizophrenia::wod::lost::Clause clause;
    clause.decode(*i);
    this->Clauses.push_back(clause);
  }
  return true;
}

YAML::Node schizophrenia::wod::lost::Contract::encode(void) const {
    YAML::Node node = schizophrenia::BasicTrait::encode();
    auto clauses = node["clauses"];
    for(const Clause& clause : this->Clauses) {
	clauses.push_back<schizophrenia::wod::lost::Clause>(clause);
    }
    return node;
}