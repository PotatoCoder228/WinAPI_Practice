cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (WinAPIPractice)
if(WIN32)
set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:wWinMainCRTStartup")
endif(WIN32)

add_executable (WinAPIPractice "WinAPIPractice.cpp"  "GraphManager.cpp" "GraphManager.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WinAPIPractice PROPERTY CXX_STANDARD 20)
endif()
