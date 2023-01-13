include(FetchContent)

# Setup plugin-sdk & xbyak
set(PSDK_EXAMPLES OFF)
set(PSDK_INSTALL  OFF)
set(PSDK_GTASA    ON)

FetchContent_Declare(
    plugin-sdk
    GIT_REPOSITORY https://github.com/imring/plugin-sdk.git
    GIT_TAG 81b18b744b64db3058f48344c144591c9030205b
)
FetchContent_Declare(
    xbyak
    GIT_REPOSITORY https://github.com/herumi/xbyak.git
    GIT_TAG 2a85bba3fe304c387d652537b715b09005e747f9
)
FetchContent_MakeAvailable(plugin-sdk xbyak)

add_library(multiplemarkers SHARED
    "main.cpp"
    "patch.cpp"
)
set_target_properties(multiplemarkers PROPERTIES SUFFIX ".asi")
target_include_directories(multiplemarkers PRIVATE .)
target_link_libraries(multiplemarkers PRIVATE xbyak::xbyak pluginsdk::gtasa)
target_compile_features(multiplemarkers PRIVATE cxx_std_20)