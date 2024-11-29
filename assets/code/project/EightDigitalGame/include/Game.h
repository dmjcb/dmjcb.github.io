/*
 * @Description:
 * @Version: 1.0
 * @Author: DaLao
 * @Email: dmjcb@outlook.com
 * @Date: 2022-09-09 23:00:11
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-20 14:13:01
 */
#ifndef GAME_H
#define GAME_H

#include "include/State.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdio>
#include <algorithm>

#include <QMainWindow>
#include <QThread>

// 游戏类
typedef class Game
{
public:
    Game() {}

    Game(std::string startConfiguration, std::string endConfiguration);

    ~Game() {}

    bool IsOdevity(std::string s1, std::string s2);

    void UpdateState(State St);

    int GetNodePos(const std::string &s, const std::vector<State> &v);

    int SetWValue(std::string node);

    void FindPath();

    std::vector<State> mOpenState;

    std::vector<State> mCloseState;

    std::vector<std::string> mPath;

    std::vector<QString> mOpenTable;

    std::vector<QString> mCloseTable;

    // 最初状态
    std::string mStartConfiguration;
    // 最终状态
    std::string mEndConfiguration;

    bool mIsFinished;

    // 可移动路径
    // 0,1,2
    // 3,4,5
    // 6,7,8
    // 代表i能移动到的四个位置(-1代表不可达)
    int mRemoveablePos[9][4] = {
        {-1, -1, 1, 3},
        {-1, 0, 2, 4},
        {-1, -1, 1, 5},
        {-1, 0, 4, 6},
        {1, 3, 5, 7},
        {-1, 2, 4, 8},
        {-1, -1, 3, 7},
        {-1, 4, 6, 8},
        {-1, -1, 5, 7}};

} Game;

#endif
