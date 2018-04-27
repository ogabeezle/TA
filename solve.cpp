#include<bits/stdc++.h>
using namespace std;
#define in pair<int,int>

int gcd(int a,int b){
	if(b==0) return 1;
	if(a<0) a*=-1;
	if(b<0) b*=-1;
	if(a%b==0) return b;
	else return gcd(b,a%b);
}

bool mt(in a,in b){
	if(a.first*b.second>b.first*a.second) return true;
	else return false;
}

pair<int,in> getbetween(vector<pair<int,in > > convex,map<int,in > check[2][2],int index,pair<int,in > to){
	pair<int,in > from=convex[index],midpoint;
	int mid=(from.first+to.first)/2;
	if(check[0][0].find(mid)==check[0][0].end()){
		//printf("ini get 1 %d %d\n",from.first,to.first);
		int count;
		printf("AskX %d\n",mid);
		scanf("%d",&count);
		int a,b;
		for(int i=0;i<count;i++){
			scanf("%d%d",&a,&b);
			if(b<0){
				b*=-1;
				a*=-1;
			}
			check[0][i][mid].first=a/gcd(a,b);
			check[0][i][mid].second=b/gcd(a,b);
		}
		if(count==2){
			if(!mt(check[0][0][mid],check[0][1][mid])){
				//printf("masuk %d %d %d %d\n",check[0][0][mid].first,check[0][0][mid].second,check[0][1][mid].first,check[0][1][mid].second);
				in temp=check[0][0][mid];
				check[0][0][mid]=check[0][1][mid];
				check[0][1][mid]=temp;
			}
		}
	}
	if(from.first<to.first){
		midpoint=make_pair(mid,check[0][0][mid]);
	}
	else{
		midpoint=make_pair(mid,check[0][1][mid]);
	}
	int num=(midpoint.first-from.first)*(to.second.first*from.second.second-from.second.first*to.second.second)*midpoint.second.second;
	num-=(to.first-from.first)*(midpoint.second.first*from.second.second-from.second.first*midpoint.second.second)*to.second.second;
	if(num/(midpoint.second.second*to.second.second)==0&&num%(midpoint.second.second*to.second.second)==0){
		int min=to.first,max=convex[index+1].first;
		while(1){
			mid=(min+max)/2;
			if(check[0][0].find(mid)==check[0][0].end()){
				int count,a,b;
				printf("AskX %d\n",mid);
				scanf("%d",&count);
				for(int i=0;i<count;i++){
					scanf("%d%d",&a,&b);
					if(b<0){
						b*=-1;
						a*=-1;
					}
					check[0][i][mid].first=a/gcd(a,b);
					check[0][i][mid].second=b/gcd(a,b);
				}
				if(count==2){
					if(!mt(check[0][0][mid],check[0][1][mid])){
						in temp=check[0][0][mid];
						check[0][0][mid]=check[0][1][mid];
						check[0][1][mid]=temp;
					}
				}
			}
			if(from.first<to.first) midpoint=make_pair(mid,check[0][0][mid]);
			else midpoint=make_pair(mid,check[0][1][mid]);
			num=(midpoint.first-from.first)*(to.second.first*from.second.second-from.second.first*to.second.second)*midpoint.second.second;
			num-=(to.first-from.first)*(midpoint.second.first*from.second.second-from.second.first*midpoint.second.second)*to.second.second;
			if(num/(midpoint.second.second*to.second.second)==0&&num%(midpoint.second.second*to.second.second)==0){
				min=(min+max)/2;
				if(max-min==1||min-max==1) return midpoint;
			}
			else{
				max=(min+max)/2;
				//printf("%d %d\n",min,max);
				if(max-min==1||min-max==1){
					if(midpoint.first==max){
						return make_pair(min,check[0][from.first<to.first?0:1][min]);
					}
					else{
						return make_pair(max,check[0][from.first<to.first?0:1][max]);
					}
				}
			
			}
		}
	}
	else return getbetween(convex,check,index,midpoint);
}

vector<pair<int,in> > checki(vector<pair<int,in> > convex,map<int,in > check[2][2]){
	for(int i=0;i<convex.size()-1;i++){
		pair<int,in> from=convex[i],to=convex[i+1],midpoint;
		int mid=(from.first+to.first)/2;
		if(check[0][0].find(mid)==check[0][0].end()){
			int count,a,b;
			printf("AskX %d\n",mid);
			scanf("%d",&count);
			for(int i=0;i<count;i++){
				scanf("%d%d",&a,&b);
				if(b<0){
					b*=-1;
					a*=-1;
				}
				check[0][i][mid].first=a/gcd(a,b);
				check[0][i][mid].second=b/gcd(a,b);
			}
			if(count==2){
				if(!mt(check[0][0][mid],check[0][1][mid])){
					in temp=check[0][0][mid];
					check[0][0][mid]=check[0][1][mid];
					check[0][1][mid]=temp;
				}
			}
		}
		if(from.first<to.first){
			midpoint=make_pair(mid,check[0][0][mid]);
		}
		else{
			midpoint=make_pair(mid,check[0][1][mid]);
		}
		int num=(midpoint.first-from.first)*(to.second.first*from.second.second-from.second.first*to.second.second)*midpoint.second.second;
		num-=(to.first-from.first)*(midpoint.second.first*from.second.second-from.second.first*midpoint.second.second)*to.second.second;
		if(num/(midpoint.second.second*to.second.second)==0&&num%(midpoint.second.second*to.second.second)==0) continue;
		else{
			convex.insert(convex.begin()+i+1,getbetween(convex,check,i,midpoint));
		}
	}
	return convex;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		int max,min,count,a,b;
		vector<pair<int,in > >fix;
		map<int,in > check[2][2];//x=0 y=1, up=0 down=1
		//finding x min
		max=-20;
		min=0;
		while(1){
			printf("AskX %d\n",(max+min)/2);
			scanf("%d",&count);
			for(int i=0;i<count;i++){
				scanf("%d%d",&a,&b);
				if(b<0){
					b*=-1;
					a*=-1;
				}
				check[0][i][(max+min)/2].first=a/gcd(a,b);
				check[0][i][(max+min)/2].second=b/gcd(a,b);
			}
			if(count==0){
				max=(max+min)/2;
			}
			if(count==1){
				check[0][1][(max+min)/2]=check[0][0][(max+min)/2];
				fix.push_back(make_pair((max+min)/2,make_pair(check[0][0][(max+min)/2].first,check[0][0][(max+min)/2].second)));
				break;
			}
			if(count==2){
				if(!mt(check[0][0][(max+min)/2],check[0][1][(max+min)/2])){
					in temp=check[0][0][(max+min)/2];
					check[0][0][(max+min)/2]=check[0][1][(max+min)/2];
					check[0][1][(max+min)/2]=temp;
				}
				min=(max+min)/2;
			}
		}
		//finding x max
		max=20;
		min=0;
		while(1){
			printf("AskX %d\n",(max+min)/2);
			scanf("%d",&count);
			for(int i=0;i<count;i++){
				scanf("%d%d",&a,&b);
				if(b<0){
					b*=-1;
					a*=-1;
				}
				check[0][i][(max+min)/2].first=a/gcd(a,b);
				check[0][i][(max+min)/2].second=b/gcd(a,b);
			}
			if(count==0){
				max=(max+min)/2;
			}
			else if(count==1){
				check[0][1][(max+min)/2]=check[0][0][(max+min)/2];
				fix.push_back(make_pair((max+min)/2,make_pair(check[0][0][(max+min)/2].first,check[0][0][(max+min)/2].second)));
				break;
			}
			else if(count==2){
				if(!mt(check[0][0][(max+min)/2],check[0][1][(max+min)/2])){
					in temp=check[0][0][(max+min)/2];
					check[0][0][(max+min)/2]=check[0][1][(max+min)/2];
					check[0][1][(max+min)/2]=temp;
				}
				min=(max+min)/2;
			}
		}
		fix.push_back(fix[0]);
		fix=checki(fix,check);
		printf("%d\n",fix.size()-1);
		for(int i=0;i<fix.size()-1;i++){
			printf("%d %d\n",fix[i].first,fix[i].second.first/fix[i].second.second);
		}
	}
}
