project("EinStein")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EinStein)

target_sources( EinStein
    PRIVATE
        "main.cpp"
        "MyAI.cpp"
        "./Board/board.cpp"
        "./Player/PlayerBase/playerBase.cpp"
        "./Player/PlayerAlphaBeta/playerAlphaBeta.cpp"
        "./Player/HYPlayer/HYPlayer.cpp"
)