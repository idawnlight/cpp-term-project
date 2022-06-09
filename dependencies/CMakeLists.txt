include(FetchContent)

# You can configure this for your need, presumbably you want speificy a git tag here instead of a branch
FetchContent_Declare(sqliteOrm
  GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
  GIT_TAG        v1.7.1
)

FetchContent_Declare(Sodium
        GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
        GIT_TAG cd8427a30e79901f35a09345884de4b2a596e5ef # HEAD as of 2022-05-28
        )

add_subdirectory(sqlite_orm)
add_subdirectory(libsodium)