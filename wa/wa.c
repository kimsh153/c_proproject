#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

#define REST 0
#define PLAY 1
int main() {
    char map[202][202];
    char map2[202][202];
    int time[202][202];
    char line[202];
    int i;
    int j;
    int cnt;
    int bomber = REST; // 0 -> 휴식
                    // 1 -> 움직임
    int xfourway[4] = { -1, 0, 1, 0 };
    int yfourway[4] = { 0, 1, 0, -1 };
    int R, C, N; // R x C의 사각형 R 세로
    //                            C 가로
    //                            N 초
    // 16918 봄버맨
    scanf("%d%d%d", &R, &C, &N);

    for (i = 0; i < R; i++) {
        scanf("%s", line);
        for (j = 0; j < C; j++) {
            map[i][j] = line[j];
            if (map[i][j] == 'O') {
                time[i][j] = 3;
            }
            else {
                time[i][j] = 999;
            }
        }
        map[i][j] = '\0';
        time[i][j] = 0;
    }




    for (int cnt = N; cnt > 0; cnt--) {
        if (bomber == REST) {
            for (i = 0; i < R; i++) {
                for (j = 0; j < C; j++) {
                    time[i][j] --;
                    if (time[i][j] == 0) {
                        map[i][j] = '.';
                        map[i - 1][j] = '.';
                        map[i][j - 1] = '.';
                        map[i + 1][j] = '.';
                        map[i][j + 1] = '.';
                    }
                }
            }
            bomber = PLAY;
        }
        else if (bomber == PLAY) {
            for (i = 0; i < R; i++) {
                for (j = 0; j < C; j++) {
                    time[i][j] --;
                    if (map[i][j] == '.') {
                        map[i][j] = 'O';
                        time[i][j] = 3;
                    }
                }
            }
            bomber = REST;
        }
    }





    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

}
