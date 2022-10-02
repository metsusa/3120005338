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
    int cLen,nLen;
} *P,problem;

enum OPERATOR{
    add=1,subtract,multiply,divide
}opt;
enum INT_OR_FT{
    I=1,F
}type;

P createProblems(int p_num,int i_num);
problem createOneproblem(int p_num);
void printProblems(P problems,int p_num);

int main(int argc,const char* argv[]){
    int p_num,r_num,i_num;    //p_num:number of problems,r_num:random number,i_num:most number of items;
    P problems;         //store the created problems;

    srand((unsigned)time(NULL));
    cout<<"Please entre the amount of problem:"<<endl;
    while(!(cin>>p_num)||p_num>=100000){
        cout<<"Please entre an integer again:"<<endl;
        cin.clear();
    }
    while(!(cout<<"Please entre the number that items should be less than:"<<endl&&cin>>i_num)||i_num>10){
        cout<<"Please entre a suitable number!"<<endl;
        cin.clear();
    }
    cout<<"p_num is:"<<p_num<<'\t'<<"i_num is:"<<i_num<<endl;
    problems=createProblems(p_num,i_num);
    cout<<sizeof(problems)<<endl;
    printProblems(problems,p_num);

    return 0;
}

void printProblems(P problems,int p_num){
    for(i=0;i<p_num;i++){
        for(j=0,k=0;j<problems->cLen;){
            cout<<problems->number[k++];
            cout<<problems->character[j++];
            cout<<problems->number[k++];
        }
        cout<<endl;                   
    }
}

P createProblems(int p_num,int i_num){
    P problems;
    // srand((unsigned)time(NULL));
    problems=(P)malloc(p_num*sizeof(P));
    // cout<<"bp1";
    cout<<"p_num is:"<<p_num<<'\t'<<"i_num is:"<<i_num<<endl;
    for(i=0;i<p_num;i++){
        problems[i]=createOneproblem(i_num);
        // printf("%d\n",i);
        cout<<"now I've created "<<i<<" problems"<<endl;
    }
    return problems;    
}

problem createOneproblem(int i_num){
    int r_num=0,r=0;
    // srand((unsigned)time(NULL));
    // cout<<"bp2 before malloc in createOneproblem"<<endl;
    problem problem;
    // cout<<"bp3 after malloc in createOneproblem"<<endl;
    // cout<<"bp4 bf rand_i"<<endl;
    while((r_num=((rand()%i_num+1)/1))<2);    //configure the amount of items;
    // cout<<"bp5 af rand_i"<<endl;

    //provide the sapce for the storage of the problem;
    if(!(problem.character=(char *)malloc(2*i_num*sizeof(char)))||!(problem.number=(int *)malloc(2*i_num*sizeof(int)))){
        cout<<"space divided failed!"<<endl;
        return problem;
    }
    // cout<<"bp6 af malloc"<<endl;
    cout<<"r_num: "<<r_num<<endl;
    for(i=0,j=0,k=0;j<r_num;j++){
        // cout<<"I've run into the for in createOneproblem!"<<endl;
        opt=static_cast<OPERATOR>((rand()%4)+1);
        type=static_cast<INT_OR_FT>((rand()%2)+1);
        switch (opt)
        {
        case add:
            problem.character[k++]='+';
            break;
        case subtract:
            problem.character[k++]='-';
            break;
        case divide:
            problem.character[k++]='/';
            break;
        case multiply:
            problem.character[k++]='x';
            break;
        default:
            break;
        }
        cout<<"bp between switch"<<endl;
        switch (type)
        {
        case I:
            problem.number[i++]=(rand()%100+1)/1;
            break;
        case F:
            problem.number[i++]=(rand()%100+1)/1;  //molecule
            problem.character[k++]='/';            
            problem.number[i++]=(rand()%100+1)/1;  //denominator
            break;
        }
        cout<<"bp af switch"<<endl;
    }
    problem.cLen=k;problem.nLen=i;
    return problem;
}