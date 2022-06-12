set(CMAKE_PREFIX_PATH "/Users/idawnlight/Qt/6.2.3/macos/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        utility.h
        db/Account.cpp
        db/Account.h
        db/Db.cpp
        db/Db.h
        db/User.h
        db/User.cpp
        db/Record.cpp
        db/Record.h
        db/Config.cpp
        db/Config.h
        ui/LoginDialog.cpp
        ui/LoginDialog.h
        ui/Dashboard.cpp
        ui/Dashboard.h
        utility.cpp
        ui/widgets/DashboardWidget.cpp
        ui/widgets/DashboardWidget.h
        ui/widgets/DashboardWidgetEmployee.cpp
        ui/widgets/DashboardWidgetEmployee.h
        ui/widgets/DashboardWidgetUser.cpp
        ui/widgets/DashboardWidgetUser.h
        ui/widgets/UsersModel.cpp
        ui/widgets/UsersModel.h
        ui/widgets/RecordsModel.cpp
        ui/widgets/RecordsModel.h
        ui/widgets/UserDialog.cpp
        ui/widgets/UserDialog.h
        ui/widgets/DashBoardFinder.cpp
        ui/widgets/DashBoardFinder.h ui/widgets/AccountWidget.cpp ui/widgets/AccountWidget.h ui/widgets/AccountInfoLabel.cpp ui/widgets/AccountInfoLabel.h)

qt_add_executable(Bank
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        )

target_compile_options(Bank PRIVATE -Wall)

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
