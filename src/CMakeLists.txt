set(CMAKE_PREFIX_PATH "/Users/idawnlight/Qt/6.2.3/macos/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        utility.h
        db/Account.cpp
        db/Account.h
        db/Db.cpp
        db/Db.h
        db/User.h
        db/User.cpp
        db/Record.cpp
        db/Record.h
        ui/LoginDialog.cpp
        ui/LoginDialog.h db/Employee.cpp db/Employee.h ui/UserDashboard.cpp ui/UserDashboard.h ui/EmployeeDashboard.cpp ui/EmployeeDashboard.h)

qt_add_executable(Bank
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        )

target_link_libraries(Bank PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Bank PRIVATE sqlite_orm::sqlite_orm)
target_link_libraries(Bank PRIVATE sodium)

set_target_properties(Bank PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER com.idawnlight.banking
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Bank)
endif ()
