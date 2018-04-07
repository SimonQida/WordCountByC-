#include<iostream>
#include<stdexcept>
#include"filetest.cpp"
#include<iterator>
#include<algorithm>
#include "doc.h"
#include<vector>

using namespace std;
void clearpara(bool x[],int c){
    for(int i=0;i<c;i++) x[i] = 1;
    x[c-1] = 0;
}

void check(const char& c,const vector<string>& para,int i){
    if(c == 'e'){
        if(i==para.size()-1) throw invalid_argument("not file after '-e'");      
    }
    if(c == 'o'){
        if(i==para.size()-1||i==0||para[i-1][0]=='-') throw invalid_argument("not a good position of '-o'");    
    }
}

vector<outdoc> analysis(vector<string> para){ //return outdoc vector to print and load out
    bool isoutput=0,haslist=0,parastate[4] = {1,1,1,0},followfile=0,isorigin=1;
    vector<outdoc> outdocvec;
    vector<indoc> indocvec;         //package an array standing for -c -w -l -a 
    outdoc *odc;
    indoc *idc;
    for(int i =0;i<para.size();i++){
        if(para[i][0] == '-')
        {
            if(followfile) throw invalid_argument(" shoule be a file  ");     
            if(para[i]=="-c"||para[i]=="-w"||para[i]=="-l"||para[i]=="-a"){
                if(isorigin){
                    for(int pi =0;pi<sizeof(parastate)/sizeof(bool);pi++)
                        parastate[pi] = 0;
                    isorigin = 0;
                }
                if(para[i]=="-c"){
                    if(parastate[0]) throw invalid_argument("duplicate declaration -c"); 
                    parastate[0] =1;
                }
                if(para[i]=="-w"){
                    if(parastate[1]) throw invalid_argument("duplicate declaration -w");  
                    parastate[1] =1;
                }
                if(para[i]=="-l"){
                    if(parastate[2]) throw invalid_argument("duplicate declaration -l");   
                    parastate[2] =1;
                }
                if(para[i]=="-a"){
                    if(parastate[3]) throw invalid_argument("duplicate declaration -a");    
                    parastate[3] =1;
                }

            }

            else if(para[i]=="-e"){          //stoplist
                if(haslist)
                    throw invalid_argument(" not existing double stoplist");
                haslist =1,followfile =1;
                check('e',para,i);
            }
            else if(para[i]=="-o"){      // coding in this way is fucking clear
                followfile =isoutput =1;
                check('o',para,i);
            }
            else throw invalid_argument("not existing such para "+para[i]);  
        }
        else {
            if(followfile&&isoutput){// -o file
                followfile =0,isoutput =0;
                odc = new outdoc(indocvec,para[i]);   //new a outdoc pointed by odc and clear state,doc_in
                indocvec.clear();
                isorigin = 1;           //  I still  wandering when to reset the mode   temprary when a -o occur
                clearpara(parastate,sizeof(parastate)/sizeof(bool));
                outdocvec.push_back(*odc);
                delete odc;
            }
            else if(followfile){    //  -e file
                followfile =0;
                vector<string> sl = readstopfile(para[i]);        //get the file content in and mark words in set
                copy(sl.begin(),sl.end(),insert_iterator<set<string>>(indoc::stoptable,indoc::stoptable.begin()));
            }
            else           //deal * *.* and normal files with name but c++ exchange * or *.cpp to filesname...
            {
                /*if(para[i][0] == '*'&&para[i].size()==1){       //you know TraverseFiles all 
                  vector<string> filenames = TraverseFiles();
                  vector<string> content = readfiles(filenames);
                  for(string s:content){
                  idc = new indoc(para[i],s,vector<bool>(parastate,parastate+4));    //new a indoc and push it into indocvec
                  indocvec.push_back(*idc);
                  }

                  }
                  else if (para[i][0]=='*'&&para[i][1] =='.'){      // TraverseFiles with filter
                  string filter = para[i].substr(2,4);
                  cout<<para[i]<<endl;
                  }
                  */
                string content = readfiles(para[i]);
                idc = new indoc(para[i],content,vector<bool>(parastate,parastate+4));
                indocvec.push_back(*idc);
                delete idc;
            }


        }
    }
    if(indocvec.size()){
        odc = new outdoc(indocvec,"output.txt");   //new a outdoc pointed by odc and clear state,doc_in
        outdocvec.push_back(*odc);
        delete odc;
    }

    /*for(string s:para){
        idc {s,""};
        docvec[0].doc_in.push_back(idc);
    }*/
    return outdocvec;
}

void print(const vector<outdoc>& data){     //print all the mes to the console and output the mes to files
    /*for(auto s:data[0])
        cout<<s.name<<endl;
        */
    cout<<endl<<"out@@@@@@@@@@@@@@@@@@@@@@@@@@2"<<endl;
    string outmes;
    ofstream fout;
    for(outdoc od : data){
        fout.open(od.name);
        if(!fout.is_open()) throw invalid_argument("file "+od.name+" can not open");
        outmes = "";
        for(indoc id:od.doc_in){
            outmes+=id.mes();
        }
        cout<<outmes;
        cout<<endl;
        cout<<outmes<<" outmes";
        fout<<outmes;
        fout.close();
    }
}

int main(int args,char* argv[]){
//    readfiles("a.tet");           //test
    /*auto fnames = TraverseFiles("cpp");
      for(string ss : fnames)
      cout<<readfiles(ss)<<endl;*/
    vector<string> paravs;
    try{
        for(int i=1;i<args;i++){
            paravs.push_back(argv[i]);
        }
        print(analysis(paravs));
    }catch(exception &e){
        cout<<e.what()<<endl;
        abort();
    }
    /*
    auto afile  = TraverseFiles("");
    for(string ii:afile)
        cout<<ii<<" ";

    cout<<endl;
    indoc b(a);
    vector<indoc> temp {a};
    temp.push_back(b);
    //cout<<a.mes();
    //cout<<isChinese('啊');
    */

}
