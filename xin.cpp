#include <iostream>
#include <string>
#include <string.h>

#define BLOCK 10000
#define llong long long

using namespace std;

int decryptionKey(int,int,int);
long long int decimalToBinary(int);
int modularExpo(int,int,int);
long long encRSA(string,int,int,int);
string decryptRSA(llong,int,int,int);
int convertChar(char);

void encryption();
void decryption();

int main(){
	
	decryption();
	decryption();

	return 0;
}

void encryption(){

	string text;
	int p,q,e;

	cout << "Text: ";
	cin >> text;
	cout << "P: ";
	cin >> p;
	cout << "Q: ";
	cin >> q;
	cout << "E: ";
	cin >> e;

	long long res;
	res = encRSA(text,p,q,e);
	cout << "Encrypted: " << res << endl;
}

void decryption(){

	long long code;
	int p,q,e;

	cout << "Code: ";
	cin >> code;
	cout << "P: ";
	cin >> p;
	cout << "Q: ";
	cin >> q;
	cout << "E: ";
	cin >> e;

	string res;
	res = decryptRSA(code,p,q,e);
	cout << "Message: " << res << endl;
}



long long decimalToBinary(int n){
    int arr[32],i = 0;
    long long ans = 0;    
    while(n>0){
    	arr[i] = (n%2==0)? 0:1;
    	n/=2;
    	i++;
    }
    for(int x = i-1; x>=0;x--){
    	ans *= 10;
    	ans += arr[x];
    }
    return ans;
}

int decryptionKey(int p,int q,int e){
	int n = (p-1)*(q-1);
	int key;
	for(key = 1; key <= n;key++){
		if(((key*e)%n)==1){
			break;
		}
	}
	return key;
}

int modularExpo(int p,int exp, int c){

	long long bin = decimalToBinary(exp);
	int x = 1;
	
	while(bin>0){
		if(bin%10 == 1){
			x = (x*p)%c;
			p = (p*p)%c;
		} else {
			p = (p*p)%c;
		}
		bin /= 10;
	}
	return x;
}

string decryptRSA(llong code,int p, int q, int e){

	int num,temp,raw,c = p*q,d = decryptionKey(p,q,e);
	string text = "";
	char let;
	while(code>0){
		num = code%BLOCK;
		temp = modularExpo(num,d,c);
			while(temp>0){
				raw = temp%100;
				let = raw +'A';
				text += let;
				temp /= 100;
			}
		code /= 10000;
	}
	char cTemp;
	int len = text.length();
	for(int x = 0; x < len/2;x++){
		cTemp = text[(len-x)-1];
		text[(len-x)-1] = text[x];
		text[x] = cTemp;
	}

	return text;
}

int convertChar(char t){

	int x = (t==tolower(t)? (t-'a'):(t-'A'));
	return x;
}

long long encRSA(string text, int p, int q, int e){
	int n = p*q;
	long long code = 0;
	for(int x = 0; x < text.length();x+=2){
		int a = convertChar(text[x]); 
		int b = convertChar(text[x+1]);
		int raw = a;
		raw *= 100;
		raw += b;
		code *= 10000;
		code += modularExpo(raw,e,n);
	}
	return code;
}
