cmake_minimum_required(VERSION 3.16)

project(pdf_butch_print VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        printer_launcher.cpp
        printer_launcher.hpp
)

qt_add_executable(pdf_butch_print MANUAL_FINALIZATION
  ${PROJECT_SOURCES}
resources/resources.qrc)

target_link_libraries(pdf_butch_print PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(pdf_butch_print PRIVATE Qt6::PrintSupport)


if (NOT DEFINED TRANSLATION_DIR)
    set(TRANSLATION_DIR ${CMAKE_BINARY_DIR}/src/)
endif()
message(TRANSLATION_DIR=${TRANSLATION_DIR})


add_custom_target(update_translations ALL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND /usr/bin/lupdate-qt6 -recursive -locations relative . -ts resources/translations/ru_RU.ts
    COMMAND /usr/bin/lrelease-qt6 resources/translations/ru_RU.ts
    COMMENT "Update and compile translations"
    BYPRODUCTS ${CMAKE_SOURCE_DIR}/resources/translations/ru_RU.qm
)

include(GNUInstallDirs)
install(TARGETS pdf_butch_print
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pdf_butch_print)
endif()
