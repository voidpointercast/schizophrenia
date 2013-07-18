#include<unittests/Unittest.hpp>
#include<character/wod/Merit.hpp>

int main(void) {
  unittest::beginTest("Bidirectional Merit to YAML conversion test");
  schizophrenia::wod::Merit merit;
  schizophrenia::wod::Merit copy;
  merit.Name  = "NAME";
  merit.Book  = "BOOK";
  merit.Value = 5;
  try {
    copy.decode(merit.encode());
  } catch(YAML::Exception& error) {
    unittest::endTest(false,"Error in conversion: " + std::string(error.what()));
    return 1;
  }
  unittest::endTest(copy == merit, "Copy and original do not match");
  
  
  unittest::beginTest("Load merits from YAML file data integration test");
  unittest::endTest(merit.Name == "NAME" && merit.Book == "BOOK" && std::distance(merit.beginValues(),merit.endValues())==0);
  unittest::beginTest("Load merits from file using LoadFromFile method");
  std::vector<schizophrenia::wod::Merit> merits;
  schizophrenia::wod::Merit::loadFromFile("./data/testdata/merits.yaml",std::back_inserter(merits));
  unittest::endTest(true);
  return 0;
}