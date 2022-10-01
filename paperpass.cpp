#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <math.h>
#include <iterator>
#include <cctype>
#include <Windows.h>
#include <malloc.h>

// #define max(a,b) (a>b)?a:b
#define SMAXLEN 100     //一句中最多一百字
#define MAXLEN 10000    //文本最多一万字
#define MAXLENS 1000    //最多一千个句子

using namespace std;

wchar_t x[MAXLEN],y[MAXLEN];
int dp[MAXLEN][MAXLEN];
int i,j;    //循环变量


typedef struct sentence{
    wchar_t *word;  //句子的数据结构
    int len;    //句子长度
}*Sentence,sentence;

typedef struct sentences{
    Sentence sents;
    int s_len;
    int t_len;
}Sentences;

float checkSentence(Sentence text,Sentence lib);
Sentences cutTosentences(string fileName);
float compareSentences(Sentences textSentences,Sentences libSentences);

int main(){
    string textFilename="D://text.txt",libFilename="D://lib.txt";
    Sentences s_test;
    s_test=cutTosentences(textFilename);
    wcout<<s_test.sents;
//     float sim=0;
//     sim=compareSentences(cutTosentences(textFilename),cutTosentences(libFilename));
//     if(sim>0.05){
//         cout<<"文本相似度超5%"<<endl;
//         cout<<"文本存在过度引用行为"<<endl;
//     }
//     else{
//         cout<<"文本相似度不超过5%"<<endl;
//         cout<<"文本不存在过度引用行为"<<endl;
//     }
//     return 0;
}

float checkSentence(Sentence text,Sentence lib,int textLen){
    float c[MAXLEN][MAXLEN]={0};
    for(i=0;i<text->len;i++){
        for(j=0;j<lib->len;j++){
            if(text->word[i]==lib->word[j]){
                c[i][j]=c[i-1][j-1]+1;
            }
            else{
                c[i][j]=max(c[i-1][j],c[i][j-1]);
            }
        }
    }
    return c[text->len][lib->len]/textLen;
}

Sentences cutTosentences(string fileName){
    ifstream infile;
    infile.open(fileName.data());
    // assert(infile.is_open());

    wchar_t currentWord;
    wchar_t tempSentence[SMAXLEN]=L"";
    
    string paper="";
    wchar_t wpaper[MAXLEN]=L"";
    Sentence temp;
    Sentence sentences;
    Sentences r_v;  //返回值
    sentences=(Sentence)malloc(MAXLENS*sizeof(sentence));

    if(!(temp->word=(wchar_t*)malloc(SMAXLEN*sizeof(wchar_t)))){
        cout<<"内存分配失败！"<<endl;
    } 
    infile >> paper;
//下面将char形式的文章转化为wchar_t类型
    int len=MultiByteToWideChar(CP_OEMCP,0,paper.data(),strlen(paper.data()),NULL,0);
    int textLen=MultiByteToWideChar(CP_OEMCP,0,paper.data(),strlen(paper.data()),wpaper,len);
    wpaper[len]='\0';
    int i=0,j=0,k=0;    //i表示文本中的第几个字,j表示句中的第几个字,表示
    while(wpaper[i]!=EOF){  //这里把EOF看作文章的末尾，但对于wchar_t来说不一定是；
      
        if(!(wpaper[i]==L'。'||wpaper[i]==L'；'||wpaper[i]==L'.'||wpaper[i]==L';'))
        //句子结束标志为中英文的分号、句号
            temp->word[j++]=wpaper[i];
        else{
            j=0;
            sentences[k++]=*temp;  //句子数组加上temp
        }
        i++;
    }
    r_v.sents=sentences;
    r_v.s_len=k;
    r_v.t_len=textLen;
    return r_v;
}

float compareSentences(Sentences textSentences,Sentences libSentences){
    float sim=0;
    for(i=0;(i<textSentences.s_len);i++){
        for(j=0;j<(libSentences.s_len);j++){
            sim+=checkSentence(&(textSentences.sents[i]),&(libSentences.sents[j]),textSentences.t_len);     //调用最长公共子序列算法检测相似度
        }
    }
    return sim;
}