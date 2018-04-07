#include<vector>
#include<iostream>          //for testing 
//#include<io.h>          //in windows
#include<sys/types.h>
#include<fstream>
#include<string>
#include<dirent.h>

using namespace std;

bool match(string name,string suffix){
    if(suffix == "")    return true;
    int pos = name.find(".");
    return suffix==name.substr(pos+1);
}

bool writefile(string name,string content){
    ofstream fout;
    fout.open(name);
    if(!fout.is_open()) return false;
    fout<<content;
    fout.close();
    return true;
}

vector<string> readfiles(vector<string> name){
    ifstream fin;
    string content="";
    vector<string> vs;
    fin.unsetf(ios::skipws);
    char temp;
    for(string s:name){
        content = "";
        fin.open(s);
        while(fin>>temp){
            content+=temp;
        }
        vs.push_back(content);
        fin.close();
    }

    return vs;
}

string readfiles(string name){
    ifstream fin;
    string content="";
    char temp;
    fin.open(name);
    if(!fin.is_open()) abort();
    fin.unsetf(ios::skipws);
    while(fin>>temp){
        content+=temp;
    }
    fin.close();
    return content;
}

vector<string> readstopfile(string name){
    ifstream fin;
    string content="";
    vector<string> dict;
    fin.open(name);
    if(!fin.is_open()) abort();     //file not open
    while(fin>>content){
        dict.push_back(content);
        content = "";       // is it necessary?
    }
    fin.close();
    return dict;
}

vector<string> TraverseFiles(string suffix=""){  //return files names with the right suffix
    //_finddata_t file_info;          //in windows
    //int handle = 
    vector<string> vn;
    DIR * dir = opendir(".");
    dirent * p =NULL;
    while((p=readdir(dir))!=NULL){
        if(p->d_name[0]!='.'&&p->d_type==DT_REG&&match(p->d_name,suffix)){         // check the filesuffix yourself
            vn.push_back(p->d_name);
        }
    }
    closedir(dir);
    return vn;
}

/*int main(){
    auto a =TraverseFiles();      //gotch
    auto cs =  readfiles(a);
    for(string s:cs)
        cout<<s<<endl;
}*/
