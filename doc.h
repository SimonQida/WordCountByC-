#include<map>
#include<iterator>
#include "heaphop.cpp"
#include<set>
#include<vector>
using namespace std;
#ifndef _WOW_H
#define _WOW_H
class wow{
    public:
        string str;
        int fre;
        wow(string s,int i):str(s),fre(i){}
        wow(){}
        bool operator ==(const wow& aw)const{
            return this->fre==aw.fre;
        }
        bool operator >(const wow& aw)const{
            return this->fre>aw.fre;
        }
        bool operator <(const wow& aw)const{
            return this->fre<aw.fre;
        }
};
#endif

#ifndef _INDOC_H
#define _INDOC_H
class indoc{
    private:
        string name;
        string text;
        int linecount{0},wordcount{0},stoped{0},symbolcount{0},codeline{0},nullline{0},balaline{0};
        map<const string,int> wordmap;      //count() return 0 or 1 to identify 
        vector<bool> para ;
        void add(string s);       //check set
        char transmall(char);
        BinaryHeap<wow> frewords;

    public:
        static set<string> stoptable;
        indoc(const string& n,const string& t,const vector<bool>& para_ = vector<bool>{1,1,1,0});

        indoc();

        /*bool isChinese(char c) {  
            return c >= 0x4E00 &&  c <= 0x9FA5;// 根据字节码判断  
        }
        */
        bool isword(char c) ;
        bool isignore(char c)   ;
        bool issymbol(char c);
              //isword contains isnum !
        void cal();
        string mes();

};
#endif

#ifndef _outdoc_H_
#define _outdoc_H_
class outdoc{
    public:
        vector<indoc> doc_in;
        string name;

        outdoc(vector<indoc> vi,string n):name(n),doc_in(vi){}
        void clear();
};
#endif
