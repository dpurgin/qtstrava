add_executable(tst_detailedactivity
    tst_detailedactivity.cpp
    tst_detailedactivity.qrc
)

target_link_libraries(tst_detailedactivity
    Qt5::Test
    qtstrava
    nlohmann_json_qt
    nlohmann_json_schema_validator
    expected-lite
)

add_test(NAME tst_detailedactivity COMMAND tst_detailedactivity)
