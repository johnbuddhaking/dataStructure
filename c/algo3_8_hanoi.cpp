#include "c1.h"
int count = 0; // global variable: move steps

void move(int n, char from, char to){
    printf("the %d step, move %d disk from %c to %c\n", ++count, n, from, to);
}

void hanoi(int diskNum, char x, char y, char z){
    if (diskNum == 1){
        move(diskNum, x, z);
    }
    else {
        hanoi(diskNum - 1, x, z, y);
        move(diskNum, x, z);
        hanoi(diskNum - 1, y, x, z);
    }
}

int main(){
    int n;
    printf("3 tower base is a, b, c. All disk initial in a, move them to c by the help of b.");
    printf("input disk number:");
    scanf("%d", &n);
    hanoi(n, 'a', 'b', 'c');
}
