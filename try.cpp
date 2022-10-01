#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Windows.h>
#define MAXLEN 100

using std::string;
using namespace std;

typedef struct a{
    char *a;
    int *b;
}*A,a;

int main(){
    A ab;
    int a_s,b_s;
    cout<<"bp 1"<<endl;
    if(!(ab->a=(char*)malloc(8*sizeof(char)))||!(ab->b=(int*)malloc(8*sizeof(int)))){
        cout<<"内存分配失败"<<endl;
    }
    else cout<<"内存分配成功"<<endl;
    cout<<"bp 2"<<endl;
    a_s=strlen(ab->a);
    b_s=sizeof(ab->b);
    cout<<"a's length is:"<<a_s<<endl;
    cout<<"b's length is:"<<b_s<<endl;
}
