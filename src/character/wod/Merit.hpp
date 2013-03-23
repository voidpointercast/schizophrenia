#ifndef CHARACTER_WOD_MERIT_HPP
#define CHARACTER_WOD_MERIT_HPP
#include<boost/iterator/filter_iterator.hpp>
#include<character/BasicTrait.hpp>

namespace schizophrenia {
namespace wod {
class Merit : public BasicTrait {
    public:
        typedef std::string    IDType;
        typedef unsigned short ValueType;
        typedef boost::filter_iterator<std::function<bool ( Attribute ) >,typename std::vector<Attribute>::const_iterator> PrequisiteIterator;
	typedef typename std::vector<std::tuple<ValueType,std::string>>::const_iterator PossibleValueIterator;
	
        static Merit createMerit ( const IDType& id, ValueType value, const std::string& description = "" );
	
	Merit(void) = default;

        PrequisiteIterator beginPrequisites ( void ) const;
        PrequisiteIterator endPrequisites ( void ) const;
	PossibleValueIterator beginValues(void) const;
	PossibleValueIterator endValues(void) const;

        YAML::Node encode(void) const;
        bool decode(const YAML::Node& node);

        bool operator== ( const Merit& right ) const;

        std::string Description;
	std::string Type;
	std::string Book;
	std::string Page;


    protected:
	Merit(const IDType& id, const std::string& name, const std::string& type, const std::string& book, const std::string& page);



    private:
        static std::vector<Merit> Prototypes;
	std::vector<std::string> Keywords;
	std::vector<std::tuple<ValueType, std::string>> PossibleValues;
    };

}
}
namespace YAML {
template<>
struct convert<schizophrenia::wod::Merit> {
    static Node encode ( const schizophrenia::wod::Merit& merit ) {
        return merit.encode();
        }

    static bool decode ( const Node& node, schizophrenia::wod::Merit& merit ) {
        return merit.decode ( node );
        }
    };
}
#endif
