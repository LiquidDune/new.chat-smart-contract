cmake_minimum_required( VERSION 3.5 )

project(a-dex.chat)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

if(${BUILD_TESTS})
    add_definitions(-DDEBUG)
endif()

add_contract(a-dex.chat a-dex.chat 
a-dex.chat.cpp
)

target_include_directories(a-dex.chat
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/tables
${CMAKE_CURRENT_SOURCE_DIR}/include
)