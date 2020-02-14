#include "c1.h"
#include <typeinfo>

// 迷宫坐标位置类型
struct PosType{
    int x;
    int y;
};


// 全局变量
PosType begin, end;  // 迷宫的入口坐标，出口坐标
// {行增量, 列增量}, 移动方向依次为东南西北
PosType direc[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

#define MAXLENGTH 25  // 设置迷宫最大行列为25
typedef int MazeType[MAXLENGTH][MAXLENGTH];  // 迷宫数组类型[行][列]
MazeType m;  //  迷宫数组
int x, y;  // 迷宫行数，列数

int main(){
    printf(typeid(m).name());
    printf("\n");
    return 0;
}


