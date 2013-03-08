#include<fstream>
#include<character/wod/Merit.hpp>

namespace schizophrenia {

std::vector<Merit> Merit::Prototypes{100}; 
  
  
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

size_t Merit::loadFromFile ( const std::string& filename ) {
    size_t entries{0};
    std::ifstream source{filename.c_str()};
    if( ! source ) {
      throw ( std::runtime_error("Could not load merits from file. Unable to open file " + filename));
    }
    YAML::Parser parser ( source );
    YAML::Node   node;
    while ( parser.GetNextDocument ( node ) ) {
        std::string id;
        std::string name;
        std::string book;
        std::string page;
	std::string type;
	node["id"] >> id;
	node["name"] >> name;
	node["type"] >> type;
	node["book"] >> book;
	node["page"] >> page;
	
        Merit merit ( id,name, type, book,page );
	auto begin = node["prequisites"].begin();
	auto end   = node["prequisites"].end();
        for ( YAML::Iterator i = begin; i != end; ++i ) {
            Attribute attribute(*i);
            merit.Attributes.push_back ( attribute );
            }
	begin = node["possibleValues"].begin();
	end   = node["possibleValues"].end();
        for ( YAML::Iterator i = begin; i != end; ++i ) {
            Merit::ValueType value;
	    std::string description;
	    (*i)["value"] >> value;
	    (*i)["description"] >> description;
            merit.PossibleValues.push_back ( std::make_tuple(value,description) );
            }
	begin = node["keywords"].begin();
	end   = node["keywords"].end();
        for ( YAML::Iterator i = begin; i != end; ++i ) {
	    std::string keyword;
	    *i >> keyword;
            merit.Keywords.push_back ( keyword );
            }
        Merit::Prototypes.push_back ( merit );
	++entries;
        }
        return entries;
    }





Merit::PrequisiteIterator Merit::beginPrequisites ( void ) const {
    return Merit::PrequisiteIterator ([] ( const Attribute& a ) -> bool { return a.getCategory() == "prequisite"; }, this->Attributes.begin(), this->Attributes.end() );
    }

Merit::PrequisiteIterator Merit::endPrequisites ( void ) const {
    return Merit::PrequisiteIterator([] ( const Attribute& a ) -> bool { return a.getCategory() == "prequisite"; }, this->Attributes.end(), this->Attributes.end() );
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







}
