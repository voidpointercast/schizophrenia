#include<fstream>
#include<character/wod/Merit.hpp>

namespace schizophrenia {

std::vector<Merit> Merit::Prototypes {100};


Merit Merit::createMerit ( const Merit::IDType& id, Merit::ValueType value, const std::string& description ) {
    auto pos = std::find_if ( Merit::Prototypes.begin(), Merit::Prototypes.end(), [&] ( const Merit& m ) -> bool { return m.ID == id; } );
    if ( pos == Merit::Prototypes.end() ) {
        throw ( std::runtime_error ( "Merit creation failed. Merit not found <id=" + std::string ( id ) + ">" ) );
        }
    Merit copy = *pos;
    copy.Description = description;
    copy.Value       = boost::lexical_cast<std::string> ( value );
    return copy;
    }


Merit::PrequisiteIterator Merit::beginPrequisites ( void ) const {
    return Merit::PrequisiteIterator ( [] ( const Attribute& a ) -> bool { return a.getCategory() == "prequisite"; }, this->Attributes.begin(), this->Attributes.end() );
    }

Merit::PrequisiteIterator Merit::endPrequisites ( void ) const {
    return Merit::PrequisiteIterator ( [] ( const Attribute& a ) -> bool { return a.getCategory() == "prequisite"; }, this->Attributes.end(), this->Attributes.end() );
    }

Merit::PossibleValueIterator Merit::beginValues ( void ) const {
    return this->PossibleValues.begin();
    }

Merit::PossibleValueIterator Merit::endValues ( void ) const {
    return this->PossibleValues.end();
    }



bool Merit::operator== ( const Merit& right ) const {
    return ( this->Description == right.Description && *static_cast<const BasicTrait*> ( this ) == static_cast<const BasicTrait> ( right ) );
    }


Merit::Merit ( const Merit::IDType& id, const std::string& name, const std::string& type, const std::string& book, const std::string& page )
    : BasicTrait ( id, name, "" ),
      Type ( type ),
      Book ( book ),
      Page ( page ) {

    }

YAML::Node Merit::encode(void) const {
  YAML::Node node = static_cast<const BasicTrait*>(this)->encode();
  node["type"] = this->Type;
  node["book"] = this->Book;
  node["page"] = this->Page;
  YAML::Node possibleValues = node["values"];
  for(const std::tuple<ValueType,std::string>& val : this->PossibleValues) {
      YAML::Node entry;
      entry["value"]       = std::get<0>(val);
      entry["description"] = std::get<1>(val);
      possibleValues.push_back(entry);
  }
  return node; 
}

bool Merit::decode(const YAML::Node& node) {
  static_cast<BasicTrait*>(this)->decode(node);
  this->Type = node["type"].as<std::string>();
  this->Book = node["book"].as<std::string>();
  this->Page = node["page"].as<std::string>();
  this->PossibleValues.clear();
  YAML::Node possibleValues = node["values"];
  auto end = possibleValues.end();
  if(possibleValues.IsSequence()) {
    for(auto it = possibleValues.begin(); it != end; ++it) {
        const YAML::Node entry = *it;
         this->PossibleValues.push_back(std::make_tuple(entry["value"].as<ValueType>(),entry["description"].as<std::string>()));
    }
  }
  return true;
}



}
