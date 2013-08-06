#ifndef SCHIZOPHRENIA_CHARACTER_WOD_CHANGELING_CHANGELING_HPP
#define SCHIZOPHRENIA_CHARACTER_WOD_CHANGELING_CHANGELING_HPP
#include<character/wod/WorldOfDarknessCharacter.hpp>
#include<character/wod/Changeling/Contract.hpp>
namespace schizophrenia {
namespace wod {
namespace lost {

class ChangelingCharacter : public schizophrenia::wod::WorldOfDarknessCharacter {
public:
    typedef std::vector<Contract>::const_iterator ConstContractIterator;

    ChangelingCharacter(void) = default;


    void addContract(const Contract& contract);

    std::tuple<bool,std::string> setValue(const Contract& contract, const typename Contract::ValueType& value);

    template<class TraitType>
    std::tuple<bool,std::string> setValueByID ( const std::string& id, const typename TraitType::ValueType& value );

    template<class Category>
    typename std::vector<Category>::const_iterator beginCategory() const;

    template<class Category>
    typename std::vector<Category>::const_iterator endCategory() const;


protected:
    std::vector<Contract> Contracts;


};




template<>
inline typename std::vector<Contract>::const_iterator ChangelingCharacter::beginCategory<Contract>() const {
    return this->Contracts.begin();
}

template<>
inline typename std::vector<Contract>::const_iterator ChangelingCharacter::endCategory<Contract>() const {
    return this->Contracts.end();
}

template<>
inline std::tuple<bool,std::string> ChangelingCharacter::setValueByID<Contract>( const std::string& id, const typename Contract::ValueType& value ) {
    return this->setGenericValue ( id,this->Contracts,value );
}

template<class Category>
typename std::vector<Category>::const_iterator ChangelingCharacter::beginCategory() const {
    return WorldOfDarknessCharacter::beginCategory<Category>();
}

template<class Category>
typename std::vector<Category>::const_iterator ChangelingCharacter::endCategory() const {
    return WorldOfDarknessCharacter::endCategory<Category>();
}

template<class TraitType>
std::tuple<bool,std::string> ChangelingCharacter::setValueByID ( const std::string& id, const typename TraitType::ValueType& value ) {
    return WorldOfDarknessCharacter::setValueByID<TraitType>(id,value);
}

}
}
}




#endif
