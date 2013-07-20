#include<character/BasicTrait.hpp>



namespace schizophrenia {

  
BasicTrait::BasicTrait ( const std::string& name, const std::string& value )
    : Value ( value ), Attributes ( size_t ( 0 ) ), Name ( name ), ID ( name )  {

    }

BasicTrait::BasicTrait ( const std::string& id, const std::string& name, const std::string& value )
    : Value ( value ), Attributes ( size_t ( 0 ) ), Name ( name ), ID ( id )  {

    }

BasicTrait::BasicTrait(const std::string& id, const std::string& name, const std::string& value, const std::string& category)
    : Value(value), Attributes(0), Name(name), ID(id), Category(category) {
      
    }
    
BasicTrait::~BasicTrait ( void ) {

    }

bool BasicTrait::operator< ( const BasicTrait& right ) const {
    return this->Name < right.Name;
    }


bool BasicTrait::operator== ( const BasicTrait& right ) const {
    return this->ID == right.ID && this->Attributes == right.Attributes;
    }

bool BasicTrait::operator== ( const std::string& right ) const {
    return this->ID == right;
    }


bool BasicTrait::hasAttribute ( const std::string& attribute ) const {
    auto begin = this->Attributes.begin();
    auto end   = this->Attributes.end();
    return std::find_if ( begin,end,[&attribute] ( const Attribute& attr )->bool {return attr.Name == attribute;} ) != this->Attributes.end();
    }

bool BasicTrait::hasAttribute ( const Attribute& attribute ) const {
    auto begin = this->Attributes.begin();
    auto end   = this->Attributes.end();
    return std::find ( begin,end,attribute ) != this->Attributes.end();
    }

YAML::Node BasicTrait::encode ( void ) const {
    YAML::Node node;
    node["id"]    = this->ID;
    node["name"]  = this->Name;
    node["value"] = this->Value;
    node["book"]  = this->Book;
    node["page"]  = this->Page;
    YAML::Node attributes = node["attributes"];
    std::for_each ( this->Attributes.begin(),this->Attributes.end(),[&] ( const Attribute& attr ) -> void { attributes.push_back<Attribute> ( attr ); } );
     return node;
    }

bool BasicTrait::decode ( const YAML::Node& node ) {
    this->ID   = node["id"].as<std::string>();
    this->Name = node["name"].as<std::string>();
    this->Value= node["value"].as<std::string>();
    this->Book = node["book"].as<std::string>();
    this->Page = node["page"].as<std::string>();
    const YAML::Node attributes = node["attributes"];
    this->Attributes.clear();
    if ( attributes.IsSequence() ) {
      auto end = attributes.end();
      for(auto it=attributes.begin(); it != end; ++it) {
         this->Attributes.push_back(it->as<Attribute>());
      }
    }
    return true;
    }



}
