cmake_minimum_required(VERSION 3.10)

project(StudentProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(modules)
add_subdirectory(thirdparty/googletest)

enable_testing()
add_subdirectory(tests)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE studentlib)

# ===== Install Rules =====
# Install the executable to the bin directory
install(TARGETS main DESTINATION bin)

# Install the student data text files
install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/students10000.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/students100000.txt
        DESTINATION .
)

# ===== CPack Configuration =====
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "MyApp")
set(CPACK_PACKAGE_VENDOR "YourName")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "My CLI App")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "your@email.com")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

set(CPACK_GENERATOR "ZIP")

include(CPack)
