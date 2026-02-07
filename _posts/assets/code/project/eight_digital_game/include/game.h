/*
 * @Description:
 * @Version: 1.0
 * @Author: DaLao
 * @Email: dmjcb@outlook.com
 * @Date: 2019-09-09 23:00:11
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-20 14:13:01
 */
#ifndef GAME_H
#define GAME_H

#include "include/state.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdio>
#include <algorithm>

#include <QMainWindow>
#include <QThread>

typedef class Game
{
public:
    Game() {}

    Game(std::string start_config, std::string end_config);

    ~Game() {}

    bool is_odevity(std::string s1, std::string s2);

    void update_state(State St);

    int get_node_position(const std::string &s, const std::vector<State> &v);

    int set_m_w_value(std::string node);

    void find_path();

    std::vector<State> m_open_state;

    std::vector<State> m_close_state;

    std::vector<std::string> m_path;

    std::vector<QString> m_open_table;

    std::vector<QString> m_close_table;

    std::string m_start_config;
    std::string m_end_config;

    bool m_is_finished;

    // 可移动路径
    // 0,1,2
    // 3,4,5
    // 6,7,8
    // 代表i能移动到的四个位置(-1代表不可达)
    int m_enable_position[9][4] = {
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
