# Modified_6×7_EinStein_Würfelt_Nicht

## 編譯
### 使用g++指令進行編譯
1. 進入與main.cpp相同層級的資料夾(也就是根資料夾)
2. 輸入以下指令
    ```
    g++ MyAI.cpp ./Board/board.cpp ./Player/PlayerBase/playerBase.cpp ./Player/PlayerAlphaBeta/playerAlphaBeta.cpp ./Player/HYPlayer/HYPlayer.cpp main.cpp --std=c++17 -o test.exe
    ```
3. 會看到在當前目錄下多了test.exe檔案
4. 直接執行test.exe即可

### 使用CMake進行編譯
1. 進入與main.cpp相同層級的資料夾(也就是根資料夾)
2. 創建一個build資料夾
    - mkdir build
3. 進入build資料夾
    - cd build
4. 輸入以下指令
    - cmake ..
    - make
5. 此時在build資料夾下會多出EinStein的執行檔
6. 直接執行EinStein檔案即可

## 架構說明
### Game
遊戲主體，會在一開始的時候創建版面同時開始遊戲流程

### Board
控制棋盤，所有與棋盤相關的資訊與功能皆放在此
- 合法走步
- 移動
- 是否結束
- 等等...

### Player
使用上次作業的PVS進行魔改，將規則更換成符合這次比賽的規則
當中比較大的差異
1. 更換審局函數的計算方法
    - 改為盡快達到終點
    - 不考慮到達終點的數字
    - 計算出的分數會乘上該數字出現的概率
2. 可以吃同顏色的旗子
