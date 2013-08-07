#include<character/wod/Advantage.hpp>

const std::string schizophrenia::wod::Advantage::Category = std::string("advantage");

schizophrenia::wod::Advantage::Advantage ( const std::string& id, const std::string& name, const std::string& value )
: BasicTrait (id, name, value, schizophrenia::wod::Advantage::Category ),
  IsDisadvantage(false) {

    }

schizophrenia::wod::Advantage::~Advantage(void ){

}
    
    
bool schizophrenia::wod::Advantage::operator==(const schizophrenia::wod::Advantage& other) const {
  if(this == &other) {
      return true;
  }
  if(this->IsDisadvantage != other.IsDisadvantage) {
      return false;
  }
  
  if(!schizophrenia::BasicTrait::operator==(other)) {
      return false;
  }
  return true;
}

YAML::Node schizophrenia::wod::Advantage::encode(void ) const {
  YAML::Node node = schizophrenia::BasicTrait::encode();
  node["disadvantage"] = this->IsDisadvantage;
  return node;
}

bool schizophrenia::wod::Advantage::decode(const YAML::Node& node) {
  if(node.IsScalar()) {
	const std::string content = node.as<std::string>();
	this->ID   = std::hash<std::string>{}(content);
	this->Name = "anonymousAdvantage";
	this->Value= content;
	return true;
  }
  
  schizophrenia::BasicTrait::decode(node);
  if(node["disadvantage"]) {
    this->IsDisadvantage = node["disadvantage"].as<bool>();
  } else {
      this->IsDisadvantage = false;
  }
  return true;
}
