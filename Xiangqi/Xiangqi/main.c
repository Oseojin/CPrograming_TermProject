#include "xiangqi.h"

Board xiangqiBoard;
PointCurser player1, player2;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "KOREAN");

	initGame(xiangqiBoard.graphicBoard, &player1, &player2);

	while (1)
	{
		char c = playerInputKey(&player1);
		if (c == '\0')
		{
			continue;
		}
		moveCurser(xiangqiBoard.graphicBoard, &player1, c);
	}

	return 0;
}