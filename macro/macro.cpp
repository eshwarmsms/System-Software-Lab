#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

 string label, mnumonic, operand, data;
 string macroName;

 ifstream input("input.txt");
 ofstream output("ouptut.txt");
 fstream macro("macro.txt");

 void getData(){
     label ="";
     mnumonic="";
     operand = "";
     getline(input, data);
     stringstream s(data);
     getline(s, label, '\t');
     getline(s, mnumonic, '\t');
     getline(s, operand, '\t');
 }

 int main(){

    getData();
    while(!input.eof()){
        if(!mnumonic.compare("MACRO")){
            macroName = label;
            getData();
            while(mnumonic.compare("MEND")){
                macro<<label<<'\t'<<mnumonic<<'\t'<<operand<<endl;
                getData();
            }
        }     
        getData();
     }

     input.close();
     macro.close();
     input.open("input.txt");
     macro.open("macro.txt");

     getData();
     while(!input.eof()){
        if(!mnumonic.compare(macroName)){
            if(!label.empty()){
                output<<label;
            }
            while(!macro.eof()){
                getline(macro, data);
                output<<data<<endl;
            }
            cout<<output.tellp()<<endl;
            output.seekp(-1, ios::cur);
            macro.close();
            macro.open("macro.txt");
        }  
        else if(!mnumonic.compare("MACRO")){
            while(mnumonic.compare("MEND")){
                getData();
            }
        }  
        else{
            output<<label<<'\t'<<mnumonic<<'\t'<<operand<<endl;
        } 
        getData();
     }

     input.close();
     output.close();
     macro.close();
 }