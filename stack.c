//************************************
//"stack.c"
//some functions to operate the stack

#include "gamestruct.h"



void InitGameStack(GAME_STACK_HEAD *S)
{
    if(!(S = (GAME_STACK_HEAD*)malloc(sizeof(GAME_STACK_HEAD))))
    {
        printf("FAILED To CREATE THE STACK!\n");
        exit(0);
    }
    (*S).stack_size = 0;
    S->next = NULL;
}

void PushGameStack(GAME_STACK_HEAD *S, struct game_2048 e)
{
    int i,j;
    GAME_STACK *stack_node;
    if(!(stack_node = (GAME_STACK*)malloc(sizeof(GAME_STACK))))
    {
        printf("FAILED TO CREATE STACK NODE!\n");
        exit(0);
    }
    if(S->stack_size>=5)
    {
        GAME_STACK *temp1 = S->next,*temp2;
        for(i=0;i<3;i++)
        {
            temp1 = temp1->next;
        }
        temp2 = temp1->next;
        temp1->next = NULL;
        free(temp2);
        S->stack_size--;
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            stack_node->data.board[i][j] = e.board[i][j];
    }
    stack_node->data.time = e.time;
    stack_node->data.score = e.score;
    stack_node->next = S->next;
    S->next = stack_node;
    S->stack_size++;
}

void PopGameStack(GAME_STACK_HEAD *S, struct game_2048 *e)
{
    int i,j;
    GAME_STACK *stack_node;
    stack_node = S->next;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            e->board[i][j] = stack_node->data.board[i][j];
    }
    e->time = stack_node->data.time;
    e->score = stack_node->data.score;
    S->next = stack_node->next;
    S->stack_size--;
    free(stack_node);
}
