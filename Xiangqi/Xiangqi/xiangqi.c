#include "xiangqi.h"

// 콘솔 커서를 특정 위치로 이동시키는 함수
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 게임 전체를 초기화 하는 함수
void initGame(Board* _board, Player *player1, Player *player2)
{
	initBoard(_board);
	initPlayer(player1, 초);
	initPlayer(player2, 한);
	initAllPiece(player1->pieceSet, player1->teamID);
	initAllPiece(player2->pieceSet, player2->teamID);
	drawBoard(_board);
	drawAllPiece(_board, player1->pieceSet);
	drawAllPiece(_board, player2->pieceSet);
	drawCurser(player1->curser.x, player1->curser.y, player1->curser.colorNum);
}

// 초기 장기판을 그래픽 배열에 저장하는 함수
void initBoard(Board* _board)
{
	for (int i = 0; i < G_BOARD_ROW; i++)
	{
		for (int j = 0; j < G_BOARD_COL; j++)
		{
			// 여백 부분
			if (i < G_ROW_START || i > G_ROW_END || j < G_COL_START || j > G_COL_END)
			{
				_board->graphicBoard[i][j] = L' ';
				continue;
			}

			// 왼쪽 위
			if (i == G_ROW_START && j == G_COL_START)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 오른쪽 위
			else if (i == G_ROW_START && j == G_COL_END)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 왼쪽 아래
			else if (i == G_ROW_END && j == G_COL_START)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 오른쪽 아래
			else if (i == G_ROW_END && j == G_COL_END)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 교차 맨 위
			else if (i == G_ROW_START && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 교차 맨 아래
			else if (i == G_ROW_END && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 교차 맨 왼쪽
			else if (j == G_COL_START && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 교차 맨 오른쪽
			else if (j == G_COL_END && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 교차 양방
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 선 수평
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) != 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 선 수직
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) != 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board->graphicBoard[i][j] = L'';
			}
			// 빈 공간
			else
			{
				_board->graphicBoard[i][j] = L' ';
			}
		}
	}
}

// 장기판을 그리는 함수
void drawBoard(Board* _board)
{
	// 콘솔 커서를 첫 위치로 설정
	gotoxy(0, 0);

	for (int i = 0; i < G_BOARD_ROW; i++)
	{
		for (int j = 0; j < G_BOARD_COL; j++)
		{
			// wchar_t 형의 문자 하나 출력
			putwchar(_board->graphicBoard[i][j]);
		}
		printf("\n");
	}
}

// 플레이어의 값들을 초기화 시키는 함수
void initPlayer(Player* player, int _teamID)
{
	int colorNum;

	switch (_teamID)
	{
	case 초:
		colorNum = BLUE;
		break;
	case 한:
		colorNum = RED;
		break;
	default:
		colorNum = WHITE;
	}

	player->teamID = _teamID;
	initCurser(&player->curser, colorNum);
	initAllPiece(player->pieceSet, player->teamID);
}

// 플레이어의 선택 위치를 표시하는 커서 위치를 초기화 시키는 함수
void initCurser(PointCurser* curser, int _colorNum)
{
	curser->x = G_BOARD_ROW / 2 - 2;
	curser->y = G_BOARD_COL / 2;
	curser->colorNum = _colorNum;
}

// 플레이어의 커서를 이동시키는 함수
void moveCurser(Board* _board, Player* player, int moveDir)
{
	removeCurser(player->curser.x, player->curser.y);
	switch (moveDir)
	{
	case LEFT:
		if (player->curser.x - (G_BOARD_INTERVAL_COL + 1) < G_COL_START)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			break;
		}

		player->curser.x -= (G_BOARD_INTERVAL_COL + 1);
		break;

	case RIGHT:
		if (player->curser.x + (G_BOARD_INTERVAL_COL + 1) > G_COL_END)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			break;
		}

		player->curser.x += (G_BOARD_INTERVAL_COL + 1);
		break;

	case UP:
		if (player->curser.y - (G_BOARD_INTERVAL_ROW + 1) < G_ROW_START)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			break;
		}

		player->curser.y -= (G_BOARD_INTERVAL_ROW + 1);
		break;

	case DOWN:
		if (player->curser.y + (G_BOARD_INTERVAL_ROW + 1) > G_ROW_END)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			break;
		}

		player->curser.y += (G_BOARD_INTERVAL_ROW + 1);
		break;

	default:
		break;
	}

	drawCurser(player->curser.x, player->curser.y, player->curser.colorNum);
}

// 커서를 지우는 함수
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

// 커서를 그리는 함수
void drawCurser(int x, int y, int colorNum)
{
	// 다음에 출력할 텍스트의 색 결정
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

	// 다음에 출력할 텍스트의 색 결정
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

// 플레이어의 입력을 받는 함수
char playerInputKey()
{
	char c;
	if (_kbhit())
	{
		c = _getch();
		// 특수 키: 화살표
		if (c == -32)
		{
			c = _getch();
			return c;
		}
		// 스페이스 바
		else if (c == 32)
		{
			printf("스페이스바\n");
		}
	}
}

// 인자로 받은 말을 초기화 하는 함수
void initPiece(Piece* _piece, wchar_t _type, int _team, int _width, float _score, int _x, int _y)
{
	_piece->pieceType = _type;
	_piece->team = _team;
	_piece->width = _width;
	_piece->score = _score;
	_piece->x = G_COL_START + _x * (G_BOARD_INTERVAL_COL + 1);
	_piece->y = G_ROW_START + _y * (G_BOARD_INTERVAL_ROW + 1);
}

// 팀의 모든 말을 초기화 하는 함수
void initAllPiece(Piece _pieceSet[PIECE_NUM], int team)
{
	if (team == 초)
	{
		// 궁
		initPiece(&_pieceSet[0], L'宮', team, 3, 0.0f, 4, 8);
		// 차
		initPiece(&_pieceSet[1], L'車', team, 2, 13.0f, 0, 9);
		initPiece(&_pieceSet[2], L'車', team, 2, 13.0f, 8, 9);
		// 포
		initPiece(&_pieceSet[3], L'包', team, 2, 7.0f, 1, 7);
		initPiece(&_pieceSet[4], L'包', team, 2, 7.0f, 7, 7);
		// 마
		initPiece(&_pieceSet[5], L'馬', team, 2, 5.0f, 1, 9);
		initPiece(&_pieceSet[6], L'馬', team, 2, 5.0f, 6, 9);
		// 상
		initPiece(&_pieceSet[7], L'象', team, 2, 3.0f, 2, 9);
		initPiece(&_pieceSet[8], L'象', team, 2, 3.0f, 7, 9);
		// 사
		initPiece(&_pieceSet[9], L'士', team, 2, 3.0f, 3, 9);
		initPiece(&_pieceSet[10], L'士', team, 2, 3.0f, 5, 9);
		// 졸
		initPiece(&_pieceSet[11], L'卒', team, 1, 2.0f, 0, 6);
		initPiece(&_pieceSet[12], L'卒', team, 1, 2.0f, 2, 6);
		initPiece(&_pieceSet[13], L'卒', team, 1, 2.0f, 4, 6);
		initPiece(&_pieceSet[14], L'卒', team, 1, 2.0f, 6, 6);
		initPiece(&_pieceSet[15], L'卒', team, 1, 2.0f, 8, 6);
	}
	else if (team == 한)
	{
		// 궁
		initPiece(&_pieceSet[0], L'宮', team, 3, 1.5f, 4, 1);
		// 차
		initPiece(&_pieceSet[1], L'車', team, 2, 13.0f, 0, 0);
		initPiece(&_pieceSet[2], L'車', team, 2, 13.0f, 8, 0);
		// 포
		initPiece(&_pieceSet[3], L'包', team, 2, 7.0f, 1, 2);
		initPiece(&_pieceSet[4], L'包', team, 2, 7.0f, 7, 2);
		// 마
		initPiece(&_pieceSet[5], L'馬', team, 2, 5.0f, 1, 0);
		initPiece(&_pieceSet[6], L'馬', team, 2, 5.0f, 6, 0);
		// 상
		initPiece(&_pieceSet[7], L'象', team, 2, 3.0f, 2, 0);
		initPiece(&_pieceSet[8], L'象', team, 2, 3.0f, 7, 0);
		// 사
		initPiece(&_pieceSet[9], L'士', team, 2, 3.0f, 3, 0);
		initPiece(&_pieceSet[10], L'士', team, 2, 3.0f, 5, 0);
		// 병
		initPiece(&_pieceSet[11], L'兵', team, 1, 2.0f, 0, 3);
		initPiece(&_pieceSet[12], L'兵', team, 1, 2.0f, 2, 3);
		initPiece(&_pieceSet[13], L'兵', team, 1, 2.0f, 4, 3);
		initPiece(&_pieceSet[14], L'兵', team, 1, 2.0f, 6, 3);
		initPiece(&_pieceSet[15], L'兵', team, 1, 2.0f, 8, 3);
	}
}

// 말을 배치하는 함수
void drawPiece(Board* _board, Piece* _piece)
{
	int colorNum;

	switch (_piece->team)
	{
	case 초:
		colorNum = BLUE;
		break;
	case 한:
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

// 팀의 모든 말을 배치하는 함수
void drawAllPiece(Board* _board, Piece _pieceSet[PIECE_NUM])
{
	for (int i = 0; i < PIECE_NUM; i++)
	{
		drawPiece(_board, &_pieceSet[i]);
	}
}



// 경고문을 표시하는 함수
void printAlert(char alertText[])
{
	gotoxy(130, 60);
	printf("%s", alertText);
}