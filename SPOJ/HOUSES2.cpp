#include<bits/stdc++.h>
using namespace std;
const double EPS=0.0;
const double INF=1E9;
#define V 11

double between_d(double x,double l,double r) {
	return (min(l,r)<=x+EPS && x<=max(l,r)+EPS);
}
double same_d(double x,double y) {
	return between_d(x,y,y);
}

int sign(double x) {
	return (0.0<x)-(x<0.0);
}


struct Point{
	int x;
	int y;
	Point() {
		x=y=0.0;
	}
	Point(double _x,double _y) {
		x=_x; y=_y;
	}
	bool operator< (Point other) const {
		if (y<other.y+EPS) return true;
		if (y+EPS>other.y) return false;
		return x<other.x+EPS;
	}
	bool operator== (Point other) const {
		return same_d(x,other.x)&&same_d(y,other.y);
	}
	bool operator !=(Point other)const{
		return !(Point(x,y)==other);
	}

};

/*Vector*/
struct Vec {
	double x,y;
	Vec() {
		x=y=0.0;
	}
	Vec(double _x,double _y) {
		x=_x; y=_y;
	}
	Vec(Point A) {
		x=A.x; y=A.y;
	}
	Vec(Point A,Point B) {
		x=B.x-A.x; y=B.y-A.y;
	}
};

double cross(Vec u,Vec v) {
	return (u.x*v.y-u.y*v.x);
}


double orientation(Point O,Point P,Point Q) {
	Vec OP(O,P), OQ(O,Q);
	double c=cross(OP,OQ);
	return c;
}

struct Line {
	double a,b,c;
	Line() {
		a=b=c=0.0;
	}
	Line(double _a,double _b,double _c) {
		a=_a; b=_b; c=_c;
	}
	Line(Point P1,Point P2) {
		if (P2<P1) {
			Point T; T=P1; P1=P2; P2=T;
		}
		if (same_d(P1.x,P2.x)) a=1.0, b=0.0, c=-P1.x;
		else a=-(P1.y-P2.y)/(P1.x-P2.x), b=1.0, c=-(a*P1.x)-P1.y;
	}
	Line (Point P,double slope) {
		if (same_d(slope,INF)) a=1.0, b=0.0, c=-P.x;
		else a=-slope, b=1.0, c=-(a*P.x)-P.y;
	}
	bool operator== (Line other) const {
		return same_d(a,other.a)&&same_d(b,other.b)&&same_d(c,other.c);
	}
	double slope() {
		if (same_d(b,0.0)) return INF;
		return -(a/b);
	}
};


struct Segment {
	Point P,Q;
	Line L;
	Segment() {
		Point T1; P=Q=T1;
		Line T2; L=T2;
	}
	Segment(Point _P,Point _Q) {
		if (_Q<_P) {
			Point T1=_P; _P=_Q; _Q=T1;
		}
		P=_P; Q=_Q;
		Line T2(_P,_Q); L=T2;
	}
	bool operator== (Segment other) const {
		return P==other.P&&Q==other.Q;
	}
};

bool onSegment(Point P,Segment S) {
	if (orientation(S.P,S.Q,P)!=0.0) return false;
	return between_d(P.x,S.P.x,S.Q.x) && between_d(P.y,S.P.y,S.Q.y);
}


bool s_intersection(Segment S1,Segment S2) {
	int o1=sign(orientation(S1.P,S1.Q,S2.P));
	int o2=sign(orientation(S1.P,S1.Q,S2.Q));
	int o3=sign(orientation(S2.P,S2.Q,S1.P));
	int o4=sign(orientation(S2.P,S2.Q,S1.Q));
	if (o1!=o2 && o3!=o4) return true;
	if (o1==0 && onSegment(S2.P,S1)) return true;
	if (o2==0 && onSegment(S2.Q,S1)) return true;
	if (o3==0 && onSegment(S1.P,S2)) return true;
	if (o4==0 && onSegment(S1.Q,S2)) return true;
	return false;
}


double graph[11][11];
vector<Segment> segment;

void generate_segment(Point arr[]){
	segment.push_back(Segment(arr[2],arr[3]));
	segment.push_back(Segment(arr[2],arr[4]));
	segment.push_back(Segment(arr[3],arr[4]));
	segment.push_back(Segment(arr[5],arr[6]));
	segment.push_back(Segment(arr[6],arr[7]));
	segment.push_back(Segment(arr[5],arr[7]));
	segment.push_back(Segment(arr[8],arr[9]));
	segment.push_back(Segment(arr[8],arr[10]));
	segment.push_back(Segment(arr[9],arr[10]));
}

double e_dist(Point P1,Point P2) {
	return hypot(P1.x-P2.x,P1.y-P2.y);
}

void generate_graph(Point arr[]){
	generate_segment(arr);
	for(int i=0;i<11;i++){
		for(int j=i+1;j<11;j++){
			if(arr[i]==arr[j]) continue;
			int count =0;
			int segCount=0,segCountRev=0;
			vector<Point> collision,collisionRev;
			bool kill=false;
			for(int k=0;k<9;k++){
				if(s_intersection(Segment(arr[i],arr[j]),segment[k])){
					count++;
					if(segment[k].P!=arr[i]&&segment[k].Q!=arr[i]&&segment[k].P!=arr[j]&&segment[k].Q!=arr[j]){
						kill=true;
						break;
					}
					if(segment[k].P==arr[j]){
						segCount++;
						collision.push_back(segment[k].Q);
					}
					else if(segment[k].Q==arr[j]){
						segCount++;
						collision.push_back(segment[k].P);
					}
					if(segment[k].P==arr[i]){
						segCountRev++;
						collisionRev.push_back(segment[k].Q);
					}
					else if(segment[k].Q==arr[i]){
						segCountRev++;
						collisionRev.push_back(segment[k].P);
					}
				}
			}
			if(kill) continue;
			if(i==0&&j==1){
				if(segCount==count){
					double dist=e_dist(arr[i],arr[j]);
					graph[i][j]=dist;
					graph[j][i]=dist;
				}
			}
			else{
				int kd=0,ld=0;
				int kd1=0,ld1=0;
				int ori=orientation(arr[i],arr[j],arr[j]);
				for(int l=0;l<collision.size();l++){
					if(ori>orientation(arr[i],arr[j],collision[l])){
						kd++;
					}
					else if(ori<orientation(arr[i],arr[j],collision[l])){
						ld++;
					}
				}
				ori=orientation(arr[j],arr[i],arr[i]);
				for(int l=0;l<collisionRev.size();l++){
					if(ori>orientation(arr[j],arr[i],collisionRev[l])){
						kd1++;
					}
					else if(ori<orientation(arr[j],arr[i],collisionRev[l])){
						ld1++;
					}
				}
				if((ld==0||kd==0)&&(ld1==0||kd1==0)){
					double dist=e_dist(arr[i],arr[j]);
					graph[i][j]=dist;
					graph[j][i]=dist;					
				}
			}
			
		}
		
	}
}

int minDistance(double dist[], bool sptSet[]) {
    double min = INT_MAX;
	int min_index; 
  
    for (int v = 0; v < V; v++){
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;        	
		}
	}
  
    return min_index; 
}

double dijkstra(double graph[V][V], int src) { 
    double dist[V];
  
    bool sptSet[V];
    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX, sptSet[i] = false; 
	}
        
    dist[src] = 0; 
    
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);   
        sptSet[u] = true;   
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) 
                dist[v] = dist[u] + graph[u][v];
		} 
    }
    return dist[1];
} 

int main(){
	int tc;
	cin>>tc;
	while(tc--){
		memset(graph,-1,sizeof graph);
		segment.clear();
		Point node[11];
		for(int j=0;j<11;j++){
			cin>>node[j].x>>node[j].y;
		}
		generate_graph(node);
		printf("%.5lf\n",dijkstra(graph,0));
	}
}
