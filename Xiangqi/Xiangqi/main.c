#include <stdio.h>
#include "xiangqi.h"

int main(int argc, char* argv[])
{
	Board xiangqiBoard;

	initBorad(xiangqiBoard.graphicBoard, G_BOARDROW, G_BOARDCOL);

	for (int i = 0; i < G_BOARDROW; i++)
	{
		for (int j = 0; j < G_BOARDCOL; j++)
		{
			printf("%c", xiangqiBoard.graphicBoard[i][j]);
		}
		printf("\n");
	}

	return 0;
}