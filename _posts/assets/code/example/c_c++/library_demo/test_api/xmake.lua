add_rules("mode.debug", "mode.release")

target("test_api")
    set_kind("shared")
    add_files("test_api.cpp")