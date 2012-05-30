#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "drawtree.h"


static void mid_trave(T_NODE* node,FILE* fp,T_NODE* parent,int lr,DRAW_TYPE type)
{
    char LR[]={"lr"};

    if(node)
    {
        fprintf(fp,"[{v:'%c', f:'%c<div style=\"color:green; font-style:italic\">%c</div>'}, '%c', ''],\n",node->id,node->id,LR[lr],parent->id);
        mid_trave(node->left,fp,node,0,type);
        mid_trave(node->right,fp,node,1,type);
    }
    else
    {
        if(type==SHOW_NULL)
        {
            fprintf(fp,"[{v:'%c_%c_NULL', f:'<div style=\"color:red; font-style:italic\">NULL</div>'}, '%c', ''],\n",parent->id,LR[lr],parent->id);
        }
    }
}

bool drawtree_build_googleAPI_html(T_NODE* head,DRAW_TYPE type,char* filename)
{
    FILE* fp=NULL;

    if(!head)
        return false;

    fp=fopen(filename,"w");
    if(!fp)
        return false;
    fprintf(fp,STR_BEGEN);
    fprintf(fp,"['%c', '', ''],\n",head->id);

    {
        mid_trave(head->left,fp,head,0,type);
    }
    {
        mid_trave(head->right,fp,head,1,type);
    }
    fprintf(fp,STR_END);

    fclose(fp);

    return true;
}

//char input[]={"865##7##a9##b##"};
//char input[]={"abdf##g##e##ch##j##"};
//char input[]={"abcd#####"};
char input[]={"a#b#c#d#e##"};
int curIndex=0;

bool create_tree(T_NODE** node)
{
    if(curIndex>sizeof(input))
    {
        return false;
    }

    curIndex++;
    if(input[curIndex]!='#')
    {
        (*node)=(T_NODE*)malloc(sizeof(T_NODE));
        memset(*node,0,sizeof(T_NODE));
        (*node)->id=input[curIndex];
        create_tree(&((*node)->left));
        create_tree(&((*node)->right));
    }
    else
    {
        *node=NULL;
    }

    return true;
}

bool create_tree_head(T_NODE** head) 
{

    (*head)=(T_NODE*)malloc(sizeof(T_NODE));
    memset((*head),0,sizeof(T_NODE));
    (*head)->id=input[curIndex];

    create_tree(&(*head)->left);
    create_tree(&(*head)->right);
    return true;
}

/*
int main(int argc,char* argv[])
{
    T_NODE* head=NULL;
    DRAW_TYPE type=SHOW_NULL;

    create_tree_head(&head);
    drawtree_build_googleAPI_html(head,type,"test_1.html");

    return 0;
}
*/
