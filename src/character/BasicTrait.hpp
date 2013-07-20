#ifndef BASICTRAIT_HPP_
#define BASICTRAIT_HPP_
#include<vector>
#include<iostream>
#include<string>
#include<memory>
#include<algorithm>
#include<boost/lexical_cast.hpp>
#include<yaml-cpp/yaml.h>
#include<character/Attribute.hpp>

namespace schizophrenia {

struct BasicTrait {
    public:
        typedef std::string ValueType;
        BasicTrait ( const std::string& name, const std::string& value );
        BasicTrait ( const std::string& id, const std::string& name, const std::string& value );
        BasicTrait ( const std::string& id, const std::string& name, const std::string& value , const std::string& category);
        template<class InputIterator>
        BasicTrait ( const std::string& name, const std::string& value, InputIterator begin, InputIterator end );
        template<class InputIterator>
        BasicTrait ( const std::string& id, const std::string& name, const std::string& value, InputIterator begin, InputIterator end );
        BasicTrait ( const BasicTrait& copy ) = default;
        BasicTrait ( void ) = default;
        virtual ~BasicTrait();
        bool operator< ( const BasicTrait& right ) const;
        bool operator== ( const BasicTrait& right ) const;
        bool operator== ( const std::string& right ) const;
        bool hasAttribute ( const std::string& attribute ) const;
        bool hasAttribute ( const Attribute& attribute ) const;
        YAML::Node encode ( void ) const;
        bool decode ( const YAML::Node& node );

        template<class Archive>
        void serialize ( Archive& archive, const unsigned int version=0 );

        template<class ReturnType>
        ReturnType getValue ( void ) const;

        void save ( std::ostream& out ) const;

        std::string             Value;
        std::vector<Attribute>  Attributes;
        std::string             Name;
        std::string             ID;
        std::string             Category;
        std::string             Book;
        unsigned short          Page;
    };

template<class Archive>
void BasicTrait::serialize ( Archive& archive, const unsigned int version ) {
    archive & this->ID;
    archive & this->Name;
    archive & this->Attributes;
    archive & this->Value;
    }

template<class InputIterator>
BasicTrait::BasicTrait ( const std::string& name, const std::string& value, InputIterator begin, InputIterator end )
    :  Value ( value ), Attributes ( begin,end ),Name ( name ),  ID ( name ) {

    }

template<class InputIterator>
BasicTrait::BasicTrait ( const std::string& id, const std::string& name, const std::string& value, InputIterator begin, InputIterator end )
    : Value ( value ), Attributes ( begin,end ), Name ( name ),ID ( id )  {
    }

template<class ReturnType>
ReturnType BasicTrait::getValue ( void ) const {
    return boost::lexical_cast<ReturnType> ( this->Value );
    }
}

namespace YAML {
template<>
struct convert<schizophrenia::BasicTrait> {
    static Node encode ( const schizophrenia::BasicTrait& trait ) {
        return trait.encode();
        }

    static bool decode ( const Node& node, schizophrenia::BasicTrait& trait ) {
        return trait.decode ( node );
        }



    };

}


#endif
