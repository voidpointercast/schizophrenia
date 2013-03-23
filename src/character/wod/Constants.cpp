#include<character/wod/Constants.hpp>
namespace schizophrenia {
 namespace wod {
   
 const schizophrenia::Attribute NoTenAgain     = schizophrenia::Attribute("NoTenAgain","ten must not be rerolled","rule");
 const schizophrenia::Attribute NineAgain      = schizophrenia::Attribute("AgainNine" ,"nines may be rerolled","rule");
 const schizophrenia::Attribute EightAgain     = schizophrenia::Attribute("AgainEight","eights may be rerolled","rule");
 const schizophrenia::Attribute RoteAction     = schizophrenia::Attribute("RoteAction","all die results below 8 may be rerolled once","rule");
 const schizophrenia::Attribute OneAntiSuccess = schizophrenia::Attribute("OneSubstractsSuccess","each one rolled negates one success","rule");
   
 }
  
}