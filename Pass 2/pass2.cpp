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
	string label, mnumonic, operand, data, locstr, location;
	int startAddress, endAddress, locctr;
	ifstream input, optab, symtab;
	ofstream output, listing;
	int code;
	input.open("input.txt");
	optab.open("optab.txt");
	output.open("output.txt");
	symtab.open("symtab.txt");
	listing.open("listing.txt");
	while(!optab.eof()){
		optab>>mnumonic>>hex>>code;
		opcodes.insert(pair<string, int>(mnumonic,code));
	}
	while(!symtab.eof()){
		symtab>>mnumonic>>hex>>code;
		symbols.insert(pair<string, int>(mnumonic,code));
	}
	getline(input, data);
	std::stringstream iss(data);
	getline(iss, locstr ,'\t');
	getline(iss, label ,'\t');
	getline(iss, mnumonic ,'\t');
	getline(iss, operand ,'\t');
	if(!mnumonic.compare("START")){
		stringstream convert(operand);
		convert>>hex>>startAddress;
		locctr = startAddress;
	}
	int length = 20;
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
			listing<<data<<endl;
			continue;
		}
		getline(iss, mnumonic ,'\t');
		getline(iss, operand ,'\t');
		int address = 0;
		bool isIndex = false;
		string objectcode = "";
		// search optab for mnumonic
		map<string,int>::iterator it = opcodes.find(mnumonic);
		// if mnumonic found
		if(it!=opcodes.end()){
			// if there is symbol in OPERAND field
			if(operand.compare("")){
				std::size_t found = operand.find(",X");
				string op = operand;
				if(found!=std::string::npos){
					op.replace(found,2,"");
					isIndex = true;
				}
				map<string,int>::iterator i = symbols.find(op);
				if(i!=symbols.end()){
					address = i->second;
				}
				else{
					address = 0;
					cout<<op<<": undefined Symbol"<<endl;
				}
			}
			else{
				address = 0;
			}
			objectcode = assemble(opcodes.find(mnumonic)->second, address, isIndex);
		}
		// byte or word
		else if(!mnumonic.compare("BYTE")){
			//if starts from C
			if(operand.at(0) == 'C'){
				for(int i=2; i<operand.length()-1; i++){
					stringstream s;
					s<<hex<<(int)operand.at(i);
					objectcode+= s.str();
				}
			}
			// If starts from X
			if(operand.at(0) == 'X')
				objectcode = operand.substr(2, operand.length()-3);
		}
		else if(!mnumonic.compare("WORD")){
			stringstream s;
			s<<setfill('0')<<setw(6)<<hex<<stoi(operand);
			objectcode = s.str();
		}
		else if(!mnumonic.compare("RESW")){
			t->fill();
		}
		else if(!mnumonic.compare("RESB")){
			t->fill();
		}
		if(!t->canAdd(objectcode)){
			output<<t->getRecord()<<endl;
			stringstream s(location);
			int locctr;
			s>>hex>>locctr;
			t = new text(locctr);
		}
		t->add(objectcode);
		listing<<location<<"\t"<<label<<"\t"<<mnumonic<<"\t"<<operand<<"\t"<<objectcode<<endl;
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
	optab.close();
	symtab.close();
	output.close();
}