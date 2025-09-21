cmake_minimum_required(VERSION 3.15)
project(ChatApp CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir headers
include_directories(
    ${PROJECT_SOURCE_DIR}/include/**
    ${PROJECT_SOURCE_DIR}/external/crow/include
    ${PROJECT_SOURCE_DIR}/external/json/include
    ${PROJECT_SOURCE_DIR}/external/libpqxx/include
    ${PROJECT_SOURCE_DIR}/external/asio/asio/include
)

# Fontes do projeto
add_executable(chat-app
    main.cpp
)

# Build libpqxx
add_subdirectory(external/libpqxx)

# Linkar libpqxx
target_link_libraries(chat-app PRIVATE pqxx pq)