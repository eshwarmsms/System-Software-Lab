// 
// This code is written by ESHWAR M S
// 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

map<string, int> opcodes;
map<string, int> symbols;

class head{
public:
	string name;
	int startAddress, length;
	head(string n,int  s,int l){
		name = n;
		startAddress = s;
		length = l;
	}
	string getRecord(){
		stringstream s;
		s<<"H"
		<<left<<setw(6)<<std::setfill(' ')<<name
		<<right<<setw(6)<<setfill('0')<<hex<<startAddress
		<<setw(6)<<setfill ('0')<<hex<<length;
		return s.str();
	}	
};

class text{
public:
	int startAddress, length;
	string opcodes;
	// bool isFull;
	int TOTAL;
	text(int s){
		startAddress = s;
		opcodes ="";
		length = 0;
		TOTAL = 30;
		// isFull = false;
	}
	string getRecord(){
		stringstream s;
		s<<"T"
		<<setw(6)<<setfill('0')<<hex<<startAddress
		<<setw(2)<<hex<<length
		<<opcodes;
		return s.str();
	}
	void add(string opcode){
		if(canAdd(opcode)){
			length += opcode.length()/2;
			opcodes.append(opcode);
		}
	}
	bool canAdd(string opcode){
		if(length + opcode.length()/2 <= TOTAL) return true;
		else return false;
	}
	//TODO - fix the bug
	void fill(){
		while(canAdd("  ")){
			opcodes.append("  ");
			TOTAL--;
		}
		// isFull = true;
	}
};

class end1{
public:
	int startAddress;
	end1(int s){
		startAddress = s;
	}
	string getRecord(){
		stringstream s;
		s<<"E"<<setw(6)<<setfill('0')<<hex<<startAddress;
		return s.str();
	}
};

string assemble(int code, int address, bool x){
	stringstream s;
	s<<setfill('0')<<setw(2)<<hex<<code;
	if(x){
		address += 0x8000;
	}
	s<<setfill('0')<<setw(4)<<hex<<address;
	return s.str();
}

int main()
{
	string label, mnumonic, operand, data, locstr, location, objectcode;
	int startAddress, endAddress, locctr;
	ifstream input;
	ofstream output;
	int code;
	input.open("input.txt");
	output.open("output.txt");
	getline(input, data);
	std::stringstream iss(data);
	getline(iss, locstr ,'\t');
	getline(iss, label ,'\t');
	getline(iss, mnumonic ,'\t');
	getline(iss, operand ,'\t');
	getline(iss, objectcode ,'\t');
	if(!mnumonic.compare("START")){
		stringstream convert(operand);
		convert>>hex>>startAddress;
		locctr = startAddress;
	}
	int length = 0x107a;
	// Write head record
	head h(label, startAddress, length);
	output<<h.getRecord()<<endl;
	
	// Initialize text record
	text *t = new text(startAddress);
	
	while(mnumonic.compare("END")){
		getline(input, data);
		std::stringstream iss(data);
		getline(iss, location ,'\t');
		getline(iss, label ,'\t');
		// if comment then continue
		if(!label.compare(".")){
			continue;
		}
		getline(iss, mnumonic ,'\t');
		getline(iss, operand ,'\t');
		getline(iss, objectcode ,'\t');
                if(!mnumonic.compare("RESW") || !mnumonic.compare("RESB")) t->fill();
		if(!t->canAdd(objectcode)){
			output<<t->getRecord()<<endl;
			stringstream s(location);
			int locctr;
			s>>hex>>locctr;
			t = new text(locctr);
		}
		t->add(objectcode);
		if(!mnumonic.compare("END")){
			break;
		}
	}
	
	output<<t->getRecord()<<endl;
	// End record
	end1 e(startAddress);
	output<<e.getRecord()<<endl;

	// Close files
	input.close();
	output.close();
}