# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/Unity/src)

# Add the Unity source files
set(UNITY_SRC ${PROJECT_SOURCE_DIR}/Unity/src/unity.c)

# Add the test executable
add_executable(MylibTest test_mylib.c ${UNITY_SRC})
target_link_libraries(MylibTest mylib)

# Add tests
add_test(NAME test_mylib COMMAND MylibTest)
