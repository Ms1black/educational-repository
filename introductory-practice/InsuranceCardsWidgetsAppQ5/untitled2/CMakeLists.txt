# Установите минимальную требуемую версию CMake. 3.16+ рекомендуется для лучшей поддержки Qt.
cmake_minimum_required(VERSION 3.16)

# Определение проекта
project(untitled2 VERSION 0.1 LANGUAGES CXX)

# Включение стандартных настроек CMake для Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Добавить текущие директории в пути поиска заголовочных файлов
set(CMAKE_AUTOUIC ON)             # Включить автоматическую обработку .ui файлов
set(CMAKE_AUTOMOC ON)             # Включить автоматический запуск Meta-Object Compiler (moc)
set(CMAKE_AUTORCC ON)             # Включить автоматическую обработку .qrc файлов (если они есть)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Поиск Qt ---
# Ищем самую новую доступную версию Qt (сначала Qt6, потом Qt5),
# которая содержит необходимые компоненты Widgets и Charts.
# Эта команда установит QT_VERSION_MAJOR и другие переменные Qt.
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)

# Эта команда гарантирует, что CMake-цели (targets) для *конкретной* найденной
# версии Qt (например, Qt5::Widgets, Qt5::Charts или Qt6::Widgets, Qt6::Charts)
# будут корректно импортированы и доступны для target_link_libraries.
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

# Выводим найденную версию Qt для информации (опционально)
message(STATUS "Found Qt version: ${Qt${QT_VERSION_MAJOR}_VERSION_STRING} (major: ${QT_VERSION_MAJOR})")
message(STATUS "Using Qt${QT_VERSION_MAJOR}::Widgets and Qt${QT_VERSION_MAJOR}::Charts")

# --- Определение исходных файлов проекта ---
# Соберите ВСЕ исходные файлы (.cpp), заголовки (.h) и UI-файлы (.ui) в один список.
# CMAKE_AUTOUIC автоматически обработает .ui файлы из этого списка при сборке цели.
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui     # <-- AUTOUIC обработает это
    ChartDialog.cpp
    ChartDialog.h
    ChartDialog.ui    # <-- AUTOUIC обработает это
    tablemanager.cpp
    tablemanager.h
    filemanager.cpp
    filemanager.h
    chartmanager.cpp
    chartmanager.h
    # Добавьте сюда другие ваши .cpp, .h или .qrc файлы, если они появятся
)

# --- Создание исполняемого файла ---
# Используем разные команды для Qt 6 и Qt 5 для лучшей совместимости
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # qt_add_executable - современный способ для Qt 6
    qt_add_executable(untitled2
        ${PROJECT_SOURCES}
    )
else()
    # Для Qt 5 используем стандартный add_executable.
    # Обработка Android из вашего оригинального файла сохранена.
    if(ANDROID)
        add_library(untitled2 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(untitled2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# --- Компоновка (линковка) с библиотеками Qt ---
# Используем импортированные CMake-цели Qt. Это работает одинаково
# хорошо и для Qt 5 (Qt5::Widgets, Qt5::Charts) и для Qt 6 (Qt6::Widgets, Qt6::Charts),
# так как ${QT_VERSION_MAJOR} будет равен 5 или 6 в зависимости от найденной версии.
target_link_libraries(untitled2 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
)

# --- Опционально: Установка (для развертывания) ---
# Если вам нужна установка приложения (например, через 'make install')
# include(GNUInstallDirs)
# install(TARGETS untitled2
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # Исполняемый файл
#     # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # Если бы это была библиотека
# )
# Для Qt приложений также может потребоваться установка зависимостей Qt,
# см. документацию CPack или deployqt утилиты.
