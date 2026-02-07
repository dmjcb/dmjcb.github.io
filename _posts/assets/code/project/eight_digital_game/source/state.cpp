/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email: dmjcb@outlook.com
 * @Date: 2022-09-09 22:58:24
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-19 18:04:00
 */

#include "include/state.h"

State::State(std::string node, std::string f_node, int g, int h)
{
    m_node = std::move(node);
    m_f_node = std::move(f_node);
    m_f_value = g + h;
    m_g_value = g;
    m_h_value = h;
}

const std::string State::get_now_node() const
{
    return m_node;
}

void State::set_now_node(std::string node)
{
    m_node = node;
}

const std::string State::get_f_node() const
{
    return m_f_node;
}

void State::set_f_node(std::string f_node)
{
    m_f_node = f_node;
}

const int State::get_f_value() const
{
    return m_f_value;
}

void State::set_f_value(const int f)
{
    m_f_value = f;
}

const int State::get_g_value() const
{
    return m_g_value;
}

void State::set_g_value(const int g)
{
    m_g_value = g;
}

const int State::get_h_value() const
{
    return m_h_value;
}

void State::set_h_value(const int h)
{
    m_h_value = h;
}

bool State::operator<(const State &s) const
{
    return s.m_f_value < m_f_value;
}

bool State::operator==(const State &s) const
{
    return s.m_node == m_node;
}

void State::update_f_and_g_value(const std::string &f_node, const int g)
{
    m_f_node = f_node;
    m_f_value = g + m_h_value;
    m_g_value = g;
}
