#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include "drawtree.h"


//#define __DEBUG__

char *pPrev=NULL;
char *pMid=NULL;

#ifdef __DEBUG__
char prev[]={"abc"};
char mid[]={"cab"};
//char mid[]={"cba"};
//char mid[]={"bac"};
#endif

void help()
{
    printf("drawtree.exe -[n]null prevlist midlist\n example:\n drawtree.exe -null abc bac\n");
}

int buildtree(T_NODE** p,int pb,int pe,int mb,int me)
{
    int prev_begin=0;
    int prev_end=0;
    int mid_begin=0;
    int mid_end=0;
    int i=0;

    if(pb>pe||mb>me)
    {
        *p=NULL;
        return 0;
    }

    *p=(T_NODE*)malloc(sizeof(T_NODE));
    memset((*p),0,sizeof(T_NODE));

    (*p)->id=pPrev[pb];
    for(i=mb;i<me;i++)
    {
        if(pPrev[pb]==pMid[i])
        {
            break;
        }
    }
    i-=mb;
    prev_begin=pb+1;
    prev_end=pb+i;
    mid_begin=mb;
    mid_end=mb+i-1;
    buildtree(&((*p)->left),prev_begin,prev_end,mid_begin,mid_end);

    prev_begin=pb+i+1;
    prev_end=pe;
    mid_begin=mb+i+1;
    mid_end=me;
    buildtree(&((*p)->right),prev_begin,prev_end,mid_begin,mid_end);

    return 0;
}

static int curId=0;
static char buf[50]={0};

static void prev_trave(T_NODE* p)
{
    if(p)
    {
        sprintf(&buf[curId++],"%c",p->id);
        prev_trave(p->left);
        prev_trave(p->right);
    }
}

static void mid_trave(T_NODE* p)
{
    if(p)
    {
        prev_trave(p->left);
        sprintf(&buf[curId++],"%c",p->id);
        prev_trave(p->right);
    }
}

bool calibration(T_NODE* head,char* prev,char* mid)
{

    if(!head)
        return false;

    curId=0;
    memset(buf,0,50);
    prev_trave(head);
#ifdef __DEBUG__
    printf("prev:%s\n",buf);
#endif
    if(strcmp(prev,prev))
        return false;

    curId=0;
    memset(buf,0,50);
    mid_trave(head);
#ifdef __DEBUG__
    printf("mid:%s\n",buf);
#endif
    if(strcmp(mid,buf))
        return false;

    return true;
}

int main(int argc,char* argv[])
{
    T_NODE* head=NULL;
    DRAW_TYPE type;
    int prev_begin=0;
    int prev_end=0;
    int mid_begin=0;
    int mid_end=0;

#ifndef __DEBUG__
    if(argc != 4)
    {
        help();
        return 0;
    }
    else
    {
        if(!strcmp(argv[1],"-null"))
        {
            type = SHOW_NULL;
        }
        else if(!strcmp(argv[1],"-nnull"))
        {
            type = UNSHOW_NULL;
        }
        else
        {
            help();
            return 0;
        }
        pPrev=(char*)malloc(sizeof(strlen(argv[2])+1));
        memset(pPrev,0,(sizeof(strlen(argv[2])+1)));
        strcpy(pPrev,argv[2]);
        prev_begin=0;
        prev_end=strlen(argv[2])-1;


        pMid=(char*)malloc(sizeof(strlen(argv[3])+1));
        memset(pMid,0,(sizeof(strlen(argv[3])+1)));
        strcpy(pMid,argv[3]);
        mid_begin=0;
        mid_end=strlen(argv[3])-1;
    }

#else
        pPrev=(char*)malloc(sizeof(strlen(prev)+1));
        memset(pPrev,0,(sizeof(strlen(prev)+1)));
        strcpy(pPrev,prev);
        prev_begin=0;
        prev_end=strlen(prev)-1;


        pMid=(char*)malloc(sizeof(strlen(mid)+1));
        memset(pMid,0,(sizeof(strlen(mid)+1)));
        strcpy(pMid,mid);
        mid_begin=0;
        mid_end=strlen(mid)-1;
#endif
    buildtree(&head,prev_begin,prev_end,mid_begin,mid_end);
    if(!calibration(head,pPrev,pMid))
    {
        printf("FAIL!!!  can't build binary tree, please check \n");
    }
    else
    {
        drawtree_build_googleAPI_html(head,type,"binarytree_graphic.html");
    }

    return 0;
}
