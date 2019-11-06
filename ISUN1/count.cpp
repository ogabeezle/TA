#include<iostream>
#include<fstream>
using namespace std;

int main(){
	double hasil=0;
	double temp;
	for(int i=0;i<100;i++){
		cin>>temp;
		hasil+=temp;
	}
	ofstream myfile;
	myfile.open ("hasil.txt",ios::app);
//	myfile << time<<endl;
	myfile<<hasil/100<<endl;
	myfile.close();
}
