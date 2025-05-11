add_library(rulebase RuleBase.cpp Rules.json)
target_include_directories(rulebase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/third_party/json)
