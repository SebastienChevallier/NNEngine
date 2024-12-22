# CMake generated Testfile for 
# Source directory: C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine
# Build directory: C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(TestApp "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/build/Debug/TestApp.exe")
  set_tests_properties(TestApp PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;51;add_test;C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(TestApp "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/build/Release/TestApp.exe")
  set_tests_properties(TestApp PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;51;add_test;C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(TestApp "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/build/MinSizeRel/TestApp.exe")
  set_tests_properties(TestApp PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;51;add_test;C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(TestApp "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/build/RelWithDebInfo/TestApp.exe")
  set_tests_properties(TestApp PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;51;add_test;C:/Users/schev/source/repos/Git-NNE/NoNameEngine/NoNameEngine/CMakeLists.txt;0;")
else()
  add_test(TestApp NOT_AVAILABLE)
endif()
