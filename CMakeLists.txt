cmake_minimum_required(VERSION 2.8)
project(Schizophrenia)
INCLUDE_DIRECTORIES("src/")
SET(EXECUTABLE_OUTPUT_PATH "./bin/")
SET(LIBRARY_OUTPUT_PATH "./lib/")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread -Wall -Wextra -Wno-unused-parameter -pedantic -O3 -Werror")

add_library(schizophrenia SHARED "src/character/Character.cpp" "src/character/Attribute.cpp" "src/character/BasicTrait.cpp")
add_library(schizophrenia-wod SHARED "src/character/wod/WorldOfDarknessCharacter.cpp"
"src/character/wod/checks/PowerStatCheck.cpp"
"src/character/wod/Merit.cpp"
"src/character/wod/Skill.cpp"
"src/character/wod/Attribute.cpp"
"src/character/wod/Characteristic.cpp"
"src/character/wod/Species.cpp"
"src/character/wod/Advantage.cpp"
)
add_library(schizophrenia-lost SHARED "src/character/wod/Changeling/Contract.cpp"
"src/character/wod/Changeling/ChangelingCharacter.cpp")


target_link_libraries(schizophrenia-wod schizophrenia)
target_link_libraries(schizophrenia yaml-cpp)
target_link_libraries(schizophrenia-lost schizophrenia-wod)

add_executable(WODTemplateTest "src/unittests/WorldOfDarknessTemplateTest.cpp")
add_executable(BasicTraitYamlTest "src/unittests/BasicTraitYamlTest.cpp")
add_executable(CharacterTest "src/unittests/CharacterTest.cpp")
add_executable(MeritTest "src/unittests/MeritTest.cpp")
add_executable(SpeciesTest "src/unittests/Species.cpp")
add_executable(TemplateGenerator "src/unittests/WODTemplateGenerator.cpp")

target_link_libraries(WODTemplateTest yaml-cpp schizophrenia-wod)
target_link_libraries(BasicTraitYamlTest yaml-cpp schizophrenia)
target_link_libraries(CharacterTest yaml-cpp schizophrenia)
target_link_libraries(MeritTest yaml-cpp schizophrenia-wod)
target_link_libraries(TemplateGenerator yaml-cpp schizophrenia schizophrenia-wod)
target_link_libraries(SpeciesTest schizophrenia-wod)


add_subdirectory(src/character/wod/Changeling)