#include "xiangqi.h"

// �ܼ� Ŀ���� Ư�� ��ġ�� �̵���Ű�� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� ��ü�� �ʱ�ȭ �ϴ� �Լ�
void initGame(Board* _board, Player *player1, Player *player2)
{
	initBoard(_board);
	initPlayer(player1, ��);
	initPlayer(player2, ��);
	initAllPiece(player1->pieceSet, player1->teamID);
	initAllPiece(player2->pieceSet, player2->teamID);
	drawBoard(_board);
	drawAllPiece(_board, player1->pieceSet);
	drawAllPiece(_board, player2->pieceSet);
	drawCurser(player1->curser.x, player1->curser.y, player1->curser.colorNum);
}

// �ʱ� ������� �׷��� �迭�� �����ϴ� �Լ�
void initBoard(Board* _board)
{
	for (int i = 0; i < G_BOARD_ROW; i++)
	{
		for (int j = 0; j < G_BOARD_COL; j++)
		{
			// ���� �κ�
			if (i < G_ROW_START || i > G_ROW_END || j < G_COL_START || j > G_COL_END)
			{
				_board->graphicBoard[i][j] = L' ';
				continue;
			}

			// ���� ��
			if (i == G_ROW_START && j == G_COL_START)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ������ ��
			else if (i == G_ROW_START && j == G_COL_END)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ���� �Ʒ�
			else if (i == G_ROW_END && j == G_COL_START)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ������ �Ʒ�
			else if (i == G_ROW_END && j == G_COL_END)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ���� �� ��
			else if (i == G_ROW_START && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ���� �� �Ʒ�
			else if (i == G_ROW_END && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ���� �� ����
			else if (j == G_COL_START && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ���� �� ������
			else if (j == G_COL_END && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// ���� ���
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// �� ����
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) != 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// �� ����
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) != 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// �� ����
			else
			{
				_board->graphicBoard[i][j] = L' ';
			}
		}
	}
}

// ������� �׸��� �Լ�
void drawBoard(Board* _board)
{
	// �ܼ� Ŀ���� ù ��ġ�� ����
	gotoxy(0, 0);

	for (int i = 0; i < G_BOARD_ROW; i++)
	{
		for (int j = 0; j < G_BOARD_COL; j++)
		{
			// wchar_t ���� ���� �ϳ� ���
			putwchar(_board->graphicBoard[i][j]);
		}
		printf("\n");
	}
}

// �÷��̾��� ������ �ʱ�ȭ ��Ű�� �Լ�
void initPlayer(Player* player, int _teamID)
{
	int colorNum;

	switch (_teamID)
	{
	case ��:
		colorNum = BLUE;
		break;
	case ��:
		colorNum = RED;
		break;
	default:
		colorNum = WHITE;
	}

	player->teamID = _teamID;
	initCurser(&player->curser, colorNum);
	initAllPiece(player->pieceSet, player->teamID);
}

// �÷��̾��� ���� ��ġ�� ǥ���ϴ� Ŀ�� ��ġ�� �ʱ�ȭ ��Ű�� �Լ�
void initCurser(PointCurser* curser, int _colorNum)
{
	curser->x = G_BOARD_ROW / 2 - 2;
	curser->y = G_BOARD_COL / 2;
	curser->colorNum = _colorNum;
}

// �÷��̾��� Ŀ���� �̵���Ű�� �Լ�
void moveCurser(Board* _board, Player* player, int moveDir)
{
	removeCurser(player->curser.x, player->curser.y);
	switch (moveDir)
	{
	case LEFT:
		if (player->curser.x - (G_BOARD_INTERVAL_COL + 1) < G_COL_START)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
			break;
		}

		player->curser.x -= (G_BOARD_INTERVAL_COL + 1);
		break;

	case RIGHT:
		if (player->curser.x + (G_BOARD_INTERVAL_COL + 1) > G_COL_END)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
			break;
		}

		player->curser.x += (G_BOARD_INTERVAL_COL + 1);
		break;

	case UP:
		if (player->curser.y - (G_BOARD_INTERVAL_ROW + 1) < G_ROW_START)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
			break;
		}

		player->curser.y -= (G_BOARD_INTERVAL_ROW + 1);
		break;

	case DOWN:
		if (player->curser.y + (G_BOARD_INTERVAL_ROW + 1) > G_ROW_END)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
			break;
		}

		player->curser.y += (G_BOARD_INTERVAL_ROW + 1);
		break;

	default:
		break;
	}

	drawCurser(player->curser.x, player->curser.y, player->curser.colorNum);
}

// Ŀ���� ����� �Լ�
void removeCurser(int x, int y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

	gotoxy(x, y);
	putwchar(L'');

	gotoxy(x - 2, y - 1);
	putwchar(L' ');

	gotoxy(x + 2, y - 1);
	putwchar(L' ');

	gotoxy(x - 2, y + 1);
	putwchar(L' ');

	gotoxy(x + 2, y + 1);
	putwchar(L' ');
}

// Ŀ���� �׸��� �Լ�
void drawCurser(int x, int y, int colorNum)
{
	// ������ ����� �ؽ�Ʈ�� �� ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);

	gotoxy(x, y);
	putwchar(L'');

	gotoxy(x - 2, y - 1);
	putwchar(L'');

	gotoxy(x + 2, y - 1);
	putwchar(L'');

	gotoxy(x - 2, y + 1);
	putwchar(L'');

	gotoxy(x + 2, y + 1);
	putwchar(L'');

	// ������ ����� �ؽ�Ʈ�� �� ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

// �÷��̾��� �Է��� �޴� �Լ�
char playerInputKey()
{
	char c;
	if (_kbhit())
	{
		c = _getch();
		// Ư�� Ű: ȭ��ǥ
		if (c == -32)
		{
			c = _getch();
			return c;
		}
		// �����̽� ��
		else if (c == 32)
		{
			printf("�����̽���\n");
		}
	}
}

// ���ڷ� ���� ���� �ʱ�ȭ �ϴ� �Լ�
void initPiece(Piece* _piece, wchar_t _type, int _team, int _width, float _score, int _x, int _y)
{
	_piece->pieceType = _type;
	_piece->team = _team;
	_piece->width = _width;
	_piece->score = _score;
	_piece->x = G_COL_START + _x * (G_BOARD_INTERVAL_COL + 1);
	_piece->y = G_ROW_START + _y * (G_BOARD_INTERVAL_ROW + 1);
}

// ���� ��� ���� �ʱ�ȭ �ϴ� �Լ�
void initAllPiece(Piece _pieceSet[PIECE_NUM], int team)
{
	if (team == ��)
	{
		// ��
		initPiece(&_pieceSet[0], L'��', team, 3, 0.0f, 4, 8);
		// ��
		initPiece(&_pieceSet[1], L'�', team, 2, 13.0f, 0, 9);
		initPiece(&_pieceSet[2], L'�', team, 2, 13.0f, 8, 9);
		// ��
		initPiece(&_pieceSet[3], L'��', team, 2, 7.0f, 1, 7);
		initPiece(&_pieceSet[4], L'��', team, 2, 7.0f, 7, 7);
		// ��
		initPiece(&_pieceSet[5], L'ة', team, 2, 5.0f, 1, 9);
		initPiece(&_pieceSet[6], L'ة', team, 2, 5.0f, 6, 9);
		// ��
		initPiece(&_pieceSet[7], L'��', team, 2, 3.0f, 2, 9);
		initPiece(&_pieceSet[8], L'��', team, 2, 3.0f, 7, 9);
		// ��
		initPiece(&_pieceSet[9], L'��', team, 2, 3.0f, 3, 9);
		initPiece(&_pieceSet[10], L'��', team, 2, 3.0f, 5, 9);
		// ��
		initPiece(&_pieceSet[11], L'��', team, 1, 2.0f, 0, 6);
		initPiece(&_pieceSet[12], L'��', team, 1, 2.0f, 2, 6);
		initPiece(&_pieceSet[13], L'��', team, 1, 2.0f, 4, 6);
		initPiece(&_pieceSet[14], L'��', team, 1, 2.0f, 6, 6);
		initPiece(&_pieceSet[15], L'��', team, 1, 2.0f, 8, 6);
	}
	else if (team == ��)
	{
		// ��
		initPiece(&_pieceSet[0], L'��', team, 3, 1.5f, 4, 1);
		// ��
		initPiece(&_pieceSet[1], L'�', team, 2, 13.0f, 0, 0);
		initPiece(&_pieceSet[2], L'�', team, 2, 13.0f, 8, 0);
		// ��
		initPiece(&_pieceSet[3], L'��', team, 2, 7.0f, 1, 2);
		initPiece(&_pieceSet[4], L'��', team, 2, 7.0f, 7, 2);
		// ��
		initPiece(&_pieceSet[5], L'ة', team, 2, 5.0f, 1, 0);
		initPiece(&_pieceSet[6], L'ة', team, 2, 5.0f, 6, 0);
		// ��
		initPiece(&_pieceSet[7], L'��', team, 2, 3.0f, 2, 0);
		initPiece(&_pieceSet[8], L'��', team, 2, 3.0f, 7, 0);
		// ��
		initPiece(&_pieceSet[9], L'��', team, 2, 3.0f, 3, 0);
		initPiece(&_pieceSet[10], L'��', team, 2, 3.0f, 5, 0);
		// ��
		initPiece(&_pieceSet[11], L'ܲ', team, 1, 2.0f, 0, 3);
		initPiece(&_pieceSet[12], L'ܲ', team, 1, 2.0f, 2, 3);
		initPiece(&_pieceSet[13], L'ܲ', team, 1, 2.0f, 4, 3);
		initPiece(&_pieceSet[14], L'ܲ', team, 1, 2.0f, 6, 3);
		initPiece(&_pieceSet[15], L'ܲ', team, 1, 2.0f, 8, 3);
	}
}

// ���� ��ġ�ϴ� �Լ�
void drawPiece(Board* _board, Piece* _piece)
{
	int colorNum;

	switch (_piece->team)
	{
	case ��:
		colorNum = BLUE;
		break;
	case ��:
		colorNum = RED;
		break;
	default:
		colorNum = WHITE;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);

	for (int i = 0; i <= _piece->width * 2; i++)
	{
		gotoxy(_piece->x - _piece->width * 2, _piece->y - _piece->width + i);
		for (int j = 0; j <= _piece->width * 4; j++)
		{
			if (i == _piece->width)
			{
				if (j == _piece->width * 2 + 1)
				{
					putwchar(_piece->pieceType);
				}
				else if (j == _piece->width / 2 + 1)
				{
					putwchar(L'\0');
				}
				else
				{
					putwchar(L'#');
				}
			}
			else
			{
				putwchar(L'#');
			}
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

// ���� ��� ���� ��ġ�ϴ� �Լ�
void drawAllPiece(Board* _board, Piece _pieceSet[PIECE_NUM])
{
	for (int i = 0; i < PIECE_NUM; i++)
	{
		drawPiece(_board, &_pieceSet[i]);
	}
}



// ����� ǥ���ϴ� �Լ�
void printAlert(char alertText[])
{
	gotoxy(130, 60);
	printf("%s", alertText);
}