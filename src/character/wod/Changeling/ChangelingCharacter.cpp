#include<character/wod/Changeling/ChangelingCharacter.hpp>

void schizophrenia::wod::lost::ChangelingCharacter::addContract(const schizophrenia::wod::lost::Contract& contract) {
    if(std::find(this->Contracts.begin(),this->Contracts.end(),contract) == this->Contracts.end()) {
      this->Contracts.push_back(contract);
    }
}

std::tuple< bool, std::string > schizophrenia::wod::lost::ChangelingCharacter::setValue(const schizophrenia::wod::lost::Contract& contract, const schizophrenia::wod::lost::Contract::ValueType& value)
{
    auto pos = std::find ( this->Contracts.begin(), this->Contracts.end(),contract );
    if ( pos == this->Contracts.end() ) {
        return std::make_tuple ( false,"Could not set value of contract with id=" + contract.ID + ". Contract not found." );
    }
    std::string encValue = boost::lexical_cast<std::string> ( value );
    auto check = this->setValueCheck ( *pos,encValue );
    if ( std::get<0> ( check ) ) {
        pos->Value = encValue;
        return std::make_tuple ( true,"" );
    }
    else {
        return std::make_tuple ( false,"Could not set value of contract with id=" + contract.ID + ". " + std::get<1> ( check ) );
    }
}



