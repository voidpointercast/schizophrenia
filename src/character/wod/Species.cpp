#include<character/wod/Species.hpp>

const std::string schizophrenia::wod::Species::Category = std::string ( "species" );

schizophrenia::wod::Species::Species ( const std::string& id, const std::string& name ) : schizophrenia::BasicTrait ( id, name ) {
    }


schizophrenia::wod::Species::Species ( const schizophrenia::wod::Species& head, const std::vector< schizophrenia::wod::Species >& path )
    : schizophrenia::wod::Species ( head ) {
    this->SubSpecies.clear();
    schizophrenia::wod::Species& current = *this;
    for ( const schizophrenia::wod::Species& node : path ) {
        current.SubSpecies.push_back ( node );
        current.SubSpecies.back().SubSpecies.clear();
        current = current.SubSpecies.back();
        }
    }

schizophrenia::wod::Species schizophrenia::wod::Species::operator& ( const schizophrenia::wod::Species& right ) const {
    Species meta ( this->ID+right.ID, this->Name+right.Name );
    meta.SubSpecies.push_back ( *this );
    meta.SubSpecies.push_back ( right );
    return meta;
    }

schizophrenia::wod::Species& schizophrenia::wod::Species::operator+= ( const schizophrenia::wod::Species& right ) {
    if ( right.ID == this->ID ) {
        throw ( std::runtime_error ( "Cannot add species to itself for species " + this->ID ) );
        }
    this->SubSpecies.push_back ( right );
    return *this;
    }


schizophrenia::wod::Species schizophrenia::wod::Species::pickSpecies ( const std::string& id ) const {
    if ( this->ID == id ) {
        return *this;
        }
    if ( ! this->hasSpecies ( id ) ) {
        throw ( std::runtime_error ( "Could not pick species " + id + " within species " + this->ID ) );
        }
    std::vector<Species> chain;
    Species& current = const_cast<schizophrenia::wod::Species&> ( *this );
    do {

        for ( const Species& cursor : chain.back().SubSpecies ) {
            if ( cursor.hasSpecies ( id ) ) {
                chain.push_back ( cursor );
                current = cursor;
                break;
                }

            }
        }
    while ( chain.back().ID != id );

    return schizophrenia::wod::Species {*this,chain};
    }

bool schizophrenia::wod::Species::hasSpecies ( const std::string& id ) const {
    if ( this->ID == id ) {
        return true;
        }
    if ( this->SubSpecies.size() == 0 ) {
        return false;
        }
    return std::accumulate ( this->SubSpecies.begin(),this->SubSpecies.end(),false,[&] ( bool init, const schizophrenia::wod::Species& s ) -> bool { return init || s.hasSpecies ( id );} );
    }

bool schizophrenia::wod::Species::operator==(const schizophrenia::wod::Species& other) const {
  if(this == &other) {
      return true;
  }
  if(this->ID != other.ID) {
      return false;
  }
  
  if(!(schizophrenia::BasicTrait::operator==(other))) {
      return false;
  }
  
  if(this->Advantages.size() != other.Advantages.size()) {
      return false;
  }
  
  if(this->SubSpecies.size() != other.SubSpecies.size()) {
      return false;
  }

  
  for(const schizophrenia::wod::Advantage& adv : this->Advantages) {
    if(std::find(other.Advantages.begin(),other.Advantages.end(),adv) == other.Advantages.end()) {
	return false;
    }
  }
  for(const schizophrenia::wod::Species& species : this->SubSpecies) {
    if(std::find(other.SubSpecies.begin(),other.SubSpecies.end(),species) == other.SubSpecies.end()) {
	return false;
    }
  }
  return true;
}
    
    


YAML::Node schizophrenia::wod::Species::encode ( void ) const {
    YAML::Node node = schizophrenia::BasicTrait::encode();
    YAML::Node advantages = node["advantages"];
    YAML::Node subs = node["subspecies"];
    for(const schizophrenia::wod::Advantage& adv : this->Advantages) {
	advantages.push_back<schizophrenia::wod::Advantage>(adv);
    }
    
    for(const schizophrenia::wod::Species& sub : this->SubSpecies) {
	subs.push_back<schizophrenia::wod::Species>(sub);
    }
    return node;
    }

bool schizophrenia::wod::Species::decode ( const YAML::Node& node ) {
    schizophrenia::BasicTrait::decode ( node );
    const YAML::Node advantages = node["advantages"];
    const YAML::Node subspecies = node["subspecies"];
    this->Advantages.clear();
    this->SubSpecies.clear();
    for ( auto adv = advantages.begin(); adv != advantages.end(); ++adv ) {
        this->Advantages.push_back ( adv->as<schizophrenia::wod::Advantage>() );
        }
    if(subspecies.IsNull()) {
	return true;
    }
    for ( auto sub = subspecies.begin(); sub != subspecies.end(); ++sub ) {
        this->SubSpecies.push_back ( sub->as<schizophrenia::wod::Species>() );
        }
    return true;
    }
    