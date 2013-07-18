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
        typedef unsigned int   RangeType;
        typedef boost::filter_iterator<std::function<bool ( Attribute ) >,typename std::vector<Attribute>::const_iterator> PrequisiteIterator;
        typedef typename std::vector<RangeType>::const_iterator PossibleValueIterator;

        static Merit createMerit ( const IDType& id, ValueType value, const std::string& description = "" );

        template<class OutputIterator>
        static void loadFromFile(const std::string& filename, OutputIterator out);
        
        template<class InputIterator, class OutputIterator>
        static void deserialize(InputIterator begin, InputIterator end, OutputIterator out);
        
        Merit ( void ) = default;

        PrequisiteIterator beginPrequisites ( void ) const;
        PrequisiteIterator endPrequisites ( void ) const;
        PossibleValueIterator beginValues ( void ) const;
        PossibleValueIterator endValues ( void ) const;

        YAML::Node encode ( void ) const;
        bool decode ( const YAML::Node& node );

        bool operator== ( const Merit& right ) const;

        std::string Description;
        std::string Type;
        std::string Book;
        std::string Page;
        bool        Multiple;


    protected:
        Merit ( const IDType& id, const std::string& name, const std::string& type, const std::string& book, const std::string& page );



    private:
        static std::vector<Merit> Prototypes;
        std::vector<std::string> Keywords;
        std::vector<unsigned int> PossibleValues;
    };

    template<class OutputIterator>
    void Merit::loadFromFile(const std::string& filename, OutputIterator out) {
      std::vector<YAML::Node> root = YAML::LoadAllFromFile(filename);
      auto begin = root.begin();
      auto end   = root.end();
      Merit::deserialize(begin,end,out);
    }

    
    
    template<class InputIterator, class OutputIterator>
    void Merit::deserialize(InputIterator begin, InputIterator end, OutputIterator out) {
          std::transform(begin,end,out,[&](const typename InputIterator::value_type& e)-> Merit { Merit m; m.decode(e); return m;} );
    }
    
    
    
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
