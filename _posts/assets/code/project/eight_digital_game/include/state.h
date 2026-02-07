#ifndef STATE_H
#define STATE_H

#include <iostream>

// 状态类
typedef class State
{
public:
    State() = default;

    State(std::string node, std::string f_node, int g, int h);

    const std::string get_now_node() const;

    const std::string get_f_node() const;

    const int get_f_value() const;

    const int get_g_value() const;

    const int get_h_value() const;

    void set_now_node(std::string node);

    void set_f_node(std::string f_node);

    void set_f_value(const int f);

    void set_g_value(const int g);

    void set_h_value(const int h);

    void update_f_and_g_value(const std::string &f_node, const int g);

    bool operator<(const State &s) const;

    bool operator==(const State &s) const;

protected:
    std::string m_node;

    std::string m_f_node;

    int m_f_value;

    int m_g_value;

    int m_h_value;

} State;

#endif
