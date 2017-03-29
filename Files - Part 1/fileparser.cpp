#include<iostream>
#include<fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main()
{
	char data[100];
	int a,b, res;
	char op;
	ifstream input;
	input.open("input.dat");
	
	while(!input.eof())
	{	//input>>data;
		cin>>data;
		//cout<<data<<" ";
		if(!strcmp(data, "ADD")){
			op = '+';
		}
		else if(!strcmp(data, "SUB")){
			op = '-';
		}
		//input>>data;
		cin>>data;
		//cout<<data<<endl;
		a = atoi(data);
		//input>>data;
		cin>>data;
		b = atoi(data);
		//cout<<data<<endl;
		switch(op){
			case '+' : res = a+b;
				break;
			case '-' : res = a-b;
				break;
		}
		//cout<<a<<op<<b<<"="<<res<<endl;
		cout<<res<<endl;
	}
	input.close();
}
