#include<bits/stdc++.h>
using namespace std;

int main(){
	srand(time(NULL));
	int n=500,m=50;
	cin>>m;
	cout<<n<<" "<<m<<endl;
	for(int i=0;i<125;i++){
		cout<<-10000+i*160<<" "<<-10000<<endl;
	}
	for(int i=0;i<125;i++){
		cout<<10000<<" "<<-10000+i*160<<endl;
	}
	for(int i=0;i<125;i++){
		cout<<10000-i*160<<" "<<10000<<endl;
	}
	for(int i=0;i<125;i++){
		cout<<-10000<<" "<<10000-i*160<<endl;
	}
	for(int i=0;i<m;i++){
		cout<<rand() % 20001 - 10000<<" "<<rand() % 20001 - 10000<<endl;
	}
}
