cmake_minimum_required(VERSION 3.5)

project(mingw-w64-x86_64-static-piwebapi-ucdavis LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXENAME piwebapi-ucdavis)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# configure compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
# generate proper GUI program on specified platform
if(WIN32) # Check if we are on Windows
        if(MINGW)
            # COMPILER-SETTINGS FOR MINGW
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=gnu++17")
            # SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
        elseif(MSVC) # Check if we are using the Visual Studio compiler
            set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE YES
                LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
            # COMPILER-SETTINGS FOR MS VISUAL C++
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
            # To fix error: C2338: va_start argument must not
            # have reference type and must not be parenthesized
            add_definitions(/D_CRT_NO_VA_START_VALIDATION)
            add_definitions(/DNOMINMAX)
        else()
            message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
        endif(MSVC)
elseif(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                        MACOSX_BUNDLE YES
        )
elseif(UNIX)
        # Nothing special required
else()
        message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)


if(MINGW)
  # COMPILER-SETTINGS FOR MINGW
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")
elseif(MSVC)
  # COMPILER-SETTINGS FOR MS VISUAL C++
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
  # To fix error: C2338: va_start argument must not
  # have reference type and must not be parenthesized
  add_definitions(/D_CRT_NO_VA_START_VALIDATION)
  add_definitions(/DNOMINMAX)
endif()

 add_executable(${EXENAME}
    src/main.cpp
    src/mainwindow.cpp
    src/treeitem.cpp
    src/treemodel.cpp
    src/amalgamated.cpp
    include/piwebapi-ucdavis/mainwindow.h
    include/piwebapi-ucdavis/treeitem.h
    include/piwebapi-ucdavis/treemodel.h
    include/piwebapi-ucdavis/amalgamated.h
    src/mainwindow.ui
    resources/icons_utility.qrc
    resources/icons_file.qrc
    resources/simpletreemodel.qrc
 )

target_link_directories(${EXENAME} PRIVATE
/lib/)

target_link_libraries(${EXENAME} PRIVATE
Qt5::Widgets
curl
nghttp2
psl.dll
idn2
gnutls
ssl
crypto
cares
ssh2
brotlidec-static
brotlienc-static
brotlicommon-static
unistring
wldap32
libz
bcrypt
crypt32

# static link a bunch of stuff
stdc++
gcc
opengl32
glu32
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
include
third_party
)

# Installation
install(TARGETS ${EXENAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
