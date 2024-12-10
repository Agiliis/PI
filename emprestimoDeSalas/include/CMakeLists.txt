add_library(limparTela
    limparTela/limparTela.c
    limparTela/limparTela.h)

add_library(loginFuncs
    loginFuncs/loginFuncs.c
    loginFuncs/loginFuncs.h)

add_library(reservasFuncs
    reservasFuncs/reservasFuncs.c
    reservasFuncs/reservasFuncs.h)

target_include_directories(limparTela PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(loginFuncs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(reservasFuncs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(loginFuncs PUBLIC limparTela)
target_link_libraries(reservasFuncs PUBLIC limparTela)

