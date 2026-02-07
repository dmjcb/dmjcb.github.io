#include "include/game.h"

Game::Game(std::string start_config, std::string end_config){
    m_start_config = std::move(start_config);
    m_end_config = std::move(end_config);
}

bool Game::is_odevity(std::string s1, std::string s2){
    int oss = 0;
    int fss = 0;
    for (int i = 1; i < 9; ++i){
        int a = 0;
        int b = 0;
        for (int j = 0; j < i; j++){
            if (s1[j] > s1[i] && s1[i] != '0'){
                a++;
            }
            if (s2[j] > s2[i] && s2[i] != '0'){
                b++;
            }
        }
        oss += a;
        fss += b;
    }
    return oss % 2 == fss % 2;
}

void Game::update_state(State state){
    std::stringstream ss;
    int blank_p = state.get_now_node().find('0');
    for (int i = 0; i < 4; i++){
        if (m_enable_position[blank_p][i] != -1){
            std::string next_s = state.get_now_node();
            std::swap(next_s[m_enable_position[blank_p][i]], next_s[blank_p]);
            if (get_node_position(next_s, m_close_state) == -1){
                int n = get_node_position(next_s, m_open_state);
                // 若该字符串也未在open表中
                if (n == -1){
                    ss << (m_open_table.size() + 1) << ":" << next_s << "不在open表中,加入";

                    m_open_table.push_back(QString::fromStdString(ss.str()));

                    ss.str("");
                    ss.clear();

                    m_open_state.emplace_back(next_s, state.get_now_node(), state.get_g_value() + 1, set_m_w_value(next_s));
                }

                // 否则若经过当前状态可以使路径更优
                else if (state.get_g_value() + 1 < m_open_state[n].get_g_value()){
                    // 将当前状态的节点设为交换后状态的父节点,并更新g值
                    m_open_state[n].update_f_and_g_value(state.get_now_node(), state.get_g_value() + 1);

                    ss << (m_open_table.size() + 1) << ":" << next_s << "在open表中,g值更新为" << (state.get_g_value() + 1);
                    m_open_table.push_back(QString::fromStdString(ss.str()));
                    ss.str("");
                    ss.clear();
                }
            }

            if (next_s == m_end_config){
                m_is_finished = true;
                return;
            }
        }
    }

    m_open_state.erase(find(m_open_state.begin(), m_open_state.end(), state));
    m_close_state.push_back(state);

    ss << (m_open_table.size() + 1) << ":" << state.get_now_node() << "被移除open表";
    m_open_table.push_back(QString::fromStdString(ss.str()));

    ss.str("");
    ss.clear();

    ss << (m_close_table.size() + 1) << ":" << state.get_now_node() << "被加入close表";
    m_close_table.push_back(QString::fromStdString(ss.str()));

    ss.str("");
    ss.clear();
}

int Game::get_node_position(const std::string &s, const std::vector<State> &v)
{
    for (int i = 0, size = v.size(); i < size; ++i)
    {
        if (v[i].get_now_node() == s)
        {
            return i;
        }
    }
    return -1;
}

int Game::set_m_w_value(std::string node)
{
    // 求出当前字符串s的每个元素在s中的下标i与s[i]在node中的下标之差
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        if (i != int(node.find('0')))
        {
            sum += abs(i - int(m_end_config.find(node[i])));
        }
    }
    return sum;
}

void Game::find_path()
{
    if (!is_odevity(m_start_config, m_end_config))
    {
        return;
    }

    m_open_state.emplace_back(m_start_config, " ", 0, 0);

    update_state(m_open_state[0]);

    m_is_finished = false;

    while (!m_open_state.empty())
    {
        if (m_is_finished)
        {
            break;
        }
        std::sort(m_open_state.begin(), m_open_state.end());

        update_state(m_open_state[m_open_state.size() - 1]);
    }

    std::vector<State> path;

    path.insert(path.end(), m_open_state.begin(), m_open_state.end());
    path.insert(path.end(), m_close_state.begin(), m_close_state.end());

    int end_p = get_node_position(m_end_config, path);

    while (path[end_p].get_f_node() != " ")
    {
        m_path.push_back(path[end_p].get_now_node());
        end_p = get_node_position(path[end_p].get_f_node(), path);
    }
    m_path.push_back(m_start_config);
    reverse(m_path.begin(), m_path.end());
}
