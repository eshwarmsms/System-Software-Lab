#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	int start, length;
	ifstream input;
	ofstream output;
	input.open("input.txt");
	output.open("output.txt");
	string data;
	char type;
	while(type != 'E'){
		getline(input, data);
		type = data.at(0);
		if(type=='T'){
			string opcodes = data.substr(9);
			string locString = data.substr(1,6);
			stringstream s(locString);
			int loc;
			s>>hex>>loc;
			while(opcodes.length() > 0)
			{
				output<<hex<<loc<<" "<<opcodes.substr(0,2)<<endl;
				opcodes.erase(0, 2);
				loc++;
			}
		}
	}
}