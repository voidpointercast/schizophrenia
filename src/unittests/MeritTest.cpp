#include<unittests/Unittest.hpp>
#include<character/wod/Merit.hpp>

int main(void) {
  unittest::beginTest("Bidirectional Merit to YAML conversion test");
  schizophrenia::Merit merit;
  schizophrenia::Merit copy;
  merit.Value = 5;
  try {
    copy.decode(merit.encode());
  } catch(YAML::Exception& error) {
    unittest::endTest(false,"Error in conversion: " + std::string(error.what()));
    return 1;
  }
  unittest::endTest(copy == merit, "Copy and original do not match");
  
  
  unittest::beginTest("Load merits from YAML file basic test");
  
  try {
    YAML::Node doc = YAML::LoadFile("./data/testdata/merittest.yaml");
    merit.decode(doc);
  } catch(YAML::Exception& error) {
    unittest::endTest(false,"Could not parse merit file correctly: " + std::string(error.what()));
    return 1;
  }
  unittest::endTest(true);
  unittest::beginTest("Load merits from YAML file data integration test");
  unittest::endTest(merit.Name == "NAME" && merit.Book == "BOOK" && std::get<0>(*merit.beginValues()) == 1);
  return 0;
}