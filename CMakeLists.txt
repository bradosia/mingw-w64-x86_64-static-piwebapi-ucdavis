cmake_minimum_required(VERSION 3.1)

project(ucdavis-Pi-Web-API-Browser VERSION 1.0.0 LANGUAGES CXX)
set(EXENAME ucdavis-Pi-Web-API-Browser)

# Configurable Options
set(BUILD_SHARED_LIBS ON)
set(BUILD_STATIC_LIBS ON)

# Automatically compile .ui to .h
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QTDIR $ENV{QTDIR})

# set(CMAKE_PREFIX_PATH ${QTDIR})
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

find_package(Qt5Widgets REQUIRED)

find_package(Boost 1.56 REQUIRED COMPONENTS
             system filesystem)

include_directories(
  third_party
  third_party/hjson/include

  "${PROJECT_SOURCE_DIR}/src"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

link_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/lib
)


# external library - HJSON
add_subdirectory(third_party/hjson)
# can't target subdirectory so a proxy target is created
add_custom_target(hjsonDone)
add_dependencies(hjsonDone hjson)
get_target_property(mytarget_basename hjson TARGET_FILE)
message(STATUS "hello2 ${mytarget_basename}")
add_custom_command(TARGET hjsonDone POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:hjson> "${CMAKE_BINARY_DIR}")

# external library - PLUGINS
add_subdirectory(src/plugins)

set(SOURCES ${SOURCES}
  src/UI/main.cpp
  src/UI/Application.cpp
  src/UI/MainWindow.cpp
  src/core/SettingsManager.cpp

  src/UI/Application.hpp
  src/UI/MainWindow.hpp
  src/UI/universalInclude.hpp
  src/core/PluginManager.hpp
  src/core/SettingsManager.hpp
  src/core/config.hpp
)

set(RESOURCES ${RESOURCES}
  src/UI/main.ui
  resources/icons_utility.qrc
  resources/icons_file.qrc
  resources/simpletreemodel.qrc
)

add_executable(${EXENAME} ${SOURCES} ${RESOURCES})

target_link_libraries(${EXENAME} PRIVATE
  # QT5
  Qt5::Widgets

  # Boost
  Boost::system
  Boost::filesystem

  # HJSON for loading settings files
  hjson

  # static link a bunch of stuff
  z
  windowscodecs
  stdc++
  gcc
  opengl32
  gdi32
  comdlg32
  oleaut32
  imm32
  winmm
  winspool
  kernel32
  user32
  shell32
  uuid
  ole32
  advapi32
  ws2_32
  mingw32
  rpcrt4
  tiff
  # std::filesystem
  stdc++fs
)

target_include_directories(${EXENAME} PRIVATE
  third_party
  third_party/hjson/include
  src/plugins
)

if(APPLE)
  find_library(COCOA_FRAMEWORK Cocoa)
  target_link_libraries(${EXENAME} ${COCOA_FRAMEWORK})
endif()

if(WIN32)
  set_target_properties(${EXENAME} PROPERTIES
    WIN32 TRUE
  )
elseif(APPLE)
  set_target_properties(${EXENAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    RESOURCE "${RESOURCES}"
  )
endif()

# Post Build
# Copy default setttings
add_custom_command(TARGET ${EXENAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/resources/settings.json" "${CMAKE_BINARY_DIR}")
