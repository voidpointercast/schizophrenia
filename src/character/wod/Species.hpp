#ifndef CHARACTER_WOD_SPECIES_HPP
#define CHARACTER_WOD_SPECIES_HPP
#include <vector>
#include <character/BasicTrait.hpp>
#include <character/wod/Advantage.hpp>

namespace schizophrenia {
namespace wod {  
 
  class Species : public BasicTrait {
  public:
        static const std::string Category;
        
        Species ( void ) = default;
        
        Species(const Species& head, const std::vector<Species>& path);
        
        Species ( const std::string& id, const std::string& name);
        
        template<class InputIterator>
        Species(const std::string& id, const std::string& name, InputIterator begin, InputIterator end);
        
        template<class InputIterator1, class InputIterator2>
        Species( const std::string& id, const std::string& name, InputIterator1 begin, InputIterator1 end, InputIterator2 beginAdv, InputIterator2 endAdv);
    

        Species operator&(const Species& right) const;
	
	bool operator==(const Species& other) const;
        
        Species& operator+=(const Species& right);
        
        Species pickSpecies(const std::string& id) const;
        
        YAML::Node encode(void) const;
        
        bool decode(const YAML::Node& node);
        
        bool hasSpecies(const std::string& id) const;
        

  protected:
    std::vector<Species>   SubSpecies;
    std::vector<Advantage> Advantages;

  };
  
template<class InputIterator>
Species::Species(const std::string& id, const std::string& name, InputIterator begin, InputIterator end) 
: BasicTrait(id, name , "", Species::Category),
  SubSpecies(),
  Advantages(begin,end) {
    
  }
  
  
template<class InputIterator1, class InputIterator2>
Species::Species ( const std::string& id, const std::string& name, InputIterator1 begin, InputIterator1 end, InputIterator2 beginAdv, InputIterator2 endAdv ) 
: BasicTrait ( id, name, "", Species::Category),
  SubSpecies(begin,end),
  Advantages(beginAdv,endAdv)  {
}

  
  
}
}

namespace YAML {
template<>
struct convert<schizophrenia::wod::Species> {
    static Node encode ( const schizophrenia::wod::Species& species ) {
        return species.encode();
        }

    static bool decode ( const Node& node, schizophrenia::wod::Species& species) {
        return species.decode ( node );
        }
    };
}



#endif