/*
 * PowerStatCheck.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#include<character/wod/checks/PowerStatCheck.hpp>

namespace schizophrenia {
namespace wod {
PowerStatCheck::PowerStatCheck ( const Character& character )
    : Check ( character ) {
    this->PowerStatCount = character.countTrait ( "powerstat" );
    if ( this->PowerStatCount == 1 ) {
        this->PowerStatValue = character["powerstat"].getValue<unsigned short>();
        return;
        }
    if ( this->PowerStatCount == 0 ) {
        this->PowerStatValue = 0;
        }
    }

PowerStatCheck::~PowerStatCheck() {
    }

std::tuple<Check<Character>::Result,std::string> PowerStatCheck::operator() ( const BasicTrait& trait, Action action ) {
    if ( this->PowerStatCount > 1 ) {
        return std::make_tuple ( Reject, "Only one Powerstat attribute may be defined according to core rules" );
        }
    if ( action == Add ) {
        if ( trait.Category == "characteristic" ) {
            return std::make_tuple ( DontCare,"" );
            }


        if ( trait.Name == "powerstat" ) {
            if ( this->PowerStatCount >= 1 ) {
                return std::make_tuple ( Reject, "Only one Powerstat attribute may be defined according to core rules" );
                }
            if ( ! this->checkTraitBounds ( trait ) ) {
                return std::make_tuple ( Reject, "Powerstat attribute must be a natural number between zero and ten" );
                }
            this->PowerStatCount = 1;
            this->PowerStatValue = trait.getValue<unsigned short>();
            return std::make_tuple ( DontCare,"" );
            }
        if ( ! this->checkTraitBounds ( trait ) ) {
            return std::make_tuple ( Reject, "Value above allowed maximum" );
            }
        return std::make_tuple ( DontCare,"" );
        }
    if ( action == Remove ) {
        if ( trait.Category == "characteristic" ) {
            return std::make_tuple ( DontCare,"" );
            }


        if ( trait.Name == "powerstat" && this->PowerStatCount > 1 ) {
            this->PowerStatCount -= 1;
            if ( this->PowerStatCount == 1 ) {
                this->PowerStatValue = this->MonitoredCharacter["powerstat"].getValue<unsigned short>();
                }
            return std::make_tuple ( Accept,"Removing of multiple Powerstat attributes encuraged" );
            }
        if ( trait.Name == "powerstat" && this->PowerStatCount == 1 ) {
            //@NotImplemented
            return std::make_tuple ( Reject,"Removing of Powerstat possible according to core rules, but not implemented yet" );
            }
        }
    return std::make_tuple ( DontCare,"" );
    }

std::tuple<Check<Character>::Result,std::string> PowerStatCheck::operator() ( const BasicTrait& trait, const std::string& value ) {
    if ( trait.Category == "characteristic" ) {
        return std::make_tuple ( DontCare,"" );
        }
    if ( boost::lexical_cast<unsigned> ( value ) <= std::max ( static_cast<unsigned short> ( 5 ),this->PowerStatValue ) ) {
        return std::make_tuple ( DontCare,"" );
        }
    return std::make_tuple ( Reject,"Desired value exceeds maximum" );
    }

std::tuple<Check<Character>::Result,std::string> PowerStatCheck::operator() ( const BasicTrait& trait, const Attribute& attribute, Action action ) {
    return std::make_tuple ( DontCare,"" );
    }

std::tuple<Check<Character>::Result,std::string> PowerStatCheck::operator() ( const BasicTrait& trait, const Attribute& attribute, const std::string& value ) {
    return std::make_tuple ( DontCare,"" );
    }


bool PowerStatCheck::checkTraitBounds ( const BasicTrait& trait ) const {
    if ( trait.Category == "characteristic" ) {
        return true;
        }

    unsigned traitValue = trait.getValue<unsigned>();
    if ( trait.hasAttribute ( "calculated" ) ) {
        return true;
        }

    if ( trait.hasAttribute ( "extended" ) ) {
        return traitValue <= 10;
        }
    return traitValue <= std::max ( static_cast<unsigned short> ( 5 ),this->PowerStatValue );
    }
}

} /* namespace schizohrenia */

