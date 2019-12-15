#include<bits/stdc++.h>
using namespace std;

string dp[70000];
bool dpp[70000];

string generate_query(int s){
	if(dpp[s]){
		return dp[s];
	}
	string ans="";
	for (int j = 0; j < 65537; ++j) {
		int bitstring = s & j;
		short count = 0;
		for (count = 0; bitstring; bitstring >>= 1) {
			if(bitstring & 1) count++;
		}
		ans += '0' + (int)(count&1);
	}
	dp[s]=ans;
	dpp[s]=true;
	return ans;
}


//return hamming_distance, minimum_hamming_count
pair<int,int> count_hamming_distance(vector<int> arr, int real_M){	
	vector<int> distance(real_M,0);
	for(int i=0;i<arr.size();i++){
		string temp = generate_query(arr[i]);
		for(int j=1;j<real_M;j++){
			if(temp[j]=='1') distance[j]++;
		}
	}
	int mini=INT_MAX;
	int min_count;
	for(int i=1;i<real_M;i++){
		if(mini==distance[i]){
			min_count++;
			mini=distance[i];
		}
		else if(mini>distance[i]){
			min_count==1;
			mini=distance[i];
		}
	}
	return make_pair(mini,min_count);
}


vector<int> generate_code_order(int M, int d){
	int hamming_distance=-1;
	vector<int> code_order;
	map<int,bool> check; //check apakah sebuah query sudah di masukan pada code order
	while(hamming_distance<d){
		pair<int,int> maxi=make_pair(-1,0);
		int idx;
		for(int i=1;i<M;i++){
			if(check[i]) continue;
			code_order.push_back(i);
			pair<int,int> temp=count_hamming_distance(code_order,M);
			cout<<i<<" "<<temp.first<<" "<<temp.second<<endl;
			if(maxi.first<temp.first){
				idx=i;
				maxi=temp;
			}
			else if(maxi.first==temp.first&&maxi.second>temp.second){
				idx=i;
				maxi=temp;
			}
			code_order.pop_back();
		}
		cout<<idx<<endl;
		code_order.push_back(idx);
		hamming_distance=maxi.first;
		check[idx]=true;
	}
	return code_order;
}

int main(){
//	memset(dpp,0,sizeof dpp);
//	vector<int> arr;
//	arr.push_back(1);
//	arr.push_back(2);
//	arr.push_back(4);
//	cout<<count_hamming_distance(arr,8).first<<endl;
//	
	int M=65536;
	
	vector<int> xx=generate_code_order(M,3);
	for(int i=0;i<xx.size();i++){
		cout<<xx[i]<<endl;//" "<<generate_query(xx[i]).substr(0,M)<<endl;
	}
	cout<<xx.size()<<endl;
}
