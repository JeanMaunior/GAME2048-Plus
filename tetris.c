
#include "gamestruct.h"

int exit_flag = 0;          //�˳���־����tetris()�����м�飬��CheckExit()�иı�


int const random_number[6][16] =    {{2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4},
                                    {2,2,2,2,2,2,2,2,4,4,4,4,4,8,8,8},
                                    {2,2,2,2,2,4,4,4,4,4,8,8,8,8,16,16},
                                    {2,2,2,4,4,4,4,8,8,8,8,16,16,16,32,32},
                                    {2,2,2,4,4,4,8,8,8,8,16,16,16,32,32,64},
                                    {2,2,4,4,8,8,8,8,16,16,16,32,32,64,64,128}};    //������б����ڹ涨���������֣�
                                                                                    //ʹ֮�뵱ǰ�������������ƥ��

int max_num = 0;            //��¼���ϵ��������



/*
�������ܣ��ҵ����ϵ�������֣����ڴ��ļ���ȡ����Ľ��֮��
*/
int FindMax(TERIS_2048 *t)
{
    int i,j;
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            max_num = max(max_num,t->board[i][j]);
        }
    }
}

/*
�������ܣ�����һ���µ��������
*/
void MakeNewBlock(TERIS_2048 *t)
{
    int mode;
    switch(max_num)
    {
    case 0:
    case 2:
    case 4:
        mode = 0;
        break;
    case 8:
        mode = 1;
        break;
    case 16:
        mode = 2;
        break;
    case 32:
        mode = 3;
        break;
    case 64:
        mode = 4;
        break;
    default:
        mode = 5;
        break;
    }
    NEWBLOCK *b;
    b = (NEWBLOCK*)malloc(sizeof(NEWBLOCK));
    b->initial_time = clock();
    srand(time(NULL));
    b->number = random_number[mode][rand()%16];
    b->nb_x = rand()%WIDTH;
    b->nb_y = HEIGHT - 1;
    t->board[b->nb_y][b->nb_x] = b->number;
    t->nb = *b;
}

/*
�������ܣ�ˢ�²����ƽ���
*/
void Display(TERIS_2048 *t)
{
    int i,j;
    NEWBLOCK *nb;
    nb = &(t->nb);
    system("CLS");
    printf("_______________Teris_2048________________\n");
    printf("Rule:\tWhen two number with the same number is next to each other,\n\tthey will merge into one with a twice number.\n");
    printf("Method:\tUse �� �� to control the new block.\n\tThe block will fall down when �� is pressed or time is out.\n\tYou can press\"x\"on the key board to pause or exit\n");
    printf("Time:%5d\nscore:%5d\n",(t->time+clock())/1000,t->score);
    printf("_________________Game_Zone_________________\n");
    printf("___________________________________________\n\n");



    for(i=HEIGHT-1; i>=0; i--)
    {
        printf("|");
        for(j=0; j<WIDTH; j++)
        {

            if(t->board[i][j]==0)
                printf("      |");
            else
                printf("%6d|",t->board[i][j]);
        }
        if(i ==0)
        printf("\n");
        else
        printf("\n------------------------------------------\n");
    }
    printf("___________________________________________\n");


}

/*
�������ܣ�ͨ���ı��²��������ֵ�����������������
�����²���������������
����ֵ�����ڴ˴�������ܹ������������򷵻�1�����򷵻�0
*/
int AutoDown(TERIS_2048 *t)
{
    NEWBLOCK *nb = &(t->nb);
    if(nb->nb_y != 0 && t->board[nb->nb_y-1][nb->nb_x] == 0)
    {
        t->board[nb->nb_y][nb->nb_x] = 0;
        nb->nb_y--;
    }
    t->board[nb->nb_y][nb->nb_x] = nb->number;
    if(nb->nb_y != 0 && t->board[nb->nb_y-1][nb->nb_x] == 0)
        return 0;
    else return 1;
}

/*
�������ܣ�      ȷ���Ƿ��˳���������y/Y(�˳�)�����˳���־exit_flag Ϊ1,
                ������n,�򲻸ı䣻�������������򷴸���ʾ����

*/
void CheckExit(TERIS_2048 *t)
{
    int input;
    do
    {
        do
        {
            Display(t);
            printf("Are you sure to exit?(y/n��");
            Sleep(1000);
        }
        while(!_kbhit());
        input =getch();
        if(input =='y'||input =='Y')
        {
            exit_flag = 1;
            return 0;
        }
    }
    while(input!='n'&&input!='N');

}
/*
***�����㷨***

�������ܣ�
1.�������룬���������ֿ�ÿ�������䣬ֱ�����յ�������䵽��
2.�����յ����룬
    1������Ϊ�����������������з�����ƶ�
    2������Ϊx,����ͣ��ȷ���Ƿ��˳�
����ֵ�������ˡ��¡����������ֿ��Ѿ��䵽�ף��򷵻�1�����򷵻�0��
*/
int Move(TERIS_2048 *t)
{
    int input;
    int down = 0;
    int bottom = 0;     //�ж��Ƿ��Զ����䵽��
    int i,j;
    NEWBLOCK *nb;
    nb = &(t->nb);
    do
    {
        if((clock()-nb->initial_time)%1000 <= 15)
        {
            bottom = AutoDown(t);
            Display(t);
            Sleep(110);
        }
    }
    while((!_kbhit())&&(!bottom));
    if(!bottom)
    {
        input = getch();
        if(input == 224)
        {
            t->board[t->nb.nb_y][t->nb.nb_x] = 0;
            input = getch();
            fflush(stdin);
            switch(input)
            {
            case 75:        //��
                if(nb->nb_x != 0&&t->board[nb->nb_y][nb->nb_x-1]==0)
                    nb->nb_x--;
                break;
            case 77:        //��
                if(nb->nb_x !=WIDTH-1 && t->board[nb->nb_y][nb->nb_x+1]==0)
                    nb->nb_x++;
                break;
            case 80:        //��
                for(i=0; i<HEIGHT; i++)
                {
                    if(t->board[i][nb->nb_x] == 0)
                    {
                        nb->nb_y = i;
                        break;
                    }
                }
                down = 1;
                break;
            }
            t->board[nb->nb_y][nb->nb_x] = nb->number;      //�ƶ�˼·��
                                                            //�������ֿ�ԭ�����Ӧ������0���ı������ֿ�����꣬
                                                            //�ٽ��ı��������Ӧ������Ϊ�����ֿ������
            Display(t);
            Sleep(100);
        }
        else if(input == 'x'||input == 'X')
            CheckExit(t);
    }
    else
        down = 1;

    return down;
}

/*
�������ܣ�����ÿһ���еĿո񣬽��ո��Ϸ��ĸ����������������ƶ�һ��
            ����ÿ�θ�������֮��
*/

void CheckDown(TERIS_2048 *t)
{
    int i,j,k,temp;
    int flag;
    do
    {
        flag = 0;
        for(j=0; j<WIDTH; j++)
        {
            for(i=0; i<HEIGHT-1; i++)
            {
                if(t->board[i][j]==0&&t->board[i+1][j]!=0)
                {
                    flag = 1;
                    for(k=i; k<HEIGHT-1; k++)
                    {
                            temp = t->board[k][j];
                            t->board[k][j] = t->board[k+1][j];
                            t->board[k+1][j] = temp;

                    }
                }
            }
        }
    }
    while(flag != 0);
}

/*
�������ܣ��������ң��������ϼ���Ƿ����������ڵ�������ͬ
            ���У�����кϲ�
����ֵ���������˺ϲ����򷵻�1;���򷵻�0
*/
int AddDown(TERIS_2048 *t)
{
    int flagdown = 0;
    int i,j;
    for(j=0; j<WIDTH; j++)
    {
        for(i=0; i<HEIGHT-1; i++)
        {
            if(t->board[i][j]==t->board[i+1][j]&&t->board[i][j]!=0)
            {
                t->board[i][j]*=2;
                max_num = max(max_num,t->board[i][j]);              //����Ƿ�ı������ֵ
                t->score += t->board[i][j];
                t->board[i+1][j] = 0;                               //�ϲ��취�� �Ƚ���ͬ�����ֿ��ϵ�����Ϊ0�����µ�����Ϊ����
                CheckDown(t);                                       //              �ٽ��ո���
                flagdown = 1;
                Display(t);
                Sleep(100);

            }
        }
    }
    return flagdown;
}

/*
�������ܣ��������ϣ��������м���Ƿ����������ڵ�������ͬ
            ���У�����кϲ�
����ֵ���������˺ϲ����򷵻�1;���򷵻�0
*/
int AddLeft(TERIS_2048 *t)
{
    int flagleft = 0;
    int i,j;
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH-1; j++)
        {
            if(t->board[i][j]==t->board[i][j+1]&&t->board[i][j]!=0)
            {
                t->board[i][j]*=2;
                max_num = max(max_num,t->board[i][j]);
                t->score += t->board[i][j];
                t->board[i][j+1] = 0;
                CheckDown(t);
                flagleft = 1;
                Display(t);
                Sleep(100);
            }
        }
    }
    return flagleft;
}

/*
***�����㷨***
�������ܣ��ó���������������ͬ���ֵİ�һ�����ȼ��ϲ�

**���ȼ�������>��������>����
*/
void Add(TERIS_2048 *t)
{
    int flagdown,flagleft,flag;
    int i,j;
    do
    {
        do
        {
            flagdown = AddDown(t);
        }
        while(flagdown == 1);
        flagleft = AddLeft(t);      //���¼Ӻͣ�ȷ������������ʱ��������Ӻͣ�
                                    //ÿ������Ӻͺ����¼���Ƿ���Լ������¼Ӻ�

    }
    while(flagleft != 0);
}

/*
�������ܣ��ж��Ƿ���Ϸʧ��
*/
int IsGameOver(TERIS_2048 *t)
{
    int i;
    for(i=0; i<WIDTH; i++)
    {
        if(t->board[HEIGHT-1][i] != 0&&t->board[HEIGHT-2][i] != 0)
            return 1;
    }
    return 0;
}

/*
�������ܣ���Ϸʧ�ܺ󣬼�¼���������
*/
void Gameover(TERIS_2048* t)
{
    ITEM* item;
    item = (ITEM*)malloc(sizeof(ITEM));
    printf("\nGame Over!\n");
    printf("Please input your name:(<10characters)\n");
    fgets(item->user_name,LENGTH,stdin);
    item->score = t->score;
}

/*
�������ܣ��½���Ϸ����ʼ�����в���
*/
TERIS_2048* Initial_2048()
{
    TERIS_2048* t;
    t = (TERIS_2048*)malloc(sizeof(TERIS_2048));
    memset(t->board,0,sizeof(t->board));
    t->score = 0;
    t->time = 0;
    return t;
}

/*
***������***
�������ܣ�������Ϸ�������̣������½���Ϸ/��ȡ��Ϸ����Ϸ���У���Ϸ��������Ϸ�˳�
����ֵ������0Ϊ���¿�ʼ��Ϸ������1Ϊ��ȡ�浵������Ϸ����������Ϊ���󣬷���-1
����ֵ��
*/
int tetris(int option)
{
    TERIS_2048 *teris;
    int over = 0;
    int down = 0;
    if(option == 0)
        teris = Initial_2048();
    else if(option == 1)
    {
        teris = (TERIS_2048*)malloc(sizeof(TERIS_2048));
        resume_tetris(teris);
        FindMax(teris);
    }
    else return -1;
    teris->time -= clock();
    MakeNewBlock(teris);
    Display(teris);
    Sleep(100);
    do
    {
        down = Move(teris);
        if(exit_flag == 0)
        {
            Add(teris);
            over = IsGameOver(teris);
            if(down == 1&&over == 0)
            {
                MakeNewBlock(teris);
                down = 0;
            }
            Display(teris);
            Sleep(80);
        }
    }
    while(over != 1 && exit_flag != 1);
    if(over == 1)
    {
        Gameover(teris);
    }

    else if(exit_flag == 1)
    {
        teris->board[teris->nb.nb_y][teris->nb.nb_x] = 0;
        teris->time += clock();
        store_tetris(*teris);
    }

    return 0;
}

