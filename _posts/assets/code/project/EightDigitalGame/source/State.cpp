/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email: dmjcb@outlook.com
 * @Date: 2022-09-09 22:58:24
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-19 18:04:00
 */

#include "include/State.h"

State::State(std::string node, std::string fatherNode, int g, int h)
{
    mNode = std::move(node);
    mFatherNode = std::move(fatherNode);
    mFValue = g + h;
    mGValue = g;
    mHValue = h;
}

const std::string State::GetNowNode() const
{
    return mNode;
}

void State::SetNowNode(std::string node)
{
    mNode = node;
}

const std::string State::GetFatherNode() const
{
    return mFatherNode;
}

void State::SetFatherNode(std::string fatherNode)
{
    mFatherNode = fatherNode;
}

const int State::GetFValue() const
{
    return mFValue;
}

void State::SetFValue(const int f)
{
    mFValue = f;
}

const int State::GetGValue() const
{
    return mGValue;
}

void State::SetGValue(const int g)
{
    mGValue = g;
}

const int State::GetHValue() const
{
    return mHValue;
}

void State::SetHValue(const int h)
{
    mHValue = h;
}

bool State::operator<(const State &s) const
{
    return s.mFValue < mFValue;
}

bool State::operator==(const State &s) const
{
    return s.mNode == mNode;
}

// 更新父节点和g值
void State::UpdateFatherAndGValue(const std::string &fatherNode, const int g)
{
    mFatherNode = fatherNode;
    mFValue = g + mHValue;
    mGValue = g;
}
