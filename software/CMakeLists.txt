cmake_minimum_required(VERSION 3.16)

project(Desafio_I LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Desafio_I
    main.cpp
    src/bits.cpp
    src/azar.cpp
    src/tablero.cpp
    src/mostrar.cpp
    src/combinaciones.cpp
    src/eliminacion.cpp
    src/cascadas.cpp
    src/redimension.cpp
    src/estado.cpp
    include/bits.h
    include/azar.h
    include/tablero.h
    include/mostrar.h
    include/combinaciones.h
    include/eliminacion.h
    include/cascadas.h
    include/redimension.h
    include/estado.h
)

include(GNUInstallDirs)
install(TARGETS Desafio_I
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
