#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main()
{
	char data[100];
	char operand[3];
	int a,b, res;
	char op;
	ifstream input;
	ofstream output;
	input.open("input.dat");
	output.open("output.dat");
	while(!input.eof())
	{	input>>operand;
		if(!strcmp(operand, "ADD")){
			input>>data;
			a = atoi(data);
			input>>data;
			b = atoi(data);
			res = a+b;
			operand[0] = '\0';
			output<<a<<" + "<<b<<" = "<<res<<endl;
		}
		else if(!strcmp(operand, "SUB")){
			input>>data;
			a = atoi(data);
			input>>data;
			b = atoi(data);
			res = a-b;
			operand[0] = '\0';
			output<<a<<" - "<<b<<" = "<<res<<endl;
		}
		
		else if(!strcmp(operand, "MUL")){
			input>>data;
			a = atoi(data);
			input>>data;
			b = atoi(data);
			res = a*b;
			operand[0] = '\0';
			output<<a<<" * "<<b<<" = "<<res<<endl;
		}
		else if(!strcmp(operand, "DIV")){
			input>>data;
			a = atoi(data);
			input>>data;
			b = atoi(data);
			if(b!=0){
				res = a/b;
				operand[0] = '\0';
			output<<a<<" / "<<b<<" = "<<res<<endl;
			}
			else{
				operand[0] = '\0';
				output<<"Invalid input"<<endl;
			}
		}
	}
	input.close();
}
