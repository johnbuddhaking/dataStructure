#include "c1.h"
#include <typeinfo>


// 迷宫坐标位置类型
struct PosType{
    int rth;
    int cth;
};


// 全局变量
PosType begin, end;  // 迷宫的入口坐标，出口坐标
// {行增量, 列增量}, 移动方向依次为东南西北
PosType direc[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

#define MAXLENGTH 25  // 设置迷宫最大行列为25
typedef int MazeType[MAXLENGTH][MAXLENGTH];  // 迷宫数组类型[行][列]
MazeType m;  //  迷宫数组
int rows, columns;  // 迷宫行数，列数

void ShowMazeLayout(){
    // 输出迷宫的解：m数组
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){
            printf("%3d", m[i][j]);
        }
        printf("\n");
    }
}

void InitMaze(){
    // set up maze's playout, wall is 0, way is 1
    printf("input maze's rows and columns:");
    scanf("%d %d", &rows, &columns);

    // set left and right wall be 0
    for(int i = 0; i < rows; ++i){
        m[i][0] = 0;
        m[i][columns-1] = 0;
    }

    // set up and down wall be 0
    for(int j = 0; j < columns; ++j){
        m[0][j] = 0;
        m[rows-1][j] = 0;
    }

    // set inside way be 1
    for(int i = 1; i < rows - 1; ++i){
        for(int j = 1; j < columns - 1; ++j){
            m[i][j] = 1;
        }
    }

    printf("input inside wall number:");
    int insideWallNumber;
    scanf("%d", &insideWallNumber);
    printf("input all input inside wall's row_num, column_num:\n");
    for(int i = 0; i < insideWallNumber; ++i){
        int rth, cth;
        scanf("%d %d", &rth, &cth);
        m[rth][cth] = 0;
    }

    printf("the maze's playout is:\n");
    ShowMazeLayout(); 

    printf("input the indoor axis:");
    scanf("%d %d", &begin.rth, &begin.cth);

    printf("input the outdoor axis:");
    scanf("%d %d", &end.rth, &end.cth);
}

// current step, init value is 1 at the indoor
int curstep = 1;

struct SElemType{
    int ord; // way's order
    PosType seat; // way's position
    int di; // next direction
};

#include "sqstack.h"
#include "sqstack_bo.h"

Status canPass(PosType b){
    // wall is 0, way is 1, when test, -1 is blocked
    if(m[b.rth][b.cth] == 1){
        return OK;
    }
    else{
        return ERROR; 
    }
}

void FootPrint(PosType b){
    // make axis b be step
    m[b.rth][b.cth] = curstep;
}

void NextPos(PosType &b, int di){
    b.cth += direc[di].cth;
    b.rth += direc[di].rth;
}

void MarkPrint(PosType b){
    m[b.rth][b.cth] = -1;
}

Status MazePath(PosType start, PosType end){
    // if there has a way from start to end, put the trace in the stack
    // and return TRUE, otherwise teturn FALSE
    PosType curpos = start;
    SqStack s;
    SElemType e;
    InitStack(s);

    // key part
    // StackEmpty(s) 
    // Push(s, e)
    // Pop(s, e)
    // canPass(curpos)
    // FootPrint(curpos)
    // MarkPrint(curpos)
    // NextPos(curpos, di)
    do{
        if(canPass(curpos)){
            // if a new position can through, then foot it
            FootPrint(curpos);

            e.ord = curstep;
            ++curstep;
            e.seat = curpos;
            e.di = 0;
            Push(s, e);

            if(curpos.cth == end.cth && curpos.rth == end.rth){
                return TRUE;
            }
            
            NextPos(curpos, e.di);
        } 
        else{
            if(!StackEmpty(s)){
                // pop the pre position
                Pop(s, e);
                --curstep;

                // if the pre position has detected all directions, mark it
                while(e.di == 3 && !StackEmpty(s)){
                    MarkPrint(e.seat);
                    Pop(s, e);
                    --curstep;
                }
                
                // if the pre position has other directions to detect, change curpos to that axis
                if(e.di < 3){
                    ++e.di;
                    Push(s, e);
                    ++curstep;
                    
                    curpos = e.seat;
                    NextPos(curpos, e.di);
                }
            }
        }
    }while(!StackEmpty(s));

    return FALSE;
}

Status MazePathRecursive(PosType curpos, int curstep){
    if(canPass(curpos)){
        m[curpos.rth][curpos.cth] = curstep;

        if(curpos.cth == end.cth && curpos.rth == end.rth){
            return TRUE;
        }
        
        PosType nextpos0 = curpos;
        PosType nextpos1 = curpos;
        PosType nextpos2 = curpos;
        PosType nextpos3 = curpos;
        NextPos(nextpos0, 0);
        NextPos(nextpos1, 1);
        NextPos(nextpos2, 2);
        NextPos(nextpos3, 3);

        if(MazePathRecursive(nextpos0, curstep + 1)){
            return TRUE;
        }
        else if (MazePathRecursive(nextpos1, curstep + 1)){
            return TRUE;
        }
        else if (MazePathRecursive(nextpos2, curstep + 1)){
            return TRUE;
        }
        else if (MazePathRecursive(nextpos3, curstep + 1)){
            return TRUE;
        }
        else {
            m[curpos.rth][curpos.cth] = -1;
            return FALSE;
        }
    }
    else {
        return ERROR;
    }
}

int main(){
    printf(typeid(m).name());
    printf("\n");

    freopen("maze_input.txt", "r", stdin);
    
    InitMaze();

    if(MazePathRecursive(begin, 1)){
        printf("one of the way from indoor to outdoor is:\n");
        ShowMazeLayout();
    }
    else{
        printf("there is no way from indoor to out door.\n");
    }
    return 0;
}

