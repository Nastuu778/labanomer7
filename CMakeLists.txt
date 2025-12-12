cmake_minimum_required(VERSION 3.15)
project(duplicate_finder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Уведомление, если Boost не найден
find_package(Boost REQUIRED COMPONENTS system filesystem program_options)

# Включаем Boost headers
include_directories(${Boost_INCLUDE_DIRS})

# Исходники
file(GLOB_RECURSE SOURCES src/*.cpp)

# Бинарник
add_executable(${PROJECT_NAME} ${SOURCES})

# Линкуем Boost (даже если header-only — на всякий случай)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
