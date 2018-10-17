#include<iostream>
#include<cstring>
#include<cmath>
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
	string gs, ms;
	cout<<"Enter Generator Code In Binary : ";
	cin>>gs;
	cout<<"Enter Message Code In Binary : ";
	cin>>ms;
	int gr = 0, mr = 0;
	int G = binaryToInt(gs, &gr), M = binaryToInt(ms, &mr);
	int mm = pow(2, gr) -1;
	int d = 1 << gr;

	int M2 = M << gr;

	for(int c = 0; mr >=0; mr--){
		c = (M2 & mm << mr) >> mr;
		if(c >= d){
			c^=G;
			M2&=(~mm<<mr);
			M2|=c<<mr;
		}
	}

	int R = M2 & mm;
	int T = M << gr | R;

	string ts = intToBinaryString(T);
	cout<<"CodeWord Bis : "<<ts<<endl;	
	return 0;
}
