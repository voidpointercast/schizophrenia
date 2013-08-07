#include<unittests/Unittest.hpp>
#include<array>
#include<character/wod/Species.hpp>

int main(void) {
    unittest::beginTest("Bidirectional Species to YAML test");
    std::array<schizophrenia::wod::Species,2> subSpecies;
    std::array<schizophrenia::wod::Advantage,2> advantages;
    subSpecies[0] = schizophrenia::wod::Species("SUBID1","SUB1");
    subSpecies[1] = schizophrenia::wod::Species("SUBID2","SUB2");
    advantages[0] = schizophrenia::wod::Advantage("ADVID1","ADVNAME1","ADVVALUE1");
    advantages[1] = schizophrenia::wod::Advantage("ADVID2","ADVNAME2","ADVVALUE2");
    schizophrenia::wod::Species original("ID","SPECIES",subSpecies.begin(),subSpecies.end(),advantages.begin(),advantages.end());
    YAML::Node node = original.encode();
    schizophrenia::wod::Species copy;
    copy.decode(node);
    unittest::endTest(copy == original);
    unittest::beginTest("Construction from YAML file");
    std::vector<YAML::Node> root = YAML::LoadAllFromFile("./data/testdata/kith.yaml");
    schizophrenia::wod::Species loader;
    for(auto node : root) {
      loader.decode(node);
    }
    unittest::endTest(true);
  
}