cmake_minimum_required(VERSION 3.16)

project(pdf_bunch_print VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport Concurrent)


set(PROJECT_SOURCES
        main.cpp
        main_window.cpp
        main_window.hpp
        printer_launcher.cpp
        printer_launcher.hpp
)

qt_add_executable(pdf_bunch_print MANUAL_FINALIZATION
  ${PROJECT_SOURCES}
resources/resources.qrc)

target_link_libraries(pdf_bunch_print PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(pdf_bunch_print PRIVATE Qt6::PrintSupport Qt6::Concurrent Qt6::Gui)


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

install (FILES ${CMAKE_SOURCE_DIR}/service/pdf_bunch_print.desktop
  DESTINATION  /usr/share/kio/servicemenus PERMISSIONS  WORLD_READ WORLD_EXECUTE
)

install (FILES ${CMAKE_SOURCE_DIR}/service/pdf_bunch_print_gnome.desktop
  DESTINATION  /usr/share/applications PERMISSIONS  WORLD_READ WORLD_EXECUTE
)

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX /usr)
endif()

include(GNUInstallDirs)
install(TARGETS pdf_bunch_print
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)



if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pdf_bunch_print)
endif()
