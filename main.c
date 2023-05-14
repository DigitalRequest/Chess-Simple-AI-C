#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define size 8
#define blank 'x'

void show_board(char board[size][size]);
int enemy_ai(char board[size][size], int win);
int calc_track(int row, int col, char dir[2], char board[size][size], int win);
int check_movement(char self, char other, int row);

int main()
{
    srand(time(NULL));

    int win = 0;
    char board[size][size] = {
        {'T', 'N', 'B', 'Q', 'K', 'B', 'N', 'T'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'t', 'n', 'b', 'q', 'k', 'b', 'n', 't'},
    };
    char pieces[6] = {'T', 'N', 'B', 'Q', 'K', 'P'};

    printf("To choose your piece, type 2 integers without space in between\n");
    printf("To choose your direction, type 2 chars without space in between\n");
    while (1)
    {
        char piece[2]; // Get the piece on the board
        char dir[2];   // Get the direction to move
        int row, col;  // Row and Column of the board

        // Show the board in the console
        show_board(board);

        printf("Type what piece you want to move (1 Column || 2 Row): ");
        scanf("%s", piece);

        row = piece[0] - '0' - 1;
        col = piece[1] - '0' - 1;

        do
        {
            if (row < 0 || row > 7 && col < 0 || col > 7)
            {
                if (!isupper(board[col][row]) || board[col][row] == blank)
                {
                    printf("Type a *upper letter* piece on the board (1 Row || 2 Column): ");
                    scanf("%s", piece);
                }
                else
                {
                    printf("Type a valid piece on the board (1 Row || 2 Column): ");
                    scanf("%s", piece);
                }

                row = piece[0] - '0' - 1;
                col = piece[1] - '0' - 1;
            }
            else
            {
                break;
            }
        } while (1);

        printf("Now type the direction you want yo move (u/d || l/r): ");
        scanf("%s", dir);

        int track = calc_track(row, col, dir, board, win);
        if (track == 0)
        {
            printf("Sorry, can't attack a piece of the same team as you\n");
            continue;
        }
        win = enemy_ai(board, win);

        if (win == 1)
        {
            printf("You WIN!!!\n");
            return 0;
        }
        else if (win == 2)
        {
            printf("AI WINS!!!\n");
            return 0;
        }
    }
}

void show_board(char board[size][size])
{
    printf("\n      ");
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size + 1; y++)
        {
            if (y < size)
            {
                printf("%c", board[x][y]);
                printf(" ");
            }
            else
                printf("\n      ");
        }
    }
    printf("\n");
}

int enemy_ai(char board[size][size], int win)
{
    int row, col;
    int random;
    int attacked = 0;
    while (1)
    {
        attacked = 0;
        row = rand() % 8;
        col = rand() % 8;

        if (isupper(board[col][row]) || board[col][row] == blank)
        {
            continue;
        }
        else
        {
            if (!check_movement(board[col][row], board[col + 1][row - 1], row) &&
                !check_movement(board[col][row], board[col + 1][row + 1], row) &&
                !check_movement(board[col][row], board[col - 1][row - 1], row) &&
                !check_movement(board[col][row], board[col - 1][row + 1], row) && row > 0)
            {
                continue;
            }
            else
            {
                if (isupper(board[col + 1][row - 1]))
                {
                    board[col + 1][row - 1] = board[col][row];
                    board[col][row] = blank;
                    if (board[col + 1][row - 1] == 'K')
                    {
                        win = 2;
                    }
                }
                else if (isupper(board[col + 1][row + 1]))
                {
                    board[col + 1][row + 1] = board[col][row];
                    board[col][row] = blank;
                    if (board[col + 1][row + 1] == 'K')
                    {
                        win = 2;
                    }
                }
                else if (isupper(board[col - 1][row + 1]))
                {
                    board[col - 1][row + 1] = board[col][row];
                    board[col][row] = blank;
                    if (board[col - 1][row + 1] == 'K')
                    {
                        win = 2;
                    }
                }
                else if (isupper(board[col - 1][row - 1]))
                {
                    board[col - 1][row - 1] = board[col][row];
                    board[col][row] = blank;
                    if (board[col - 1][row - 1] == 'K')
                    {
                        win = 2;
                    }
                }
                else
                {
                    int random = rand() % 4;
                    switch (random)
                    {
                    case 0:
                        if (col < 7 && row > 0 && check_movement(board[col][row], board[col + 1][row - 1], row))
                        {
                            if (board[col + 1][row - 1] == 'K')
                            {
                                win = 2;
                            }
                            board[col + 1][row - 1] = board[col][row];
                            board[col][row] = blank;
                            attacked = 1;
                        }
                        break;
                    case 1:
                        if (col < 7 && row < 7 && check_movement(board[col][row], board[col + 1][row + 1], row))
                        {
                            if (board[col + 1][row + 1] == 'K')
                            {
                                win = 2;
                            }
                            board[col + 1][row + 1] = board[col][row];
                            board[col][row] = blank;
                            attacked = 1;
                        }
                        break;
                    case 2:
                        if (col > 0 && row > 0 && check_movement(board[col][row], board[col - 1][row - 1], row))
                        {
                            if (board[col - 1][row - 1] == 'K')
                            {
                                win = 2;
                            }
                            board[col - 1][row - 1] = board[col][row];
                            board[col][row] = blank;
                            attacked = 1;
                        }
                        break;
                    case 3:
                        if (col > 0 && row < 7 && check_movement(board[col][row], board[col - 1][row + 1], row))
                        {
                            if (board[col - 1][row + 1] == 'K')
                            {
                                win = 2;
                            }
                            board[col - 1][row + 1] = board[col][row];
                            board[col][row] = blank;
                            attacked = 1;
                        }
                        break;
                    }
                }
            }
        }
        if (attacked == 1)
        {
            break;
        }
        else
        {
            continue;
        }
    }
    printf("%d\n", win);
    return win;
}

int calc_track(int row, int col, char dir[2], char board[size][size], int win)
{
    int can_attack;
    if (row >= 0 && row <= 7 && col >= 0 && col <= 7)
    {
        switch (dir[0])
        {
        case 'd':
            if (dir[1] == 'l')
            {
                can_attack = check_movement(board[col][row], board[col + 1][row - 1], row);
                if (can_attack)
                {
                    if (board[col + 1][row - 1] == 'k')
                    {
                        win = 1;
                    }
                    board[col + 1][row - 1] = board[col][row];
                    board[col][row] = blank;
                    return 1;
                }
            }
            else if (dir[1] == 'r')
            {
                can_attack = check_movement(board[col][row], board[col + 1][row + 1], row);
                if (can_attack)
                {
                    if (board[col + 1][row + 1] == 'k')
                    {
                        win = 1;
                    }
                    board[col + 1][row + 1] = board[col][row];
                    board[col][row] = blank;
                    return 1;
                }
            }
            break;
        case 'u':
            if (dir[1] == 'l')
            {
                can_attack = check_movement(board[col][row], board[col - 1][row - 1], row);
                if (can_attack)
                {
                    if (board[col - 1][row - 1] == 'k')
                    {
                        win = 1;
                    }
                    board[col - 1][row - 1] = board[col][row];
                    board[col][row] = blank;
                    return 1;
                }
            }
            else if (dir[1] == 'r')
            {
                can_attack = check_movement(board[col][row], board[col - 1][row + 1], row);
                if (can_attack)
                {
                    if (board[col - 1][row + 1] == 'k')
                    {
                        win = 1;
                    }
                    board[col - 1][row + 1] = board[col][row];
                    board[col][row] = blank;
                    return 1;
                }
            }
            break;
        }
    }

    return 0;
}

int check_movement(char self, char other, int row)
{
    if (isupper(self) && isupper(other) || !isupper(self) && !isupper(other) && other != blank)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}