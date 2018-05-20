#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <list>

#define NPOS string::npos

using namespace std;

ofstream out;//输出文件流
string ins;//预编译指令
string para;//宏名
string val;//值
map<string, string > define;//存放宏和值的映射
map<string, int> instructions;//指令集的值
list<string> inss;//define后的宏名

void read(string filename);//读取文件
void handle_include(string para);
void handle_define(string para, string val);
void handle_undef(string para);
bool handle_if(string para);
bool handle_else(bool statusRead);
bool handle_ifdef(string para);
bool handel_ifndef(string para);
bool handle_endif();
void build_ins();//构建指令集的int值

int main(int argc, char** argv){
    if(argc != 3){
        cout<<"Need two names of source and destination files";
        return 0;
    }
    build_ins();
    out.open(argv[2]);
    read(argv[1]);
    out.close();
}
void read(string filename){
    bool statusRead = true;
    ifstream fin(filename);
    string line;
    while(getline(fin, line)){
        if(line.find("#") == 0){
                /*分割预编译指令，得到各个值，并进行相应的处理*/
            int first = line.find(" ");
            if(first != NPOS){
                ins = line.substr(0, first);
                int second = line.find(" ",first+1);
                para = line.substr(first+1, second-first-1);
                if(second != NPOS){
                    val = line.substr(second+1);
                }else{
                    val = "";
                }
            }else{
                ins = line;
            }
            switch(instructions[ins]){
                case 0:handle_include(para);break;
                case 1:handle_define(para, val);break;
                case 2:handle_undef(para);break;
                case 3:statusRead= handle_if(para);break;
                case 4:statusRead = handle_else(statusRead);break;
                case 5:statusRead = handle_ifdef(para);break;
                case 6:statusRead = handel_ifndef(para);break;
                case 7:statusRead = handle_endif();
            }
        }else{
        /*根据每行是否读取操作无指令的行，并处理带有一个参数的宏和#处理的参数*/
            if(statusRead){
                list<string>::iterator it;
                int index;
                int index1;
                int index2;
                bool isNull = true;
                string name;
                string arg1;
                string arg2;
                string temp;
                for(it = inss.begin(); it != inss.end();it++){
                    index = (*it).find("(");
                    if(index == NPOS){
                        name = (*it);
                        isNull = true;
                    }else{
                        name = (*it).substr(0, index);
                        arg1 = (*it).substr(index+1, para.size() - index-2);
                        isNull = false;
                        if((define[*it]).find("\"#") != NPOS)
                            arg1 = "#"+arg1;
                    }
                    index = line.find(name);
                    if(index != NPOS){
                        if(isNull){
                            temp = define[*it];
                            while(index != NPOS){
                                line.replace(index, (*it).size(), temp);
                                index = line.find(*it, index+1);
                            }
                        }else{

                            index1 = line.find(")",index);
                            arg2 = line.substr(index + name.size(), index1-index-name.size()+1);
                            if((define[*it]).find("\"#") != NPOS){
                                arg2.replace(0,1,"\"");
                                arg2.replace(arg2.size()-1,1,"\"");
                            }

                            temp = define[*it];

                            while(index != NPOS){
                                line.replace(index, name.size()+arg2.size(), temp);
                                index = line.find(name);
                            }

                            index = line.find(arg1);
                            while(index != NPOS){
                                line.replace(index, arg1.size(), arg2);
                                index = line.find(arg1);
                            }
                        }
                    }
                }
                out<<line<<endl;
            }
        }
    }
    fin.close();
}

void handle_include(string para){
    if(para.find("<") == 0){
        out<<"#include "<<para<<endl;
    }
    if(para.find("\"") == 0){
        read(para.substr(1,para.size()-2));
    }
}

void handle_define(string para, string val){
    define.insert(make_pair(para, val));
    inss.push_back(para);
}
void handle_undef(string para){
    define.erase(para);
    inss.remove(para);
}

bool handle_if(string para){
    while(define.count(para) == 1){
        para = define[para];
    }
    return (para == "1");
}

bool handle_else(bool statusRead){
    return (!statusRead);
}

bool handle_ifdef(string para){
    return (define.count(para) == 1);
}

bool handel_ifndef(string para){
    return (define.count(para) == 0);
}

bool handle_endif(){
    return true;
}

void build_ins(){
    instructions.insert(make_pair("#include",0));
    instructions.insert(make_pair("#define",1));
    instructions.insert(make_pair("#undef",2));
    instructions.insert(make_pair("#if",3));
    instructions.insert(make_pair("#else",4));
    instructions.insert(make_pair("#ifdef",5));
    instructions.insert(make_pair("#ifndef",6));
    instructions.insert(make_pair("#endif",7));
}
