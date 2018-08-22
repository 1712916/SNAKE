#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<Windows.h>
#include<dos.h>
#include<time.h>

using namespace std;
#define SPEED 2
int HEIGH_CONSOLE, WIDTH_CONSOLE;

void FixConsoleWindow() //hàm cố định màn hình console
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void gotoxy(int x, int y) //Di chuyển trên tọa độ màn hình Console
{
	HANDLE hConsoleOutput;

	COORD Cursor_an_Pos = { x, y }; //các thuộc tính liên quan đến WIN32 API

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);

	//hàm moveto(): là để di chuyển con trỏ trên màn hình đồ họa

	/*void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}*/
}

void DRAWFRAME(int SIZE)
{
	HEIGH_CONSOLE = WIDTH_CONSOLE = SIZE;
	for (int i = 0; i <= WIDTH_CONSOLE; i++)
	{
		cout << "<>";
	}
	cout << endl;
	for (int i = 1; i < HEIGH_CONSOLE-2; i++)
	{
		cout << "<>";
		gotoxy(WIDTH_CONSOLE * 2, i);
		cout << "<>" << endl;
	}
	for (int i = 0; i <= WIDTH_CONSOLE; i++)
	{
		cout << "<>";
	}
	
}
struct SNAKE
{
	char snake;
	int x, y;
};

class C_SNAKE
{

public:
	SNAKE mini_snake[2];
	int scores = 0;
	bool LIVE;
	C_SNAKE(char SYMBOL, int x1, int y1)
	{
		mini_snake[1].snake = SYMBOL;
		mini_snake[1].x = x1;
		mini_snake[1].y = y1;
		LIVE = TRUE;
	}
	void hien(int x,int y)
	{
		gotoxy(x, y);
		cout << mini_snake[1].snake;
	}
	void GAME_SCORE(int x1, int y1)
	{
		gotoxy(x1, y1);
		cout << "SCRORE:" << scores;
		
	}
	int SNAKE_EAT(int x1, int y1)
	{
		if (mini_snake[1].x == x1 && mini_snake[1].y == y1)
		{
			scores++;
			return 1;
		}
		return 0;
	}
	
	void LOSE(char moving)
	{
		switch (moving)
		{
		case 'w':
		{
					if (mini_snake[1].y  == 0)
					 LIVE=FALSE;
		}
		case 's':
		{
					if (mini_snake[1].y + 1 == HEIGH_CONSOLE - 1)
						LIVE = FALSE;
		}
		case 'd':
		{
					if (mini_snake[1].x + 1 == WIDTH_CONSOLE * 2+1) 
						LIVE = FALSE;
		}
		case 'a':
		{
					if (mini_snake[1].x - 1 == 0)
						LIVE = FALSE;
		}
		}

	}
};
/*class C2_SNAKE : public C_SNAKE
{ 
public:
	int is_snake[100][2]; //thay 100=HEIGH_CONSOLE* WIDTH_CONSOLE
	void LOSE()
	{
		
	}
};*/
////////////****HÀM MOVE****//////////////
void up(int x, int &y, char ch_main)
{
	gotoxy(x, y);
	cout << " ";
	y = y - 1;
}
void down(int x, int &y, char ch_main)
{
	gotoxy(x, y);
	cout << " ";
	y = y + 1;
}
void right(int &x, int y, char ch_main)
{
	gotoxy(x, y);
	cout << " ";
	x = x + 1;
}
void left(int &x, int y, char ch_main)
{
	gotoxy(x, y);
	cout << " ";
	x = x - 1;
}
bool move_(char moving, char ch_main, int &x, int &y, int is_snake[100][2], int &n, int n1 = 2)
{
	int after_x = is_snake[n][0], after_y=is_snake[n][1];
	/////////
	for (int i = n; i >= n1; i--)
	{
		is_snake[i][0] = is_snake[i - 1][0];
		is_snake[i][1] = is_snake[i - 1][1];
	}
	
	switch (moving)
	{
		case 'w':
		{
					
					up(x, y, ch_main);
					break;
		}
		case 's':
		{
					
					down(x, y, ch_main);
					break;
		}
		case 'd':
		{
					
					right(x, y, ch_main);
					break;
		}
		case 'a':
		{
					
					left(x, y, ch_main);
					break;
		}
	}
	
	
	gotoxy(x, y);

	cout << ch_main;

	for (int i = 1; i <= n; i++)
	{
		gotoxy(is_snake[i][0], is_snake[i][1]);
		cout << ch_main;
	}
	

	gotoxy(is_snake[n][0], is_snake[n][1]);
	Sleep(1000/4*SPEED);
	cout << " ";
	for (int i = 2; i <= n; i++)
	{
		if (is_snake[1][0] == is_snake[i][0] && is_snake[1][1] == is_snake[i][1])
		{
			return FALSE;
		}
	}
	return TRUE;

}
void startgame()
{
	gotoxy(WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2);
	cout << "START GAME";
	Sleep(1000);
	system("cls");
}

void main()
{
	char SYMBOL = '@';
	int is_snake[100][2];
	int SIZE=WIDTH_CONSOLE = HEIGH_CONSOLE = 20;
	
	C_SNAKE meocon = C_SNAKE(SYMBOL, WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2);
	meocon.LIVE = TRUE;
	SNAKE EAT;

	DRAWFRAME(SIZE);
	startgame();
	DRAWFRAME(SIZE);
	
	srand((unsigned)time(NULL));

	meocon.GAME_SCORE(WIDTH_CONSOLE * 2 + 3, HEIGH_CONSOLE/2);

	EAT.snake = 'o';
	EAT.x = rand() % (2*WIDTH_CONSOLE - 2) + 2 ;
	EAT.y = rand() % (HEIGH_CONSOLE - 3) + 1;

	gotoxy(EAT.x, EAT.y);
	cout << EAT.snake;

	meocon.hien(WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2); //HIỆN RẮN KHI BẮT ĐẦU GAME
	
	char moving='d'; //CHO RẮN ĐI THẲNG TỚI
	char key;

	is_snake[1][0] = meocon.mini_snake[1].x;
	is_snake[1][1] = meocon.mini_snake[1].y;
	
	int sizeof_snake = 0;
	do
	{
		while (!_kbhit() && meocon.LIVE == TRUE)
		{
			sizeof_snake = meocon.scores + 1;

			meocon.mini_snake[1].x = is_snake[1][0];
			meocon.mini_snake[1].y = is_snake[1][1];


			meocon.LOSE(moving); //KIỂM TRA THUA CHƯA
			
		

			if (meocon.LIVE == FALSE)
			{ 
				break;
			}
			

			meocon.LIVE=move_(moving, meocon.mini_snake[1].snake, is_snake[1][0], is_snake[1][1], is_snake, sizeof_snake);
			
	
			if (meocon.LIVE == FALSE)
			{
				break;
			}

			gotoxy(WIDTH_CONSOLE * 2 + 3, 1+HEIGH_CONSOLE / 2); //HIỆN TỌA ĐỒ MỒI
			cout << "TOA DO EAT (x,y): " << "(" << EAT.x << "," << EAT.y << ")";
			for (int i = 1; i < sizeof_snake; i++)
			{ 
				gotoxy(WIDTH_CONSOLE * 2 + 3, 1 + HEIGH_CONSOLE / 2+i);
				cout << is_snake[i][0] << ":" << is_snake[i][1];
			}//KIỂM TRA TỌA DỘ MỒI

			if (meocon.SNAKE_EAT(EAT.x, EAT.y) == 1)
			{
				meocon.GAME_SCORE(WIDTH_CONSOLE * 2 + 3, HEIGH_CONSOLE / 2);

				EAT.x =  rand() % (2 * WIDTH_CONSOLE - 2) + 2;
				EAT.y =  rand() % (HEIGH_CONSOLE - 2) + 1;

				gotoxy(EAT.x, EAT.y);
				cout << EAT.snake;
			}
			
		}

		if (meocon.LIVE == FALSE)
		{
			break;
		}

		moving=key = _getch();

	} while (key != 27 && meocon.LIVE == TRUE);

	
	gotoxy(WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2); //KẾT THÚC GAME
	cout << "HIHI RAN U DAU ROI!!!";
	Sleep(1000);

	_getch();
}