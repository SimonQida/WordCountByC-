#include "doc.h"
#include<iostream>
#include<iterator>
#include<map>
#include<set>

using namespace std;
indoc::indoc(const string& n,const string& t,const vector<bool>& para_){//default 1,1,1,0
    this->name = n;
    this->text = t;
    this->para = para_;
    cal();
}

indoc::indoc(){}

/*bool isChinese(char c) {  
  return c >= 0x4E00 &&  c <= 0x9FA5;// 根据字节码判断  
  }
  */
bool indoc::isword(char c) {  
    return (c>='A'&&c<='Z')||(c>='a'&&c<='z');  
}
bool indoc::isignore(char c) {  
    return (c>='0'&&c<='9'||c=='"'||c=='-');
}
bool indoc::issymbol(char c){
    return !(isword(c));        //isword contains isnum !
}

//  单词不区分大小写    content-b1ased"，视为1个单词 (ignore)    num ' and -
bool hasletter(string s){
    for(char c:s)
        if(c>='a'&&c<='z')
            return true;
    return false;
}

void indoc::add(string s){        //check set
    if(!indoc::stoptable.count(s)&&hasletter(s)){  //check map and add count or add new word
        auto itr =wordmap.find(s);
        if(itr != wordmap.end())
            (*itr).second++;
        else wordmap[s] = 1;
    }
}

void indoc::cal(){
    string word;
    bool _null=true,_zhushi=false,_code=true;       //emmm not a well part
    for(char c:text){
        if(c=='\n'){            //judge the linetype and cut the word and stands a symbol
            symbolcount++,linecount++;
            if(word.size()){
                add(word);
                word = "";      //to map
            }
        }
        else if(isword(c)){
            word+=transmall(c);
        }
        else if(isignore(c)){
            if(c=='"'||c=='-')  symbolcount++;
            if(c=='-') word+='-';
        }
        else{
            if(word.size()){
                add(word);
                word = "";
            }
            symbolcount++;
        }
    }
    if(word.size()){
        add(word);
        word = "";      //to map
    }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@222222222222problem
    wow *wp;
    for(auto itr=wordmap.begin();itr!=wordmap.end();itr++){
        wp = new wow((*itr).first,(*itr).second);
        if(frewords.currentsize>=100){       // get the top 100
            //cout<<" "<<frewords.currentsize<<" ";
            if(frewords.findMin()<(*wp))
            {
                frewords.deleteMin();
                frewords.insert(*wp);
            }
        }
        else 
            frewords.insert(*wp);
        wordcount+= (*itr).second;
        delete wp;
    }
    cout<<"sparing over";
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@222222222222problem

char indoc::transmall(char s){
    if(s>='A'&&s<='Z')
        s +=32;
    return s;
}

string indoc::mes(){
    string message= "name:"+name+"\n";
    wow w;
    vector<pair<string,int>> vp;
    int edge = frewords.currentsize;
    for(int i=0;i<edge;i++){
        frewords.deleteMin(w);
        vp.push_back(make_pair(w.str,w.fre));       // push all and out reverse
    }
    for(auto itr = vp.rbegin();itr!=vp.rend();itr++){
        message+=(*itr).first+" "+to_string((*itr).second)+"\n";
    }

    /*
    if(para[2] ==true){
        message +="\tsymbolcount:";
        message+=to_string(symbolcount);
    }
    if(para[1] == true)
    {
        message +="\twordcount:";
        message+=to_string(wordcount);
    }
    if(para[0]==true)
    {
        message +="\tlinecount:";
        message+=to_string(linecount);
    }
    if(para[3] == true){
        message +="\tcodeline:";
        message+=to_string(codeline);
        message+="\tnullline:";
        message+=to_string(nullline);
        message+="\tbalaline:";
        message+=to_string(balaline);
    }
    */
    return message+'\n';
}

set<string> indoc::stoptable = {};
void outdoc::clear(){
    doc_in.clear();                     
    //vector<indoc>().swap(doc_in);       //clear the space 
}


