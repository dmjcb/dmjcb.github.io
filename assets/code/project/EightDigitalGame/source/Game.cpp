#include "include/Game.h"

Game::Game(std::string startConfiguration, std::string endConfiguration)
{
    mStartConfiguration = std::move(startConfiguration);
    mEndConfiguration = std::move(endConfiguration);
}

bool Game::IsOdevity(std::string s1, std::string s2)
{
    int oss = 0;
    int fss = 0;
    for (int i = 1; i < 9; ++i)
    {
        int a = 0;
        int b = 0;
        for (int j = 0; j < i; j++)
        {
            if (s1[j] > s1[i] && s1[i] != '0')
            {
                a++;
            }
            if (s2[j] > s2[i] && s2[i] != '0')
            {
                b++;
            }
        }
        oss += a;
        fss += b;
    }
    return oss % 2 == fss % 2;
}

void Game::UpdateState(State state)
{
    std::stringstream ss;
    int blankPos = state.GetNowNode().find('0');
    for (int i = 0; i < 4; i++)
    {
        if (mRemoveablePos[blankPos][i] != -1)
        {
            std::string nextStr = state.GetNowNode();
            std::swap(nextStr[mRemoveablePos[blankPos][i]], nextStr[blankPos]);
            if (GetNodePos(nextStr, mCloseState) == -1)
            {
                int n = GetNodePos(nextStr, mOpenState);
                // 若该字符串也未在open表中
                if (n == -1)
                {
                    ss << (mOpenTable.size() + 1) << ":" << nextStr << "不在open表中,加入";

                    mOpenTable.push_back(QString::fromStdString(ss.str()));

                    ss.str("");
                    ss.clear();

                    mOpenState.emplace_back(nextStr, state.GetNowNode(), state.GetGValue() + 1, SetWValue(nextStr));
                }

                // 否则若经过当前状态可以使路径更优
                else if (state.GetGValue() + 1 < mOpenState[n].GetGValue())
                {
                    // 将当前状态的节点设为交换后状态的父节点,并更新g值
                    mOpenState[n].UpdateFatherAndGValue(state.GetNowNode(), state.GetGValue() + 1);

                    ss << (mOpenTable.size() + 1) << ":" << nextStr << "在open表中,g值更新为" << (state.GetGValue() + 1);
                    mOpenTable.push_back(QString::fromStdString(ss.str()));
                    ss.str("");
                    ss.clear();
                }
            }

            if (nextStr == mEndConfiguration)
            {
                mIsFinished = true;
                return;
            }
        }
    }

    mOpenState.erase(find(mOpenState.begin(), mOpenState.end(), state));
    mCloseState.push_back(state);

    ss << (mOpenTable.size() + 1) << ":" << state.GetNowNode() << "被移除open表";
    mOpenTable.push_back(QString::fromStdString(ss.str()));

    ss.str("");
    ss.clear();

    ss << (mCloseTable.size() + 1) << ":" << state.GetNowNode() << "被加入close表";
    mCloseTable.push_back(QString::fromStdString(ss.str()));

    ss.str("");
    ss.clear();
}

int Game::GetNodePos(const std::string &s, const std::vector<State> &v)
{
    for (int i = 0, size = v.size(); i < size; ++i)
    {
        if (v[i].GetNowNode() == s)
        {
            return i;
        }
    }
    return -1;
}

int Game::SetWValue(std::string node)
{
    // 求出当前字符串s的每个元素在s中的下标i与s[i]在node中的下标之差
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        if (i != int(node.find('0')))
        {
            sum += abs(i - int(mEndConfiguration.find(node[i])));
        }
    }
    return sum;
}

void Game::FindPath()
{
    if (!IsOdevity(mStartConfiguration, mEndConfiguration))
    {
        return;
    }

    mOpenState.emplace_back(mStartConfiguration, " ", 0, 0);

    UpdateState(mOpenState[0]);

    mIsFinished = false;

    while (!mOpenState.empty())
    {
        if (mIsFinished)
        {
            break;
        }
        std::sort(mOpenState.begin(), mOpenState.end());

        UpdateState(mOpenState[mOpenState.size() - 1]);
    }

    std::vector<State> path;

    path.insert(path.end(), mOpenState.begin(), mOpenState.end());
    path.insert(path.end(), mCloseState.begin(), mCloseState.end());

    int endNodePos = GetNodePos(mEndConfiguration, path);

    while (path[endNodePos].GetFatherNode() != " ")
    {
        mPath.push_back(path[endNodePos].GetNowNode());
        endNodePos = GetNodePos(path[endNodePos].GetFatherNode(), path);
    }
    mPath.push_back(mStartConfiguration);
    reverse(mPath.begin(), mPath.end());
}
