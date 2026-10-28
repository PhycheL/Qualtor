# 评分器提供的构建模板：Agent 只提交测试源文件，不能修改构建、排除测试或替换被测代码。
cmake_minimum_required(VERSION 3.20)
project(qualtor_scoring LANGUAGES C CXX)

set(CMAKE_C_STANDARD ${QUALTOR_C_STANDARD})
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

foreach(required QUALTOR_MODE QUALTOR_TARGET_SOURCES)
  if(NOT DEFINED ${required} OR "${${required}}" STREQUAL "")
    message(FATAL_ERROR "${required} must be set by the assessment module")
  endif()
endforeach()

find_package(GTest 1.12.1 EXACT CONFIG REQUIRED)

# 被测源文件直接编进测试可执行文件，不打包成静态库：
# 测试里重新定义被测函数会产生重复定义的链接错误，而不是悄悄替换真实实现。
add_executable(scored_tests ${QUALTOR_TEST_SOURCES} ${QUALTOR_TARGET_SOURCES} ${QUALTOR_SUPPORT_SOURCES})
target_include_directories(scored_tests PRIVATE ${QUALTOR_INCLUDE_DIRS})
target_compile_definitions(scored_tests PRIVATE ${QUALTOR_DEFINES})
target_compile_options(scored_tests PRIVATE ${QUALTOR_COMPILE_OPTIONS})
target_compile_options(scored_tests PRIVATE -O0 -g "$<$<COMPILE_LANGUAGE:CXX>:-include;${CMAKE_CURRENT_LIST_DIR}/cxx11_guard.h>")
target_link_libraries(scored_tests PRIVATE GTest::gmock GTest::gtest_main)

if(QUALTOR_MODE STREQUAL "coverage")
  if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR NOT CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "14.2.0")
    message(FATAL_ERROR "coverage mode requires GCC 14.2.0")
  endif()
  if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU" OR NOT CMAKE_C_COMPILER_VERSION VERSION_EQUAL "14.2.0")
    message(FATAL_ERROR "coverage mode requires GCC C 14.2.0")
  endif()
  # 只给被测源文件插桩，测试和 GoogleTest 不进入覆盖率分母。
  set_source_files_properties(${QUALTOR_TARGET_SOURCES} PROPERTIES COMPILE_OPTIONS "--coverage;-fprofile-abs-path")
  target_link_options(scored_tests PRIVATE --coverage)
elseif(QUALTOR_MODE STREQUAL "mull")
  if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR NOT CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "19.1.7")
    message(FATAL_ERROR "mull mode requires Clang 19.1.7")
  endif()
  if(NOT CMAKE_C_COMPILER_ID STREQUAL "Clang" OR NOT CMAKE_C_COMPILER_VERSION VERSION_EQUAL "19.1.7")
    message(FATAL_ERROR "mull mode requires Clang C 19.1.7")
  endif()
  if(NOT EXISTS "/usr/lib/mull-ir-frontend-19")
    message(FATAL_ERROR "Mull LLVM 19 plugin is missing")
  endif()
  # 只给被测源文件加载 Mull 插件。
  set_source_files_properties(${QUALTOR_TARGET_SOURCES} PROPERTIES COMPILE_OPTIONS "-fpass-plugin=/usr/lib/mull-ir-frontend-19;-grecord-command-line")
elseif(QUALTOR_MODE STREQUAL "plain")
  # 不插桩：用于替换版本执行和宿主机辅助检查。
else()
  message(FATAL_ERROR "QUALTOR_MODE must be coverage, mull or plain")
endif()
