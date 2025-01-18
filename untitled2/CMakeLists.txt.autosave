cmake_minimum_required(VERSION 3.16)

project(untitled2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)  # Убедитесь, что у вас установлен стандарт C++11 (или выше)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appuntitled2
    main.cpp
    MyModel.cpp  # Добавлено в список файлов, если он нужен для компиляции
)

qt_add_qml_module(appuntitled2
    URI untitled2
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        MyModel.h
)

# Установка свойств для приложения (можно закомментировать, если не нужно)
set_target_properties(appuntitled2 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Подключаем необходимые библиотеки
target_link_libraries(appuntitled2
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql  # Добавлено подключение к Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appuntitled2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
