add_executable(${PROJECT_NAME}
   mainGUI.c
   dbg.h)

target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS})

target_link_libraries(${PROJECT_NAME} PRIVATE limparTela)
target_link_libraries(${PROJECT_NAME} PRIVATE loginFuncs)
target_link_libraries(${PROJECT_NAME} PRIVATE reservasFuncs)

target_compile_definitions(${PROJECT_NAME} PRIVATE DBG=1)