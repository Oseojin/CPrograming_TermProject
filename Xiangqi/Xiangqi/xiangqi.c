#include "xiangqi.h"

void initBorad(char _pBoard[G_BOARDROW][G_BOARDCOL])
{
	for (int i = 0; i < G_BOARDROW; i++)
	{
		for (int j = 0; j < G_BOARDCOL; j++)
		{
			if (i % 5 == 0 || j % 5 == 0)
			{
				_pBoard[i][j] = 'D';
			}
		}
	}
}