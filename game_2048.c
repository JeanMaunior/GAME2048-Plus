
#include "gamestruct.h"



int moveLeft(int board[SIZE][SIZE])
{
    int i,j,k,score = 0,flag = -1,element,next_element;
    //deal with the element which is not 0
    //if the element is equal to the next_element on the left,
    //add it up and change next_element into 0
    for(i = 0;i < SIZE;i++)
    {
        for(j = 0;j < SIZE;j++)
        {
            element = board[i][j];
            if(element != 0)
            {
                k = j+1;
                while(k < SIZE)
                {
                    next_element = board[i][k];
                    if(next_element != 0)
                    {
                        if(element == next_element)
                        {
                            flag = 0;
                            board[i][j] += board[i][k];
                            score += board[i][j];
                            board[i][k] = 0;
                        }
                        k = SIZE;
                        break;
                    }
                    k++;
                }
            }
        }
    }
    //deal with the element which is 0
    //find the next_element on its right which is not 0
    //change element into next_element and change next_element into 0
    for(i = 0;i < SIZE;i++)
    {
        for(j = 0;j < SIZE-1;j++)
        {
            element = board[i][j];
            if(element == 0)
            {
                k = j+1;
                while(k < SIZE)
                {
                    next_element = board[i][k];
                    if(next_element != 0)
                    {
                        flag = 0;
                        board[i][j] = next_element;
                        board[i][k] = 0;
                        k = SIZE;
                    }
                    k++;
                }
            }
        }
    }
    if(flag != -1)
        return score;
    else
        return -1;
}

int moveRight(int board[SIZE][SIZE])
{
    int i,j,k,score = 0,flag = -1,element,next_element;
    for(i = 0;i < SIZE;i++)
    {
        for(j = SIZE-1;j >= 0;j--)
        {
            element = board[i][j];
            if(element != 0)
            {
                k = j-1;
                while(k >= 0)
                {
                    next_element = board[i][k];
                    if(next_element != 0)
                    {
                        if(element == next_element)
                        {
                            flag = 0;
                            board[i][j] += board[i][k];
                            score += board[i][j];
                            board[i][k] = 0;
                        }
                        k = -1;
                        break;
                    }
                    k--;
                }
            }
        }
    }
    for(i = 0;i < SIZE;i++)
    {
        for(j = SIZE-1;j > 0;j--)
        {
            element = board[i][j];
            if(element == 0)
            {
                k = j-1;
                while(k >= 0)
                {
                    next_element = board[i][k];
                    if(next_element != 0)
                    {
                        flag = 0;
                        board[i][j] = next_element;
                        board[i][k] = 0;
                        k = -1;
                    }
                    k--;
                }
            }
        }
    }
    if(flag != -1)
        return score;
    else
        return -1;
}

int moveDown(int board[SIZE][SIZE])
{
    int i,j,k,score = 0,flag = -1,element,next_element;
    for(i = SIZE-1;i >= 0;i--)
    {
        for(j = 0;j < SIZE;j++)
        {
            element = board[i][j];
            if(element != 0)
            {
                k = i-1;
                while(k >= 0)
                {
                    next_element = board[k][j];
                    if(next_element != 0)
                    {
                        if(board[i][j] == board[k][j])
                        {
                            flag = 0;
                            board[i][j] += board[k][j];
                            score += board[i][j];
                            board[k][j] = 0;
                        }
                        k = 0;
                        break;
                    }
                    k--;
                }
            }
        }
    }
    for(i = SIZE-1;i > 0;i--)
    {
        for(j = 0;j < SIZE;j++)
        {
            element = board[i][j];
            if(element == 0)
            {
                k = i-1;
                while(k >= 0)
                {
                    next_element = board[k][j];
                    if(next_element != 0)
                    {
                        flag = 0;
                        board[i][j] = next_element;
                        board[k][j] = 0;
                        k = 0;
                    }
                    k--;
                }
            }
        }
    }
    if(flag != -1)
        return score;
    else
        return -1;
}

int moveUp(int board[SIZE][SIZE])
{
   int i,j,k,score = 0,flag = -1,element,next_element;
    for(i = 0;i < SIZE;i++)
    {
        for(j = 0;j < SIZE;j++)
        {
            element = board[i][j];
            if(element != 0)
            {
                k = i+1;
                while(k < SIZE)
                {
                    next_element = board[k][j];
                    if(next_element != 0)
                    {
                        if(element == next_element)
                        {
                            flag = 0;
                            board[i][j] += board[k][j];
                            score += board[i][j];
                            board[k][j] = 0;
                        }
                        k = SIZE;
                        break;
                    }
                    k++;
                }
            }
        }
    }
    for(i = 0;i < SIZE-1;i++)
    {
        for(j = 0;j < SIZE;j++)
        {
            element = board[i][j];
            if(element == 0)
            {
                k = i+1;
                while(k < SIZE)
                {
                    next_element = board[k][j];
                    if(next_element != 0)
                    {
                        flag = 0;
                        board[i][j] = next_element;
                        board[k][j] = 0;
                        k = SIZE;
                    }
                    k++;
                }
            }
        }
    }
    if(flag != -1)
        return score;
    else
        return -1;
}

int move_game(int move_dir,int board[SIZE][SIZE])
{
    int score=1;
    switch(move_dir)
    {
        case UP:
            score = moveUp(board);
            break;
        case RIGHT:
            score = moveRight(board);
            break;
        case DOWN:
            score = moveDown(board);
            break;
        case LEFT:
            score = moveLeft(board);
            break;
        default:
            printf("INVALID DIRECTION!\n");
    }
    return score;
}


// gameOver returns 0 if it is possible to make a move on the board
// It returns 1 otherwise.

int gameOver(int board[SIZE][SIZE])
{
    int copy_board[SIZE][SIZE],i,j;
    //in order to avoid changing board when judging whether is gameover or not
    //copy board to another array for judging
    for(i = 0;i < SIZE;i++)
    {
        for(j = 0;j < SIZE;j++)
        {
            copy_board[i][j] = board[i][j];
        }
    }
    if(moveDown(copy_board) == -1 && moveUp(copy_board) == -1 && moveLeft(copy_board) == -1 && moveRight(copy_board) == -1)
        return 1;
    else
        return 0;
}

// boardContains2048 returns 1 if the board contains 2048.
// It returns 0 otherwise.
int boardContains2048(int board[SIZE][SIZE])
{
    int i,j;
    for(i = 0;i < SIZE;i++)
    {
        for(j = 0;j < SIZE;j++)
        {
            if(board[i][j] == 2048)
                return 1;
        }
    }
    return 0;
}

// printBoard displays the board.
void printBoard(int board[SIZE][SIZE])
{
    int i,j;
    printf("+");
    for(j = 0;j < SIZE+1;j++)
    {
        printf("-----");
    }
    printf("+\n");
    for(i = 0;i < SIZE;i++)
    {
        printf("|");
        for(j = 0;j < SIZE;j++)
        {
            if(board[i][j] == 0)
            {
                char a = '.';
                printf("%5c",a);
            }
            else
            {
                 printf("%5d",board[i][j]);
            }
        }
        printf("     |\n\n");
    }
    printf("+");
    for(j = 0;j < SIZE+1;j++)
    {
        printf("-----");
    }
    printf("+\n");
}


// print a help message
void printHelp(void)
{
    printf("Enter �� for left, �� for down, �� for up, �� for right, q to quit\n");
}


// add a new number to the board
// it will either be a 2 (90% probability) or a 4 (10% probability)
void insertNewNumber(int board[SIZE][SIZE])
{
    int row, column;
    int random_number, vacantSquares = 0;
    // count vacant squares
    srand(time(NULL));
    for (row = 0; row < SIZE; row = row + 1)
    {
        for (column = 0; column < SIZE; column = column + 1)
        {
            if (board[row][column] == 0)
            {
                vacantSquares++;
            }
        }
    }
    if (vacantSquares == 0)
    {
        printf("Internal error no available square\n");
        exit(1);
    }
    // randomly pick a vacant square
    random_number = rand() % vacantSquares;
    for (row = 0; row < SIZE; row = row + 1)
    {
        for (column = 0; column < SIZE; column = column + 1)
        {
            if (board[row][column] == 0)
            {
                if (random_number == 0)
                {
                    if (rand() % 10 == 0)
                        board[row][column] = 4;
                    else
                        board[row][column] = 2;
                    return;
                }
                random_number--;
            }
        }
    }
}

int input()
{
    int c;
    c = getch();
    while (c != EOF && isspace(c))      //isspace: if c is an empty char,return 1
    {
        c = getch();
    }
    if(c == 224)
    {
        c = getch();
    }
    return c;
}

void game_2048(int player)
{
    GAME_2048 game;
    int i,j,c, Current_Score, Whether_Won=0, Wheter_auto;
    long time1,time2;
    game.score = 0;
    game.time = 0;
    for(i = 0;i < SIZE;i++)
    {
        for(j = 0;j < SIZE;j++)
            game.board[i][j] = 0;
    }
    insertNewNumber(game.board);
    printHelp();
    printBoard(game.board);
    printf("Your score is %d.\n", game.score);
    while (gameOver(game.board) == 0)
    {
        if (Whether_Won == 0 && boardContains2048(game.board))
        {
            Whether_Won = 1;
            printf("Congratulations you've won the game - q to quit or you can keep going\n");
        }
        printf("> ");
        time1 = time(NULL);

        if(player==0)                   //choose player
            c = input();
        else if(player==1)
        {
            c = DFS(game.board);
            //Sleep(100);
        }

        time2 = time(NULL);

        game.time += time2 - time1;
        system("cls");
        printf("\n");
        if (c == EOF || c == 'q' || c == 'Q')
        {
            printf("your final score was %d.\n", game.score);
        }
        if (c != 80 && c != 72 && c != 75 && c != 77)
        {
            printHelp();
        }
        else
        {
            Current_Score = 0;
            if (c == 75)
            {
                Current_Score = moveLeft(game.board);
                if(Current_Score == -1)
                    printf("�� is not a legal move in the current position.\n");
            }
            else if (c == 80)
            {
                Current_Score = moveDown(game.board);
                if(Current_Score == -1)
                    printf("�� is not a legal move in the current position.\n");
            }
            else if (c == 72)
            {
                Current_Score = moveUp(game.board);
                if(Current_Score == -1)
                    printf("�� is not a legal move in the current position.\n");
            }
            else if (c == 77)
            {
                Current_Score = moveRight(game.board);
                if(Current_Score == -1)
                    printf("�� is not a legal move in the current position.\n");
            }
            if (Current_Score != -1)
            {
                insertNewNumber(game.board);
                game.score = game.score + Current_Score;
            }
        }
        printBoard(game.board);
        printf("Your score is %d.\n", game.score);
        printf("Your used time is %ld seconds.\n",game.time);
    }
    system("cls");
    printBoard(game.board);
    printf("Game over - your final score is %d,total time is %ld seconds.\n", game.score,game.time);
}


