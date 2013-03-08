#include<unittests/Unittest.hpp>
#include<character/wod/Merit.hpp>

int main(void) {
  unittest::beginTest("Load merits from YAML file basic test");
  size_t count = schizophrenia::Merit::loadFromFile("./data/testdata/merittest.yaml");
  unittest::endTest(count == 1, "unexpected count, got " + boost::lexical_cast<std::string>(count));
  unittest::beginTest("Load merits from YAML file data integration test");
  schizophrenia::Merit merit = schizophrenia::Merit::createMerit("ID", 2, "description");
  unittest::endTest(merit.Name == "NAME" && merit.Book == "BOOK" && std::get<0>(*merit.beginValues()) == 1);
  return 0;
}