#include<character/wod/Characteristic.hpp>

schizophrenia::wod::Characteristic::Characteristic ( const std::string& name, const std::string& value )
: schizophrenia::BasicTrait ( name, name, value, "characteristic" )
{
}

schizophrenia::wod::Characteristic::Characteristic ( const std::string& id, const std::string& name, const std::string& value )
: schizophrenia::BasicTrait ( id, name, value, "characteristic" )
  {

}
