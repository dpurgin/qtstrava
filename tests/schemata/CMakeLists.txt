add_executable(tst_schemata tst_schemata.cpp)

target_link_libraries(tst_schemata
    Qt5::Test
    qtstrava
    nlohmann_json_schema_validator
)

add_test(NAME tst_schemata COMMAND tst_schemata)
