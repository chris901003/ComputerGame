project("Modified_6x7_EinStein")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EinStein)

target_sources( EinStein
    PRIVATE
        "main.cpp"
        "./Board/board.cpp"
        "./Game/game.cpp"
        "./Player/PlayerBase/playerBase.cpp"
        "./Player/PlayerHuman/playerHuman.cpp"
        "./Player/PlayerRandom/playerRandom.cpp"
        "./Player/PlayerAlphaBeta/playerAlphaBeta.cpp"
)