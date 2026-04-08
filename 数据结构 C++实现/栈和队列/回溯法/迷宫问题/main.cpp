#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
// 现在用回溯算法实现迷宫找出迷宫的一个解

class offset
{
public:
    offset() : offset_x(0), offset_y(0) {}
    offset(int x, int y) : offset_x(x), offset_y(y) {}
    int offset_x;
    int offset_y;
};

// 定义方向映射
map<int, offset> dirs = {
    {1, offset(0, -1)},
    {2, offset(1, -1)},
    {3, offset(1, 0)},
    {4, offset(1, 1)},
    {5, offset(0, 1)},
    {6, offset(-1, 1)},
    {7, offset(-1, 0)},
    {8, offset(-1, -1)}};

// 先定义一个方向x,y偏移量
class Move
{
public:
    Move(int i)
    {
        dir = i;
        map<int, offset>::iterator it = dirs.find(i);
        if (it == dirs.end())
            return;
        this->offset_x = (*it).second.offset_x;
        this->offset_y = (*it).second.offset_y;
    }
    int dir;
    int offset_x;
    int offset_y;
};

bool SeekPath(vector<vector<int>> &Maze, int x, int y, int end_x, int end_y)
{
    // 越界判断
    if (x < 0 || x >= Maze[0].size() || y < 0 || y >= Maze.size())
        return false;
    // 障碍或已访问
    if (Maze[y][x] == 1 || Maze[y][x] == 3)
        return false;
    // 到达终点
    if (x == end_x && y == end_y)
        return true;

    Maze[y][x] = 3; // 标记已访问
    for (int i = 1; i <= 8; i++)
    {
        Move m(i);
        int x2 = x + m.offset_x;
        int y2 = y + m.offset_y;
        if (SeekPath(Maze, x2, y2, end_x, end_y))
            return true;
    }
    //8个方向全都不行 回溯
    Maze[y][x] = 0;
    return false;
}

int main()
{
    // 0 表示可走，1 表示障碍
    vector<vector<int>> Maze = {
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 1}};
    int start_x = 0, start_y = 0; // 起点
    int end_x = 3, end_y = 4;     // 终点

    Maze[start_y][start_x] = 2; // 标记起点

    bool found = SeekPath(Maze, start_x, start_y, end_x, end_y);

    if (found)
        cout << "找到出口！" << endl;
    else
        cout << "无解。" << endl;

    // 输出路径
    for (auto &row : Maze)
    {
        for (auto cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
    return 0;
}