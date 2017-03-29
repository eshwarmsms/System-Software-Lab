#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <cstring>

using namespace std;

int main(){
	int start, length;
	ifstream input;
	ofstream output;
	input.open("input.txt");
	output.open("output.txt");
	string data;
	char type;
	cout<<"Enter starting address: "<<endl;
	cin>>hex>>start;
	getline(input, data);
	type = data.at(0);
	if(type=='H'){
		
	}
	while(type != 'E'){
		getline(input, data);
		type = data.at(0);
		if(type=='T'){
			string address, bin;
			// strings in integers
			int loc = 0, mod, add;
			// Mask
			int mask = 0x800;
			string locString = data.substr(1, 6);
			string modifier = data.substr(7, 3);
			string opcodes = data.substr(10);
			
			stringstream s1(locString);
			s1>>hex>>loc;
			loc += start;
			
			stringstream s2(modifier);
			s2>>hex>>mod;

			while(opcodes.length() > 0)
			{
				address = opcodes.substr(0,6);
				stringstream s3(address);
				s3>>hex>>add;
				int a = mod;
				if(a & mask)
				{
					add += start;
				}
				mod = mod  << 1;
				a = mod;
				output<<hex<<loc<<" "<<hex<<add<<endl;
				opcodes.erase(0,6);
				loc += 3;
			}
		}
	}
}