/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email: dmjcb@outlook.com
 * @Date: 2022-09-09 22:57:33
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-20 01:58:36
 */

#ifndef STATE_H
#define STATE_H

#include <iostream>

// 状态类
typedef class State
{
public:
    State() = default;

    State(std::string node, std::string fatherNode, int g, int h);

    const std::string GetNowNode() const;

    const std::string GetFatherNode() const;

    const int GetFValue() const;

    const int GetGValue() const;

    const int GetHValue() const;

    void SetNowNode(std::string node);

    void SetFatherNode(std::string fatherNode);

    void SetFValue(const int f);

    void SetGValue(const int g);

    void SetHValue(const int h);

    void UpdateFatherAndGValue(const std::string &fatherNode, const int g);

    bool operator<(const State &s) const;

    bool operator==(const State &s) const;

protected:
    std::string mNode;

    std::string mFatherNode;

    int mFValue;

    int mGValue;

    int mHValue;

} State;

#endif
