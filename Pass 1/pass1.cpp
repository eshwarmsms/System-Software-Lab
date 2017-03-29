// 
// This code is written by ESHWAR M S
// 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <map>

using namespace std;

map<string, int> opcodes;
map<string, int> symbols;

int main()
{
	string label, opcode, operand, data;
	int startAddress, endAddress, locctr;
	ifstream input, optab;
	ofstream output, symtab;
	string nmu;
	int code;
	input.open("input.txt");
	optab.open("optab.txt");
	output.open("output.txt");
	symtab.open("symtab.txt");
	while(!optab.eof()){
		optab>>nmu>>hex>>code;
		opcodes.insert(pair<string, int>(nmu,code));
	}
	getline(input, data);
	std::stringstream iss(data);
	getline(iss, label ,'\t');
	getline(iss, opcode ,'\t');
	getline(iss, operand ,'\t');
	if(!opcode.compare("START")){
		stringstream convert(operand);
		convert>>hex>>startAddress;
		locctr = startAddress;
		if(!label.empty()){
			symbols.insert(pair<string, int>(label, locctr));
			symtab<<label<<"\t"<<hex<<locctr<<endl;
		}
		output<<hex<<locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
	}
	while(opcode.compare("END")){
		getline(input, data);
		std::stringstream iss(data);
		getline(iss, label ,'\t');
		//comment
		if(!label.compare(".")){
			output<<'\t'<<data<<endl;
			continue;
		}
		getline(iss, opcode ,'\t');
		operand = "";
		getline(iss, operand ,'\t');
		// write the line to intermediate file
		output<<hex<<locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
		// Add label to symtab if it exists
		if(!label.empty()){
			map<string,int>::iterator it = symbols.find(label);
			if(it!=symbols.end()){
				cout<<"Symbol already exist"<<endl;
				break;
			}
			else{
				symbols.insert(pair<string, int>(label, locctr));
				symtab<<label<<"\t"<<hex<<locctr<<endl;
			}
		}
		// find if opcode exists in optab else suitable assembly directive
		map<string,int>::iterator it = opcodes.find(opcode);
		if(it!=opcodes.end()){
			locctr += 3;
		}
		else if(!opcode.compare("WORD")){
			locctr += 3;
		}
		else if(!opcode.compare("RESW")){
			int temp;
			stringstream convert(operand);
			convert>>temp;
			locctr += 3 * temp;
		}
		else if(!opcode.compare("RESB")){
			int temp;
			stringstream convert(operand);
			convert>>temp;
			locctr += temp;
		}
		else if(!opcode.compare("BYTE")){
			if (operand.at(0) == 'C')
			{
				int temp = operand.length()-3;
				locctr += temp;
			}
			else if (operand.at(0) == 'X')
			{
				int temp = operand.length()-3;
				locctr += temp/2;
			}
		}
		else{
			if(!opcode.compare("END")){
				break;
			}
			cout<<"Invalid opcode"<<endl;
			exit(1);
		}
	}
	input.close();
	optab.close();
	symtab.close();
	output.close();
	endAddress = locctr;
	cout<<"Length is: "<<endAddress - startAddress<<endl;
}