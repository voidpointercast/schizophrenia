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
    if(this->ID != right.ID) {
        return false;
    }
    for(auto attr : this->Attributes) {
        if(std::find(right.Attributes.begin(),right.Attributes.end(),attr) == right.Attributes.end()) {
            return false;
        }
    }
    return true;
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
    if(!node["id"]) {
	throw(std::runtime_error("ID missing"));
    }
    if(!node["name"]) {
	throw(std::runtime_error("Name missing"));
    }
  
    this->ID   = node["id"].as<std::string>();
    this->Name = node["name"].as<std::string>();
    
    
    //Optional fields
    if(node["value"]) {
      this->Value= node["value"].as<std::string>();
    } else {
	this->Value = "";
    }
    if(node["book"]) {
      this->Book = node["book"].as<std::string>();
    } else {
	this->Book = "";
    }
    if(node["page"]) {
      this->Page = node["page"].as<std::string>();
    } else {
	this->Page = "";
    }
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
