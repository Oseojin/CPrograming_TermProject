#define _CRT_SECURE_NO_WARNINGS

#include "xiangqi.h"

Board xiangqiBoard;
Player player1, player2;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "KOREAN");

	initGame(&xiangqiBoard, &player1, &player2);

	while (1)
	{
		char c = playerInputKey();

		if (c == '\0')
		{
			continue;
		}
		moveCurser(&xiangqiBoard, &player1, c);
	}

	return 0;
}