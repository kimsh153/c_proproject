#include <stdio.h>
#include<Windows.h>
#include <time.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#pragma warning(disable : 4996)
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define ENTER 13

int boom_x, boom_y; //폭탄 좌표 기억
int mon_x[4], mon_y[4]; //몬스터 좌표 기억
int boomdelay; //폭탄 사용 딜레이
int Noprint; //출력 겹침 고치기
int clear; //창 지우기
int start; // 게임화면으로 넘어가기
int boom = 1;
int Boomchoice;
int mon = 0, mon2 = 0, mon3 = 0, mon4 = 0;
int Print = 0;
int stage = 0;
int score = 0;
int boomprint = 0;
int high_score[3] = { 00000,00000,00000 };

void sleep() {
	Sleep(27);
}

char wall[22][42];

char to_wall[22][42] = {
	{"111111111111111111111111111111111111111111"},
	{"100000000000000000000000000000000020000001"},
	{"100000000000000000000000000000000242000001"},
	{"100000000000000000000000000000000020000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000001222221000000000000000001"},
	{"100000000000000002000002000000000000000001"},
	{"100000000000000002000002000000000000000001"},
	{"100000000000000002009002000000000000000001"},
	{"100000000000000002000002000000000000000001"},
	{"100000000000000002000002000000000000000001"},
	{"100000000000000001222221000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000001"},
	{"111111111111111111111111111111111111111111"}
};

char stage1_wall[22][42] =
{
	{"111111111111111111111111111111111111111111"},
	{"100000002222221111111111111222222200000001"},
	{"100000002000000000000000000000000200000001"},
	{"100000002000000000000000000000000200000001"},
	{"100000002000000000011100000000000200000001"},
	{"100000002000000000000000000000000200000001"},
	{"100000002000000000000000000000000200000001"},
	{"111112222000000001222221000000000222211111"},
	{"122222000000000002000002000000000000222221"},
	{"111112000000100002000002000010000000211111"},
	{"122222000000100002009002000010000000222221"},
	{"111112000000100002000002000010000000211111"},
	{"122222000000000002000002000000000000222221"},
	{"111112222200000001222221000000022222211111"},
	{"100000000200000000000000000000020000000001"},
	{"100000000200000000000000000000020000000001"},
	{"100000000200000000011100000000020000000001"},
	{"100000000200000000000000000000020000000001"},
	{"100000000222222222222222222222220000000001"},
	{"100000000112221112211221111222110000000001"},
	{"111111111111111111111111111111111111111111"}
};

char Startmap[30][100] =
{
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000900000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000900000000000000000000000000000000000000000000000000"},
	{"0009990009900009990999000999000099900090999900000999099900099900000999000000"},
	{"0090000090090090009000900900900900090099000000009000900090000900009000900000"},
	{"0090000090090090009000900900090999990090000000009000900090999990009000900000"},
	{"0090000090090090009000900900900900000090000000009000900090900909009000900000"},
	{"0009990009900090009000900099000099990090000000009000900090099009009000900000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000000000000000000"}

};
	
void save()
{
	FILE* save;
	save = fopen("save.txt", "w");
	fprintf(save, "%05d %05d %05d", high_score[0], high_score[1], high_score[2]);
	fclose(save);
}

void road()
{
	FILE* road;
	road = fopen("save.txt", "r");
	fscanf(road, "%05d %05d %05d", &high_score[0], &high_score[1], &high_score[2]);
	fclose(road);
}
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; 
	cursorInfo.bVisible = FALSE; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Startprint() {
	gotoxy(0, 0);
	for (int z = 0; z <= 21; z++)
	{
		for (int v = 0; v <= 100; v++)
		{
			if (Startmap[z][v] == '9') {
				printf("#");
			}
			if (Startmap[z][v] == '0')
			{
				printf(" ");
			}
			if (Startmap[z][v] == '2')
				printf(">");
		}
		printf("\n");
	}
	gotoxy(80, 5);
	printf("High Record");
	gotoxy(80, 6);
	int cnt = 0;
	for (int i = 0; i < 3; i++)
	{
		gotoxy(80, cnt + 6);
		cnt++;
		printf("┌────────┐");
		gotoxy(80, cnt + 6);
		cnt++;
		printf("│   %05d│", high_score[i]);
		gotoxy(80, cnt + 6);
		printf("└────────┘");
		cnt++;
	}
	gotoxy(35, 15);
	printf("시작하기 ");
	gotoxy(35, 17);
	printf("게임 설명 ");
	gotoxy(35, 19);
	printf("종료 ");
}

void print() {
	gotoxy(0, 0);
	int cnt = 0;
	for (int z = 0; z <= 21; z++)
	{
		for (int v = 0; v <= 41; v++) {
			if (wall[z][v] == '1')
				printf("■");
			else if (wall[z][v] == '0')
				printf("  ");
			else if (wall[z][v] == '2')
				printf("□");
			else if (wall[z][v] == '6')
				printf("Х");
			else if (wall[z][v] == '5')
				printf("＠");
			else if (wall[z][v] == '9')
				printf("¤");
			else if (wall[z][v] == '7')
				printf("▣");
			else if (wall[z][v] == '8')
				printf("♣");
			else if (wall[z][v] == '3')
				printf("※");
			else if (wall[z][v] == '4')
				printf("Π");
		}
		printf("\n");
	}
	printf("--------------------------------------\n");
	printf("* 만약 화면이 깨진다면 'c'를 누르시오\n");
	printf("--------------------------------------");
	gotoxy(90, 5);
	printf("My score : %d", score);
}

unsigned _stdcall Thread_A(void* arg) {
	boomdelay = 1;
	clock_t start = clock();
	int boomDelete = 0;
	for (;;) {
		clock_t end = clock();
		if ((double)(end - start) / CLOCKS_PER_SEC == 3.006 && boom == 3)
		{
			if (wall[boom_x - 1][boom_y] == '2')
			{
				wall[boom_x - 1][boom_y] = '0';
				score += 50;
			}
			if (boom_x - 1 == mon_x[0] && boom_y == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x - 1 == mon_x[1] && boom_y == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x - 1 == mon_x[2] && boom_y == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x - 1 == mon_x[3] && boom_y == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x - 1][boom_y] != '1' && wall[boom_x - 1][boom_y] != '4')
				wall[boom_x - 1][boom_y] = '3';
			if (wall[boom_x + 1][boom_y] == '2')
			{
				wall[boom_x + 1][boom_y] = '0';
				score += 50;
			}
			if (boom_x + 1 == mon_x[0] && boom_y == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x + 1 == mon_x[1] && boom_y == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x + 1 == mon_x[2] && boom_y == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x + 1 == mon_x[3] && boom_y == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x + 1][boom_y] != '1' && wall[boom_x + 1][boom_y] != '4')
				wall[boom_x + 1][boom_y] = '3';
			if (wall[boom_x][boom_y - 1] == '2')
			{
				wall[boom_x][boom_y - 1] = '0';
				score += 50;
			}
			if (boom_x == mon_x[0] && boom_y - 1 == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x == mon_x[1] && boom_y - 1 == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x == mon_x[2] && boom_y - 1 == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x == mon_x[3] && boom_y - 1 == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x][boom_y - 1] != '1' && wall[boom_x][boom_y - 1] != '4')
				wall[boom_x][boom_y - 1] = '3';
			if (wall[boom_x][boom_y + 1] == '2')
			{
				wall[boom_x][boom_y + 1] = '0';
				score += 50;
			}
			if (boom_x == mon_x[0] && boom_y + 1 == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x == mon_x[1] && boom_y + 1 == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x == mon_x[2] && boom_y + 1 == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x == mon_x[3] && boom_y + 1 == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x][boom_y + 1] != '1' && wall[boom_x][boom_y + 1] != '4')
				wall[boom_x][boom_y + 1] = '3';
			if (wall[boom_x - 1][boom_y + 1] == '2')
			{
				wall[boom_x - 1][boom_y + 1] = '0';
				score += 50;
			}
			if (boom_x - 1 == mon_x[0] && boom_y + 1 == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x - 1 == mon_x[1] && boom_y + 1 == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x - 1 == mon_x[2] && boom_y + 1 == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x - 1 == mon_x[3] && boom_y + 1 == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x - 1][boom_y + 1] != '1' && wall[boom_x - 1][boom_y + 1] != '4')
				wall[boom_x - 1][boom_y + 1] = '3';
			if (wall[boom_x + 1][boom_y - 1] == '2')
			{
				wall[boom_x + 1][boom_y - 1] = '0';
				score += 50;
			}
			if (boom_x + 1 == mon_x[0] && boom_y - 1 == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x + 1 == mon_x[1] && boom_y - 1 == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x + 1 == mon_x[2] && boom_y - 1 == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x + 1 == mon_x[3] && boom_y - 1 == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x + 1][boom_y - 1] != '1' && wall[boom_x - 1][boom_y - 1] != '4')
				wall[boom_x + 1][boom_y - 1] = '3';
			if (wall[boom_x - 1][boom_y - 1] == '2')
			{
				wall[boom_x - 1][boom_y - 1] = '0';
				score += 50;
			}
			if (boom_x - 1 == mon_x[0] && boom_y - 1 == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x - 1 == mon_x[1] && boom_y - 1 == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x - 1 == mon_x[2] && boom_y - 1 == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x - 1 == mon_x[3] && boom_y - 1 == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x - 1][boom_y - 1] != '1' && wall[boom_x - 1][boom_y - 1] != '4')
				wall[boom_x - 1][boom_y - 1] = '3';
			if (wall[boom_x + 1][boom_y + 1] == '2')
			{
				wall[boom_x + 1][boom_y + 1] = '0';
				score += 50;
			}
			if (boom_x + 1 == mon_x[0] && boom_y + 1 == mon_y[0])
			{
				mon = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x + 1 == mon_x[1] && boom_y + 1 == mon_y[1])
			{
				mon2 = 1;
				score += 1000;
				Print = 2;
			}
			if (boom_x + 1 == mon_x[2] && boom_y + 1 == mon_y[2])
			{
				mon3 = 1;
				score += 1000;
				Print = 1;
			}
			if (boom_x + 1 == mon_x[3] && boom_y + 1 == mon_y[3])
			{
				mon4 = 1;
				score += 1000;
				Print = 1;
			}
			if (wall[boom_x + 1][boom_y + 1] != '1' && wall[boom_x + 1][boom_y + 1] != '4')
				wall[boom_x + 1][boom_y + 1] = '3';
			wall[boom_x][boom_y] = '3';
			boomDelete = 1;
			Noprint = 0;
			Sleep(17);
			print();
			Sleep(17);
			Noprint = 1;
			clear = 1;
			break;
		}
		else if ((double)(end - start) / CLOCKS_PER_SEC == 1.506 && boom == 1 || boom == 2) {
			if (boom == 1)
			{
				if (wall[boom_x - 1][boom_y] == '2')
				{
					wall[boom_x - 1][boom_y] = '0';
					score += 50;
				}
				if (boom_x - 1 == mon_x[0] && boom_y == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x - 1 == mon_x[1] && boom_y == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x - 1 == mon_x[2] && boom_y == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x - 1 == mon_x[3] && boom_y == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x - 1][boom_y] != '1' && wall[boom_x - 1][boom_y] != '4')
					wall[boom_x - 1][boom_y] = '3';
				if (wall[boom_x + 1][boom_y] == '2')
				{
					wall[boom_x + 1][boom_y] = '0';
					score += 50;
				}
				if (boom_x + 1 == mon_x[0] && boom_y == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x + 1 == mon_x[1] && boom_y == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x + 1 == mon_x[2] && boom_y == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x + 1 == mon_x[3] && boom_y == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x + 1][boom_y] != '1' && wall[boom_x + 1][boom_y] != '4')
					wall[boom_x + 1][boom_y] = '3';
				if (wall[boom_x][boom_y - 1] == '2')
				{
					wall[boom_x][boom_y - 1] = '0';
					score += 50;
				}
				if (boom_x == mon_x[0] && boom_y - 1 == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x == mon_x[1] && boom_y - 1 == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x == mon_x[2] && boom_y - 1 == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x == mon_x[3] && boom_y - 1 == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x][boom_y - 1] != '1' && wall[boom_x][boom_y - 1] != '4')
					wall[boom_x][boom_y - 1] = '3';
				if (wall[boom_x][boom_y + 1] == '2')
				{
					wall[boom_x][boom_y + 1] = '0';
					score += 50;
				}
				if (boom_x == mon_x[0] && boom_y + 1 == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x == mon_x[1] && boom_y + 1 == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x == mon_x[2] && boom_y + 1 == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x == mon_x[3] && boom_y + 1 == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x][boom_y + 1] != '1' && wall[boom_x][boom_y + 1] != '4')
					wall[boom_x][boom_y + 1] = '3';
				wall[boom_x][boom_y] = '3';
				boomDelete = 1;
				Noprint = 0;
				Sleep(17);
				if (boomprint == 0)
					print();
				Sleep(17);
				Noprint = 1;
				clear = 1;
				break;
			}
			else if ((double)(end - start) / CLOCKS_PER_SEC == 1.506 && boom == 2)
			{
				if (wall[boom_x - 1][boom_y + 1] == '2')
				{
					wall[boom_x - 1][boom_y + 1] = '0';
					score += 50;
				}
				if (boom_x - 1 == mon_x[0] && boom_y + 1 == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x - 1 == mon_x[1] && boom_y + 1 == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x - 1 == mon_x[2] && boom_y + 1 == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x - 1 == mon_x[3] && boom_y + 1 == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x - 1][boom_y + 1] != '1' && wall[boom_x -1][boom_y + 1] != '4')
					wall[boom_x - 1][boom_y + 1] = '3';
				if (wall[boom_x + 1][boom_y - 1] == '2')
				{
					wall[boom_x + 1][boom_y - 1] = '0';
					score += 50;
				}
				if (boom_x + 1 == mon_x[0] && boom_y - 1 == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x + 1 == mon_x[1] && boom_y - 1 == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x + 1 == mon_x[2] && boom_y - 1 == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x + 1 == mon_x[3] && boom_y - 1 == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x + 1][boom_y - 1] != '1' && wall[boom_x + 1][boom_y - 1] != '4')
					wall[boom_x + 1][boom_y - 1] = '3';
				if (wall[boom_x - 1][boom_y - 1] == '2')
				{
					wall[boom_x - 1][boom_y - 1] = '0';
					score += 50;
				}
				if (boom_x - 1 == mon_x[0] && boom_y - 1 == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x - 1 == mon_x[1] && boom_y - 1 == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x - 1 == mon_x[2] && boom_y - 1 == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x - 1 == mon_x[3] && boom_y - 1 == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x - 1][boom_y - 1] != '1' && wall[boom_x - 1][boom_y - 1] != '4')
					wall[boom_x - 1][boom_y - 1] = '3';
				if (wall[boom_x + 1][boom_y + 1] == '2')
				{
					wall[boom_x + 1][boom_y + 1] = '0';
					score += 50;
				}
				if (boom_x + 1 == mon_x[0] && boom_y + 1 == mon_y[0])
				{
					mon = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x + 1 == mon_x[1] && boom_y + 1 == mon_y[1])
				{
					mon2 = 1;
					score += 1000;
					Print = 2;
				}
				if (boom_x + 1 == mon_x[2] && boom_y + 1 == mon_y[2])
				{
					mon3 = 1;
					score += 1000;
					Print = 1;
				}
				if (boom_x + 1 == mon_x[3] && boom_y + 1 == mon_y[3])
				{
					mon4 = 1;
					score += 1000;
					Print = 1;
				}
				if (wall[boom_x + 1][boom_y + 1] != '1' && wall[boom_x + 1][boom_y + 1] != '4')
					wall[boom_x + 1][boom_y + 1] = '3';
				wall[boom_x][boom_y] = '3';
				boomDelete = 1;
				Noprint = 0;
				Sleep(17);
				if (boomprint == 0)
					print();
				Sleep(17);
				Noprint = 1;
				clear = 1;
				break;
			}
		}
	}
	if (boomDelete == 1)
	{
		clock_t start2 = clock();
		for (;;) {
			clock_t end2 = clock();
			if ((double)(end2 - start2) / CLOCKS_PER_SEC == 0.503) {
				if (boom == 1)
				{
					if (wall[boom_x - 1][boom_y] != '1' && wall[boom_x - 1][boom_y] != '4')
						wall[boom_x - 1][boom_y] = '0';
					if (wall[boom_x + 1][boom_y] != '1' && wall[boom_x + 1][boom_y] != '4')
						wall[boom_x + 1][boom_y] = '0';
					if (wall[boom_x][boom_y - 1] != '1' && wall[boom_x][boom_y - 1] != '4')
						wall[boom_x][boom_y - 1] = '0';
					if (wall[boom_x][boom_y + 1] != '1' && wall[boom_x][boom_y + 1] != '4')
						wall[boom_x][boom_y + 1] = '0';
				}
				if (boom == 2)
				{
					if (wall[boom_x - 1][boom_y + 1] != '1' && wall[boom_x - 1][boom_y + 1] != '4')
						wall[boom_x - 1][boom_y + 1] = '0';
					if (wall[boom_x + 1][boom_y + 1] != '1' && wall[boom_x + 1][boom_y + 1] != '4')
						wall[boom_x + 1][boom_y + 1] = '0';
					if (wall[boom_x - 1][boom_y - 1] != '1' && wall[boom_x - 1][boom_y - 1] != '4')
						wall[boom_x - 1][boom_y - 1] = '0';
					if (wall[boom_x + 1][boom_y - 1] != '1' && wall[boom_x + 1][boom_y - 1] != '4')
						wall[boom_x + 1][boom_y - 1] = '0';
				}
				if (boom == 3)
				{
					if (wall[boom_x - 1][boom_y] != '1' && wall[boom_x - 1][boom_y] != '4')
						wall[boom_x - 1][boom_y] = '0';
					if (wall[boom_x + 1][boom_y] != '1' && wall[boom_x + 1][boom_y] != '4')
						wall[boom_x + 1][boom_y] = '0';
					if (wall[boom_x][boom_y - 1] != '1' && wall[boom_x][boom_y - 1] != '4')
						wall[boom_x][boom_y - 1] = '0';
					if (wall[boom_x][boom_y + 1] != '1' && wall[boom_x][boom_y + 1] != '4')
						wall[boom_x][boom_y + 1] = '0';
					if (wall[boom_x - 1][boom_y + 1] != '1' && wall[boom_x - 1][boom_y + 1] != '4')
						wall[boom_x - 1][boom_y + 1] = '0';
					if (wall[boom_x + 1][boom_y + 1] != '1' && wall[boom_x + 1][boom_y + 1] != '4')
						wall[boom_x + 1][boom_y + 1] = '0';
					if (wall[boom_x - 1][boom_y - 1] != '1' && wall[boom_x - 1][boom_y - 1] != '4')
						wall[boom_x - 1][boom_y - 1] = '0';
					if (wall[boom_x + 1][boom_y - 1] != '1' && wall[boom_x + 1][boom_y - 1] != '4')
						wall[boom_x + 1][boom_y - 1] = '0';
				}
				wall[boom_x][boom_y] = '0';
				Noprint = 0;
				Sleep(13);
				if(boomprint == 0)
					print();
				Sleep(19);
				Noprint = 1;
				clear = 1;
				boomDelete = 0;
				boomdelay = 0;
				break;
			}
		}
	}
}

unsigned _stdcall Thread_B(void* arg) {
	int monster_move_random1;
	int monster_move_random2;
	int monster_move_random3;
	int monster_move_random4;
	srand((unsigned)time(NULL));
	while (1)
	{
		Sleep(1813);
		if (mon == 1 && mon2 == 1 && mon3 == 1 && mon4 == 1 && stage == 2)
		{
			stage = 3;
		}
		if (mon == 0)
		{
			if (mon == 0 && Boomchoice == 0)
			{
				monster_move_random1 = rand() % 4 + 1;
				switch (monster_move_random1)
				{
				case 1:
					if (wall[mon_x[0] + 1][mon_y[0]] == '3')
					{
						mon = 1;
					}
					if (mon == 0)
					{
						if (wall[mon_x[0] + 1][mon_y[0]] == '1' || wall[mon_x[0] + 1][mon_y[0]] == '9' || wall[mon_x[0] + 1][mon_y[0]] == '2')
						{
							mon_x[0]--;
						}
						else if (wall[mon_x[0] + 1][mon_y[0]] == '0')
						{
							wall[mon_x[0] + 1][mon_y[0]] = '8';
							wall[mon_x[0]][mon_y[0]] = '0';
						}
						mon_x[0]++;
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 2:
					if (wall[mon_x[0] - 1][mon_y[0]] == '3')
					{
						mon = 1;	
					}
					if (mon == 0)
					{
						if (wall[mon_x[0] - 1][mon_y[0]] == '1' || wall[mon_x[0] - 1][mon_y[0]] == '9' || wall[mon_x[0] - 1][mon_y[0]] == '2')
						{
							mon_x[0]++;
						}
						else if (wall[mon_x[0] - 1][mon_y[0]] == '0')
						{
							wall[mon_x[0] - 1][mon_y[0]] = '8';
							wall[mon_x[0]][mon_y[0]] = '0';
						}
						mon_x[0]--;
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 3:
					if (wall[mon_x[0]][mon_y[0] + 1] == '3')
					{
						mon = 1;
					}
					if (mon == 0)
					{
						if (wall[mon_x[0]][mon_y[0] + 1] == '1' || wall[mon_x[0]][mon_y[0] + 1] == '9' || wall[mon_x[0]][mon_y[0] + 1] == '2')
						{
							mon_y[0]--;
						}
						else if (wall[mon_x[0]][mon_y[0] + 1] == '0')
						{
							wall[mon_x[0]][mon_y[0] + 1] = '8';
							wall[mon_x[0]][mon_y[0]] = '0';
						}
						mon_y[0]++;
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 4:
					if (wall[mon_x[0]][mon_y[0] - 1] == '3')
					{
						mon = 1;
					}
					if (mon == 0)
					{
						if (wall[mon_x[0]][mon_y[0] - 1] == '1' || wall[mon_x[0]][mon_y[0] - 1] == '9' || wall[mon_x[0]][mon_y[0] - 1] == '2')
						{
							mon_y[0]++;
						}
						else if (wall[mon_x[0]][mon_y[0] - 1] == '0')
						{
							wall[mon_x[0]][mon_y[0] - 1] = '8';
							wall[mon_x[0]][mon_y[0]] = '0';
						}
						mon_y[0]--;
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				}
			}
		Sleep(23);
		}
		if(wall[mon_x[1]][mon_y[1]] == '3')
		{
			mon2 = 1;
			Print = 1;
		}
		if (mon2 == 0 && Boomchoice == 0)
		{
			if (wall[mon_x[1]][mon_y[1]] == '3')
			{
				wall[mon_x[1]][mon_y[1]] = '0';
				mon2 = 1;
				Print = 1;
			}
			if (mon2 == 0)
			{
				monster_move_random2 = rand() % 4 + 1;
				switch (monster_move_random2)
				{
				case 1:
					if (wall[mon_x[1] + 1][mon_y[1]] == '3')
					{
						wall[mon_x[1]][mon_y[1]] = '0';
						mon2 = 1;
						break;
					}
					else if (wall[mon_x[1] + 1][mon_y[1]] == '1' || wall[mon_x[1] + 1][mon_y[1]] == '9' || wall[mon_x[1] + 1][mon_y[1]] == '2')
					{
						mon_x[1]--;
					}
					else if (wall[mon_x[1] + 1][mon_y[1]] == '0')
					{
						wall[mon_x[1] + 1][mon_y[1]] = '8';
						wall[mon_x[1]][mon_y[1]] = '0';
					}
					mon_x[1]++;
					if (Print == 1)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 2:
					if (wall[mon_x[1] - 1][mon_y[1]] == '3')
					{
						wall[mon_x[1]][mon_y[1]] = '0';
						mon2 = 1;
						break;
					}
					else if (wall[mon_x[1] - 1][mon_y[1]] == '1' || wall[mon_x[1] - 1][mon_y[1]] == '9' || wall[mon_x[1] - 1][mon_y[1]] == '2')
					{
						mon_x[1]++;
					}
					else if (wall[mon_x[1] - 1][mon_y[1]] == '0')
					{
						wall[mon_x[1] - 1][mon_y[1]] = '8';
						wall[mon_x[1]][mon_y[1]] = '0';
					}
					mon_x[1]--;
					if (Print == 1)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 3:
					if (wall[mon_x[1]][mon_y[1] + 1] == '3')
					{
						wall[mon_x[1]][mon_y[1]] = '0';
						mon2 = 1;
						break;
					}
					else if (wall[mon_x[1]][mon_y[1] + 1] == '1' || wall[mon_x[1]][mon_y[1] + 1] == '9' || wall[mon_x[1]][mon_y[1] + 1] == '2')
					{
						mon_y[1]--;
					}
					else if (wall[mon_x[1]][mon_y[1] + 1] == '0')
					{
						wall[mon_x[1]][mon_y[1] + 1] = '8';
						wall[mon_x[1]][mon_y[1]] = '0';
					}
					mon_y[1]++;
					if (Print == 1)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 4:
					if (wall[mon_x[1]][mon_y[1] - 1] == '3')
					{
						wall[mon_x[1]][mon_y[1]] = '0';
						mon2 = 1;
						break;
					}
					else if (wall[mon_x[1]][mon_y[1] - 1] == '1' || wall[mon_x[1]][mon_y[1] - 1] == '9' || wall[mon_x[1]][mon_y[1] - 1] == '2')
					{
						mon_y[1]++;
					}
					else if (wall[mon_x[1]][mon_y[1] - 1] == '0')
					{
						wall[mon_x[1]][mon_y[1] - 1] = '8';
						wall[mon_x[1]][mon_y[1]] = '0';
					}
					mon_y[1]--;
					if (Print == 1)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				}
			}
		}
		Sleep(37);
		if (wall[mon_x[2]][mon_y[2]] == '3')
		{
			mon3 = 1;
			Print = 1;
		}
		if (mon3 == 0 && Boomchoice == 0)
		{
			if (wall[mon_x[2]][mon_y[2]] == '3')
			{
				wall[mon_x[2]][mon_y[2]] = '0';
				mon3 = 1;
				Print = 1;
			}
			if (mon3 == 0)
			{
				monster_move_random3 = rand() % 4 + 1;
				switch (monster_move_random3)
				{
				case 1:
					if (wall[mon_x[2] + 1][mon_y[2]] == '3')
					{
						wall[mon_x[2]][mon_y[2]] = '0';
						mon3 = 1;
						break;
					}
					else if (wall[mon_x[2] + 1][mon_y[2]] == '1' || wall[mon_x[2] + 1][mon_y[2]] == '9' || wall[mon_x[2] + 1][mon_y[2]] == '2')
					{
						mon_x[2]--;
					}
					else if (wall[mon_x[2] + 1][mon_y[2]] == '0')
					{
						wall[mon_x[2] + 1][mon_y[2]] = '8';
						wall[mon_x[2]][mon_y[2]] = '0';
					}
					mon_x[2]++;
					Noprint = 0;
					sleep();
					if (Boomchoice != 1)
						print();
					sleep();
					Noprint = 1;
					break;
				case 2:
					if (wall[mon_x[2] - 1][mon_y[2]] == '3')
					{
						wall[mon_x[2]][mon_y[2]] = '0';
						mon3 = 1;
						break;
					}
					else if (wall[mon_x[2] - 1][mon_y[2]] == '1' || wall[mon_x[2] - 1][mon_y[2]] == '9' || wall[mon_x[2] - 1][mon_y[2]] == '2')
					{
						mon_x[2]++;
					}
					else if (wall[mon_x[2] - 1][mon_y[2]] == '0')
					{
						wall[mon_x[2] - 1][mon_y[2]] = '8';
						wall[mon_x[2]][mon_y[2]] = '0';
					}
					mon_x[2]--;
					Noprint = 0;
					sleep();
					if (Boomchoice != 1)
						print();
					sleep();
					Noprint = 1;
					break;
				case 3:
					if (wall[mon_x[2]][mon_y[2] + 1] == '3')
					{
						wall[mon_x[2]][mon_y[2]] = '0';
						mon3 = 1;
						break;
					}
					else if (wall[mon_x[2]][mon_y[2] + 1] == '1' || wall[mon_x[2]][mon_y[2] + 1] == '9' || wall[mon_x[2]][mon_y[2] + 1] == '2')
					{
						mon_y[2]--;
					}
					else if (wall[mon_x[2]][mon_y[2] + 1] == '0')
					{
						wall[mon_x[2]][mon_y[2] + 1] = '8';
						wall[mon_x[2]][mon_y[2]] = '0';
					}
					mon_y[2]++;
					Noprint = 0;
					sleep();
					if (Boomchoice != 1)
						print();
					sleep();
					Noprint = 1;
					break;
				case 4:
					if (wall[mon_x[2]][mon_y[2] - 1] == '3')
					{
						wall[mon_x[2]][mon_y[2]] = '0';
						mon3 = 1;
						break;
					}
					else if (wall[mon_x[2]][mon_y[2] - 1] == '1' || wall[mon_x[2]][mon_y[2] - 1] == '9' || wall[mon_x[2]][mon_y[2] - 1] == '2')
					{
						mon_y[2]++;
					}
					else if (wall[mon_x[2]][mon_y[2] - 1] == '0')
					{
						wall[mon_x[2]][mon_y[2] - 1] = '8';
						wall[mon_x[2]][mon_y[2]] = '0';
					}
					mon_y[2]--;
					Noprint = 0;
					sleep();
					if (Boomchoice != 1)
						print();
					sleep();
					Noprint = 1;
					break;
				}
			}
		}
		Sleep(89);
		if (wall[mon_x[3]][mon_y[3]] == '3')
		{
			mon4 = 1;
			Print = 1;
		}
		if (mon4 == 0 && Boomchoice == 0)
		{
			if (wall[mon_x[3]][mon_y[3]] == '3')
			{
				wall[mon_x[3]][mon_y[3]] = '0';
				mon4 = 1;
				Print = 1;
			}
			if (mon4 == 0)
			{
				monster_move_random4 = rand() % 4 + 1;
				switch (monster_move_random4)
				{
				case 1:
					if (wall[mon_x[3] + 1][mon_y[3]] == '3')
					{
						wall[mon_x[3]][mon_y[3]] = '0';
						mon4 = 1;
						break;
					}
					else if (wall[mon_x[3] + 1][mon_y[3]] == '1' || wall[mon_x[3] + 1][mon_y[3]] == '9' || wall[mon_x[3] + 1][mon_y[3]] == '2')
					{
						mon_x[3]--;
					}
					else if (wall[mon_x[3] + 1][mon_y[3]] == '0')
					{
						wall[mon_x[3] + 1][mon_y[3]] = '8';
						wall[mon_x[3]][mon_y[3]] = '0';
					}
					mon_x[3]++;
					if (Print == 2)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 2:
					if (wall[mon_x[3] - 1][mon_y[3]] == '3')
					{
						wall[mon_x[3]][mon_y[3]] = '0';
						mon4 = 1;
						break;
					}
					else if (wall[mon_x[3] - 1][mon_y[3]] == '1' || wall[mon_x[3] - 1][mon_y[3]] == '9' || wall[mon_x[3] - 1][mon_y[3]] == '2')
					{
						mon_x[3]++;
					}
					else if (wall[mon_x[3] - 1][mon_y[3]] == '0')
					{
						wall[mon_x[3] - 1][mon_y[3]] = '8';
						wall[mon_x[3]][mon_y[3]] = '0';
					}
					mon_x[3]--;
					if (Print == 2)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 3:
					if (wall[mon_x[3]][mon_y[3] + 1] == '3')
					{
						wall[mon_x[3]][mon_y[3]] = '0';
						mon4 = 1;
						break;
					}
					else if (wall[mon_x[3]][mon_y[3] + 1] == '1' || wall[mon_x[3]][mon_y[3] + 1] == '9' || wall[mon_x[3]][mon_y[3] + 1] == '2')
					{
						mon_y[3]--;
					}
					else if (wall[mon_x[3]][mon_y[3] + 1] == '0')
					{
						wall[mon_x[3]][mon_y[3] + 1] = '8';
						wall[mon_x[3]][mon_y[3]] = '0';
					}
					mon_y[3]++;
					if (Print == 2)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
					break;
				case 4:
					if (wall[mon_x[3]][mon_y[3] - 1] == '3')
					{
						wall[mon_x[3]][mon_y[3]] = '0';
						mon4 = 1;
						break;
					}
					else if (wall[mon_x[3]][mon_y[3] - 1] == '1' || wall[mon_x[3]][mon_y[3] - 1] == '9' || wall[mon_x[3]][mon_y[3] - 1] == '2')
					{
						mon_y[3]++;
					}
					else if (wall[mon_x[3]][mon_y[3] - 1] == '0')
					{
						wall[mon_x[3]][mon_y[3] - 1] = '8';
						wall[mon_x[3]][mon_y[3]] = '0';
					}
					mon_y[3]--;
					if (Print == 2)
					{
						Noprint = 0;
						sleep();
						if (Boomchoice != 1)
							print();
						sleep();
						Noprint = 1;
					}
				break;
				}
			}
		}
	}
}
int end() {
	mon = 1;
	mon2 = 1;
	mon3 = 1;
	mon4 = 1;
	boomprint = 1;
	Sleep(300);
	system("cls");
	char clear[10][2] = { "C","L","E","A","R","!","!"};
	system("cls");
	gotoxy(19, 10);
	for (int i = 0; i < 7; i++)
	{
		printf("%s", clear[i]);
		Sleep(200);
	}
	gotoxy(19, 11);
	printf("점수 : %d", score);
	Sleep(4000);
	gotoxy(19, 12);
	printf("메인화면으로 이동합니다.");
	Sleep(2000);
	main();
}

int die() {
	mon = 1;
	mon2 = 1;
	mon3 = 1;
	mon4 = 1;
	boomprint = 1;
	Sleep(300);
	char gameover[10][20] = { "G","A","M","E"," ","O","V","E","R" };
	system("cls");
	gotoxy(19, 10);
	for (int i = 0; i < 9; i++)
	{
		printf("%s", gameover[i]);
		Sleep(200);
	}
	Sleep(2000);
	gotoxy(19, 11);
	printf("점수 : %d", score);
	Sleep(2000);
	gotoxy(19, 12);
	printf("메인화면으로 이동합니다.");
	Sleep(2000);
	main();
}

int main() {
	CursorView();
	road();
	system("cls");
	Noprint = 1;
	clear = 0;
	start = 1;
	if (score > high_score[0])
	{
		high_score[2] = high_score[1];
		high_score[1] = high_score[0];
		high_score[0] = score;
	}
	else if (score > high_score[1] && score < high_score[0])
	{
		high_score[2] = high_score[1];
		high_score[1] = score;
	}
	else if (score > high_score[2] && score < high_score[0] && score < high_score[1])
	{
		high_score[2] = score;
	}
	score = 0;
	save();
	char c;
	int mini_stage;
	mini_stage = 0;
	Startmap[15][30] = '2';
	Startmap[17][30] = '0';
	Startmap[19][30] = '0';
	Startprint();
	int up=0, down=0;
	while (start)
	{
		if (_kbhit())
		{
			c = _getch();
			switch (c)
			{
			case UP:
				if (down != 0)
				{
					if (down == 2)
					{
						Startmap[17][30] = '2';
						Startmap[19][30] = '0';
						down = 1;
					}
					else if (down == 1)
					{
						Startmap[15][30] = '2';
						Startmap[17][30] = '0';
						down = 0;
					}
					Startprint();
				}
				break;
			case DOWN:
				if (down != 2)
				{
					if (down == 0)
					{
						Startmap[15][30] = '0';
						Startmap[17][30] = '2';
						down = 1;
					}
					else if (down == 1)
					{
						Startmap[17][30] = '0';
						Startmap[19][30] = '2';
						down = 2;
					}
					Startprint();
				}
				break;
			case ENTER:
				if (down == 1)
				{
					system("cls");
					printf("====================================\n");
					printf("게임 설명\n");
					printf("¤ <- 폭탄(스페이스바로 설치)\n");
					printf("※ <- 폭탄 범위\n");
					printf("■ <- 폭탄으로 부서지지 않는 벽\n");
					printf("□ <- 폭탄으로 부서지는 벽 (부시면 점수 +50)\n");
					printf("＠ <- 플레이어(방향키로 이동)\n");
					printf("♣ <- 몬스터(플레이어와 몬스터가 부딪치면 플레이어가 죽음,폭탄으로 죽일 수 있음 죽이면 점수 + 1000)\n");
					printf("Π <- 다음 스테이지로 가는 문\n");
					printf("게임 플레이 중 Tab키를 누르면 폭탄의 터지는 범위 조정 가능\n");
					printf("====================================\n\n");
					printf("아무키나 눌러서 뒤로 가기...\n");
					c = _getch();
					switch (c)
					{
					default:
						main();
						break;
					}
				}
				if (down == 2)
				{
					system("cls");
					gotoxy(20, 10);
					printf("게임을 종료합니다...");
					Sleep(1000);
					exit(0);
				}
				if (down == 0)
				{
					system("cls");
					start = 0;
					break;
				}
			}
		}
	}
	if (start != 1)
	{
		int x = 10;
		int y = 20;
		wall[x][y] = '5';
		print();
		if (stage == 3)
			mini_stage = stage;
		if (mini_stage == 3)
			stage = mini_stage - 1;
		while (1)
		{
			if (mon == 1 && mon2 == 1 && mon3 == 1 && mon4 == 1 && mini_stage == 3)
			{
				Sleep(100);
				system("cls");
				Sleep(100);
				if (clear == 1)
				{
					system("cls");
					clear = 0;
				}
				if (Noprint == 1)
					print();
				mini_stage = 0;
				end();
				break;
			}
			if (mini_stage == 0)
			{
				strcpy(wall, to_wall);
				x = 10;
				y = 20;
				wall[x][y] = '5';
				system("cls");
				print();
				mini_stage = 1;
			}
			else if (mini_stage == 2)
			{
				strcpy(wall,stage1_wall);
				x = 10;
				y = 20;
				wall[x][y] = '5';
				system("cls");
				print();
				mon_x[0] = 3;
				mon_y[0] = 4;
				wall[mon_x[0]][mon_y[0]] = '8';
				mon_x[1] = 4;
				mon_y[1] = 37;
				wall[mon_x[1]][mon_y[1]] = '8';
				mon_x[2] = 17;
				mon_y[2] = 3;
				wall[mon_x[2]][mon_y[2]] = '8';
				mon_x[3] = 17;
				mon_y[3] = 37;
				wall[mon_x[3]][mon_y[3]] = '8';
				mon = 0;
				mon2 = 0;
				mon3 = 0;
				mon4 = 0;
				_beginthreadex(NULL, 0, Thread_B, 0, 0, NULL);
				print();
				mini_stage = 3;
			}
			if (Boomchoice != 1)
			{
				if (wall[x][y] == '3' || wall[x][y] == '8')
				{
					wall[x][y] = '6';
					Sleep(100);
					system("cls");
					Sleep(100);
					Noprint = 0;
					sleep();
					print();
					sleep();
					Noprint = 1;
					mini_stage = 0;
					die();
				}
				if (_kbhit())
				{
					Sleep(7);
					c = _getch();
					switch (c)
					{
					case LEFT:
						if (wall[x][y - 1] == '4')
						{
							wall[x][y] = '0';
							system("cls");
							gotoxy(17, 10);
							printf("스테이지 클리어!");
							Sleep(1000);
							gotoxy(17, 11);
							printf("점수 : %d", score);
							mini_stage += 1;
							Sleep(1000);
							break;
						}
						else if (wall[x][y - 1] == '3' || wall[x][y - 1] == '8')
						{
							wall[x][y - 1] = '6';
							wall[x][y] = '0';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							mini_stage = 0;
							die();
						}
						else if (wall[x][y - 1] == '1' || wall[x][y - 1] == '9' || wall[x][y - 1] == '2')
						{
							y++;
						}
						else if (wall[x][y] == '9')
						{
							wall[x][y - 1] = '5';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							y--;
							break;
						}
						else if (wall[x][y - 1] == '0')
						{
							wall[x][y - 1] = '5';
							wall[x][y] = '0';
						}
						y--;
						if (clear == 1)
						{
							system("cls");
							clear = 0;
						}
						if (Noprint == 1)
							print();
						break;
					case RIGHT:
						if (wall[x][y + 1] == '4')
						{
							wall[x][y] = '0';
							system("cls");
							gotoxy(17, 10);
							printf("스테이지 클리어!");
							Sleep(1000);
							gotoxy(17, 11);
							printf("점수 : %d", score);
							mini_stage += 1;
							Sleep(1000);
							break;
						}
						else if (wall[x][y + 1] == '3' || wall[x][y + 1] == '8')
						{
							wall[x][y + 1] = '6';
							wall[x][y] = '0';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							mini_stage = 0;
							die();
						}
						if (wall[x][y + 1] == '1' || wall[x][y + 1] == '9' || wall[x][y + 1] == '2')
						{
							y--;
						}
						if (wall[x][y] == '9')
						{
							wall[x][y + 1] = '5';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							y++;
							break;
						}
						if (wall[x][y + 1] == '0')
						{
							wall[x][y + 1] = '5';
							wall[x][y] = '0';
						}
						y++;
						if (clear == 1)
						{
							system("cls");
							clear = 0;
						}
						if (Noprint == 1)
							print();
						break;
					case UP:
						if (wall[x - 1][y] == '4')
						{
							wall[x][y] = '0';
							system("cls");
							gotoxy(17, 10);
							printf("스테이지 클리어!");
							Sleep(1000);
							gotoxy(17, 11);
							printf("점수 : %d", score);
							mini_stage += 1;
							Sleep(1000);
							break;
						}
						else if (wall[x - 1][y] == '3' || wall[x - 1][y] == '8')
						{
							wall[x - 1][y] = '6';
							wall[x][y] = '0';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							mini_stage = 0;
							die();
						}
						else if (wall[x - 1][y] == '1' || wall[x - 1][y] == '2' || wall[x - 1][y] == '9')
							x++;
						else if (wall[x][y] == '9')
						{
							wall[x - 1][y] = '5';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							x--;
							break;
						}
						else if (wall[x - 1][y] == '0')
						{
							wall[x - 1][y] = '5';
							wall[x][y] = '0';
						}
						x--;
						if (clear == 1)
						{
							system("cls");
							clear = 0;
						}
						if (Noprint == 1)
							print();
						break;
					case DOWN:
						if (wall[x + 1][y] == '4')
						{
							wall[x][y] = '0';
							system("cls");
							gotoxy(17, 10);
							printf("스테이지 클리어!");
							Sleep(1000);
							gotoxy(17, 11);
							printf("점수 : %d", score);
							mini_stage += 1;
							Sleep(1000);
							break;
						}
						else if (wall[x + 1][y] == '3' || wall[x + 1][y] == '8')
						{
							wall[x + 1][y] = '6';
							wall[x][y] = '0';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							die();
						}
						if (wall[x + 1][y] == '1' || wall[x + 1][y] == '9' || wall[x + 1][y] == '2')
						{
							x--;
						}
						if (wall[x][y] == '9')
						{
							wall[x + 1][y] = '5';
							if (clear == 1)
							{
								system("cls");
								clear = 0;
							}
							if (Noprint == 1)
								print();
							x++;
							break;
						}
						if (wall[x + 1][y] == '0')
						{
							wall[x + 1][y] = '5';
							wall[x][y] = '0';
						}
						x++;
						if (clear == 1)
						{
							system("cls");
							clear = 0;
						}
						if (Noprint == 1)
							print();
						break;
					case SPACE:
						if (boomdelay == 0)
						{
							wall[x][y] = '9';
							boom_x = x;
							boom_y = y;
							if (Noprint == 1)
								print();
							if (Boomchoice != 1)
								_beginthreadex(NULL, 0, Thread_A, 0, 0, NULL);
						}
						break;
					case 'c':
						system("cls");
						if (Noprint == 1)
							print();
						break;
					case '\t':
						if (boomdelay != 1)
						{
							Boomchoice = 1;
							system("cls");
							gotoxy(30, 11);
							printf("대기중..");
							Sleep(500);
							system("cls");
							printf("==============\n");
							printf("폭탄 선택\n");
							printf("==============\n");
							printf("1.+모양 폭탄\t2.X모양 폭탄\t3.네모모양 폭탄(폭탄이 터질때까지의 대기시간 김!)");
							c = _getch();
							switch (c)
							{
							case '1':
								boom = 1;
								break;
							case '2':
								boom = 2;
								break;
							case '3':
								boom = 3;
								break;
							}
							system("cls");
							gotoxy(30, 11);
							printf("대기중..");
							Sleep(500);
							Boomchoice = 0;
							print();
						}
					}
				}
			}
		}
		return 0;
	}
}