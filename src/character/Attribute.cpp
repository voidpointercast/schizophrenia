/*
 * Attribute.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#include "Attribute.hpp"

namespace schizophrenia {

Attribute::Attribute ( const std::string& name, const std::string& value )
    : Name ( name ),
      Value ( value ) {

    }

Attribute::Attribute ( const YAML::Node& node ) {
    this->decode ( node );
    }




Attribute::~Attribute() {
    // TODO Auto-generated destructor stub
    }

bool Attribute::operator< ( const Attribute& right ) const {
    return this->Name < right.Name;
    }

bool Attribute::operator== ( const Attribute& right ) const {
    return this->Name == right.Name;
    }

const std::string& Attribute::getCategory ( void ) const {
    return this->Category;
    }


YAML::Node Attribute::encode ( void ) const {
    YAML::Node node;
    node["name"]        = this->Name;
    node["value"]       = this->Value;
    node["category"]    = this->Category;
    YAML::Node keywords = node["keywords"];
    std::for_each ( this->Keywords.begin(), this->Keywords.end(), [&] ( const std::string& key ) -> void { keywords.push_back ( key ); } );
    return node;
    }

bool Attribute::decode ( const YAML::Node& node ) {
    this->Name     = node["name"].as<std::string>();
    this->Value    = node["value"].as<std::string>();
    this->Category = node["category"].as<std::string>();
    const YAML::Node keywords = node["keywords"];
    this->Keywords.clear();
    if ( keywords.IsSequence() ) {
        for ( auto it = keywords.begin(); it != keywords.end(); ++it ) {
            this->Keywords.push_back ( it->as<std::string>() );
            }
        }
    return true;
    }

}
