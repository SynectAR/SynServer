cmake_minimum_required(VERSION 3.5)

project(SynServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

###
#GENERATING
###

set(PB_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
set(PB_DIR "${CMAKE_SOURCE_DIR}")
set(VNARPC_PROTO_SRCS "${PB_DIR}/vnarpc.pb.cc")
set(VNARPC_PROTO_HDRS "${PB_DIR}/vnarpc.pb.h")
set(VNARPC_GRPC_SRCS "${PB_DIR}/vnarpc.grpc.pb.cc")
set(VNARPC_GRPC_HDRS "${PB_DIR}/vnarpc.grpc.pb.h")

if (WIN32)
    set(GRPC_CPP_PLUGIN ${gRPC_LIB_DIRS}/../bin/grpc_cpp_plugin.exe)
else ()
    set(GRPC_CPP_PLUGIN ${gRPC_LIB_DIRS}/../bin/grpc_cpp_plugin)
endif ()

message(${GRPC_CPP_PLUGIN})
message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
message(STATUS ${Protobuf_PROTOC_EXECUTABLE})
add_custom_command(
        OUTPUT "${VNARPC_PROTO_SRCS}" "${VNARPC_PROTO_HDRS}" "${VNARPC_GRPC_SRCS}" "${VNARPC_GRPC_HDRS}"
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}#$<TARGET_FILE:protobuf::protoc>
        ARGS --grpc_out "${PB_DIR}"
        --cpp_out "${PB_DIR}"
        -I "${PB_SOURCE_DIR}"
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
        "${PB_SOURCE_DIR}/vnarpc.proto"
        DEPENDS "${PB_SOURCE_DIR}/vnarpc.proto")

###
#
###

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Qt5 COMPONENTS Qml REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        tempsoltcalibrator.cpp
        tempsoltcalibrator.h
        scpisocketsession.cpp
        scpisoltcalibrator.cpp
        server.cpp
        isoltcalibrator.h
        scpisocketsession.h
        scpisoltcalibrator.h
        server.h
        qml.qrc
        images.qrc
        rpcclient.cpp
        rpcclient.h
        # generated files
        vnarpc.grpc.pb.cc
        vnarpc.pb.cc
        vnarpc.grpc.pb.h
        vnarpc.pb.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SynServer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SynServer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SynServer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SynServer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SynServer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt5::Network
    Qt5::Qml
    gRPC::gRPC
    protobuf::protobuf
    )

set_target_properties(SynServer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SynServer)
endif()
