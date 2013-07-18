/*
 * Attribute.hpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include<vector>
#include<boost/lexical_cast.hpp>
#include<yaml-cpp/yaml.h>

namespace schizophrenia {

class Attribute {
    public:
        typedef typename std::vector<std::string>::iterator KeywordIterator;
        Attribute ( const std::string& name, const std::string& value );
        Attribute ( const std::string& name, const std::string& value, const std::string& category );
        Attribute ( const YAML::Node& );
        Attribute ( void ) = default;
        Attribute ( const Attribute& copy ) = default;
        virtual ~Attribute();

        bool operator< ( const Attribute& right ) const;

        bool operator== ( const Attribute& right ) const;

        YAML::Node encode ( void ) const;

        bool decode ( const YAML::Node& );

        KeywordIterator begin(void);
        KeywordIterator end(void);
        
        template<typename ReturnType=std::string>
        ReturnType getValue ( void ) const;

        const std::string& getCategory ( void ) const;

        template<typename InputType=std::string>
        void setValue ( const InputType& value );

        template<class Archive>
        void serialize ( Archive& archive, const unsigned int version );

        std::string Name;

    protected:
        std::string Value;
        std::string Category;
    public:
        std::vector<std::string> Keywords;

    };




template<typename ReturnType>
ReturnType Attribute::getValue() const {
    return boost::lexical_cast<ReturnType> ( this->Value );
    }

template<typename InputType>
void Attribute::setValue ( const InputType& value ) {
    this->Value = boost::lexical_cast<std::string> ( value );
    }

template<class Archive>
void Attribute::serialize ( Archive& archive, const unsigned int version ) {
    archive & this->Name;
    archive & this->Value;
    archive & this->Category;
    archive & this->Keywords;
    }



}

namespace YAML {
template<>
struct convert<schizophrenia::Attribute> {
    static Node encode ( const schizophrenia::Attribute& attr ) {
        return attr.encode();
        }

    static bool decode ( const Node& node, schizophrenia::Attribute& attr ) {
        return attr.decode ( node );
        }
    };
}





#endif /* ATTRIBUTE_HPP_ */
