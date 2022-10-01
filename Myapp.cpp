#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;
int i,j,k;  //循环变量

typedef struct problem{
    char *character;    //用字符数组存储运算符号序列    
    int *number;        //用整型数组存储运算数序列
} *P,problem;

enum OPERATOR{
    add=1,subtract,multiply,divide
}opt;
enum INT_OR_FT{
    INT=1,FT
}type;

P createProblem(int p_num,int i_num);

int main(int argc,const char* argv[]){
    int p_num,r_num,i_num;    //p_num:number of problems,r_num:random number,i_num:most number of items;
    srand((unsigned)time(NULL));
    cout<<"Please entre the amount of problem:"<<endl;
    while(!(cin>>p_num)||p_num<100000){
        cout<<"Please entre an integer again:"<<endl;
        cin.clear();
    }
    while(!(cout<<"Please entre the number that items should be less than:"<<endl&&cin>>i_num)||i_num>10){
        cout<<"Please entre a suitable number!"<<endl;
        cin.clear();
    }
    createProblem(p_num,i_num);

    return 0;
}

void printProblems(P problems){
    for(i=0;i<;i++){
        for(;;){
            
        }
        cout<<endl;                   
    }
}

P createProblems(int p_num,int i_num){
    P problems;
    problems=(P)malloc(p_num*sizeof(P));
    for(i=0;i<p_num;i++){
        problems[i]=*createOneproblem(i_num);
    }
    return problems;    
}

P createOneproblem(int i_num){
    int r_num=0,r=0;
    P problem=(P)malloc(sizeof(problem));

    while(r_num=((rand()%i_num+1)/1)<2);    //configure the amount of items;
    for(i=0,j=0;j<r_num;j++,i++){
        opt=static_cast<OPERATOR>((rand()%4)+1);
        type=static_cast<INT_OR_FT>((rand()%2)+1);
        switch (opt)
        {
        case add:
            problem->character[i]='+';
            break;
        case subtract:
            problem->character[i]='-';
            break;
        case divide:
            problem->character[i]='÷';
            break;
        case multiply:
            problem->character[i]='x';
            break;
        default:
            break;
        }
        switch (type)
        {
        case INT:
            problem->number[i++]=(rand()%100+1)/1;
            break;
        case FT:
            problem->number[i]=(rand()%100+1)/1;  //molecule
            problem->character[i++]='/';
            problem->number[i++]=(rand()%100+1)/1;  //denominator
            break;
        }
    }
}