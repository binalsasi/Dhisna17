#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

// this function will convert the binary string provided into corresponding integer value and calculate its degree
// a degree of a string is the position of the most significant high(1) bit where position starts from 0
int binaryToInt(string binary, int * degree){
	int num = 0, size = binary.length();
	char * bin = new char[size];
	strcpy(bin, binary.c_str());
	for(int i = 0; i < size; i++){
		if(bin[size-1-i] == '1'){
			degree = &i;
			num+=pow(2,i+1);
		}
	}
	return num;
}

// this function will convert the integer number provided into its corresponding binary string
string intToBinaryString(int num){
	string str = "";
	for(int i = 1; num != 0; num>>1){
		if(num&&i) str+='1';
		else str+='0';
	}	
	reverse(str.begin(), str.end());
	return str;
}


int main(){

	string gs, ts;
	int G = 0, T2 = 0, gr = 0, tr = 0;
	cout<<"Enter Generator Code In Binary : "; 
	cin>>gs;
	cout<<"Enter Received CodeWord In Binary : ";
	cin>>ts;

	G = binaryToInt(gs, &gr);
	T2 = binaryToInt(ts, &tr);

	int num_iter = tr - gr;
	int d = 1 << gr;
	int mm = pow(2,gr) -1;
	for(int c = 0; num_iter > -1; num_iter--){
		c = (T2 & mm << num_iter) >> num_iter;
		if(c>=d){
			c^=G;
			T2&=(~mm<<num_iter);
			T2|= c<<num_iter;
		}
	}

	int R2 = T2 & mm;
	if(R2 == 0)
		cout<<"No Error Was Detected!" << endl;
	else{
		string inBinary = intToBinaryString(R2);
		cout<< "Error Detected! Remainder = "<< inBinary <<endl;
	}
	return 0;	
}
