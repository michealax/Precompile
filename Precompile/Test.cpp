#include <iostream>
int a;
int b;
int sum(int arg1, int arg2){
	return arg1 + arg2;
}
using namespace std;


int main(){
	a = 3;
	b = 5;
	int s = sum(a, b);
	int p = (a*b);
	int flag = 1;
	cout<<"#include pass !"<<endl;


	flag ++;
	cout<<"#define check1 pass !"<<endl;
	cout<<"#ifdef pass !"<<endl;

	flag ++;
	cout<<"#undef pass ! "<<endl;
	cout<<"#else pass !" <<endl;

	flag ++;
	cout<<"#ifndef pass !"<<endl;

	flag ++;
	cout<<"#if pass !"<<endl;

	flag ++;
	cout<<"#define check2 pass !"<<endl;

	flag ++;
	cout<<"#define check3 pass !"<<endl;

	flag++;
	cout<<"#define check4 pass !"<<endl;

	if(s==8&&p==15) {
		flag ++;
		cout<<"#define check5 pass !"<<endl;
	} else {
		cout<<"#define check5 fail !"<<endl;
	}

	if(flag==9) {
		cout<<"PART 2 pass !!!!!"<<endl;
	} else {
		cout<<"PART 2 fail !!!!!"<<endl;
	}

	int d = (2*(a));
	if(d==2*a) {
		cout<<"PART 3 pass !!!!!"<<endl;
	} else {
		cout<<"PART 3 fail !!!!!"<<endl;
	}

	cout<<"PLUSES ""pass"<<" !!!!!"<<endl;


	return 0;
}
