#include<iostream>
#include"heaphop.h"
#include<fstream>

using namespace std;
bool writefile(string name,string content){
    ofstream fout;
    fout.open(name);
    if(!fout.is_open()) return false;
    fout<<content;
    fout.close();
    return true;
}

string readfiles(string name){
    ifstream fin;
    string content="";
    char temp;
    fin.open(name);
    fin.unsetf(ios::skipws);
    while(fin>>temp){
        content+=temp;
    }
    fin.close();
    return content;
}
int main(){
    string s=readfiles("wordcount.cpp");
    cout<<writefile("output.txt","love you this mother fucker");
}
