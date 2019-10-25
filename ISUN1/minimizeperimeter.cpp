#include<bits/stdc++.h>
using namespace std;
const double EPS=0.0;
const double PI=acos(-1.0);
const double INF=1E9;

map<Point,bool> pool;

double same_d(double x,double y) {
	return between_d(x,y,y);
}

double between_d(double x,double l,double r) {
	return (min(l,r)<=x+EPS && x<=max(l,r)+EPS);
}

struct Point{
	double x,y;
	bool fixed;
	point(double _x,double _y) {
		x=_x; y=_y;
		fixed=false;
	}

	Point(double _x,double _y,bool _fixed){
		x=_x;
		y=_y;
		fixed=_fixed;
	}
	
	bool operator< (point other) const {
		if (y<other.y+EPS) return true;
		if (y+EPS>other.y) return false;
		return x<other.x+EPS;
	}
	bool operator== (point other) const {
		return same_d(x,other.x)&&same_d(y,other.y);
	}
};

struct Vector {
	double x,y;
	Vector() {
		x=y=0.0;
	}
	Vector(double _x,double _y) {
		x=_x; y=_y;
	}
	Vector(Point A) {
		x=A.x; y=A.y;
	}
	Vector(Point A,Point B) {
		x=B.x-A.x; y=B.y-A.y;
	}
};

double cross(Vector u,Vector v) {
	return (u.x*v.y-u.y*v.x);
}

double orientation(point O,point P,point Q) {
	Vector OP(O,P), OQ(O,Q);
	double c=cross(OP,OQ);
	return c;
}

struct Segment {
	Point P,Q;
	line L;
	Segment() {
		point T1; P=Q=T1;
		line T2; L=T2;
	}
	Segment(point _P,point _Q) {
		if (_Q<_P) {
			point T1=_P; _P=_Q; _Q=T1;
		}
		P=_P; Q=_Q;
		line T2(_P,_Q); L=T2;
	}
	bool operator== (Segment other) const {
		return P==other.P&&Q==other.Q;
	}
};

struct Polygon {
	vector<point> P;
	Polygon() {
		P.clear();
	}
	Polygon(vector<point> &_P) {
		P=_P;
	}
	int prev(int idx) {
		return (idx==0?P.size()-1:idx-1);
	}
	int next(int idx) {
		return (idx==P.size()-1?0:idx+1);
	}
	double perimeter() {
		double ret=0;
		for(int i=0;i<P.size();i++) {
			ret+=e_dist(P[i],P[next(i)]);
		}
		return ret;
	}
	double area() {
		double ret=0;
		for(int i=0;i<P.size()i++) {
			ret+=P[i].x*(P[prev(i)].y-P[next(i)].y);
		}
		return ret/2;
	}
};

bool onSegment(point P,Segment S) {
	if (orientation(S.P,S.Q,P)!=0.0) return false;
	return between_d(P.x,S.P.x,S.Q.x) && between_d(P.y,S.P.y,S.Q.y);
}

int outsidePolygon(Point &P,Polygon &A) { //-1 inside,0 onsegment, 1 outside
	int ret=0;
	for(int i=0;i<A.P.size();i++) {
		if (P==A.P[i]) return 0;
		int j=A.next(i);
		if (onSegment(P,segment(A.P[i],A.P[j]))) return 0;
		bool below=(A.P[i].y<P.y);
		if (below!=(A.P[j].y<P.y)) {
			double o=orientation(P,A.P[i],A.P[j]);
			if (o==0.0) return 0;
			if (below==(o>0.0)) ret+=below?1:-1;
		}
	}
	return ret==0?1:-1;
}

Polygon convexHull(vector<point> &pts){
    sort(pts.begin(),pts.end());
    vector<point> hull;
    for(int i=0;i<2;i++){
        int start=(int)hull.size();
        for(auto pt:pts){
            while((int)hull.size()>=start+2&&orientation(hull[(int)hull.size()-1],hull[(int)hull.size()-2],pt)<0.0)hull.pob();
            hull.push_back(pt);
        }
        hull.pop_back();
        reverse(pts.begin(),pts.end());
    }
    if((int)hull.size()==2&&hull[0]==hull[1])hull.pop_back();
    return Polygon(hull);
}


Polygon shrink(vector<Point> perimeter, vector<Point> trees){
	vector<Point> hull;
	bool tree=false;
	for(int i=0;i<perimeter.size();i++){
		while((int)hull.size()>2&&!hull[(int)hull.size()-1].fixed&&orientation(hull[(int)hull.size()-1],hull[(int)hull.size()-2],perimeter[i])>=0.0){
			vector<Point> tempPoint;
			Point start=hull[(int)hull.size()-2];
			Point end=perimeter[i];
			Polygon triangle;
			triangle.P.push_back(hull[(int)hull.size()-2]);
			triangle.P.push_back(hull[(int)hull.size()-1]);
			triangle.P.push_back(perimeter[i]);
			pool.erase(hull[(int)hull.size()-1]);
			hull.pop_back();
			for(auto point:pool){
				if(outsisePolygon(point.first,triangle)<1) tempPoint.push_back(point.first);
			}
			Polygon convex=convexHull(tempPoint);
			for(int i=convex.P.size();i>=0;i--){
				
			}
		}
		hull.push_back(perimeter[i])
	}
	return Polygon(hull);
}

int main(){
	vector<Point> perimeter;
	vector<Point> trees;
	int n,m;
	cin>>n>>m;
	
	//input perimeter coordinate
	for(int i=0;i<n;i++){
		int a,b;
		cin>>a>>b;
		perimeter.push_back(Point(a,b,false));
		pool[Point(a,b,false)]=true;
	}
//	//perimeter coordinate check
//	for(int i=0;i<n;i++){
//		cout<<perimeter[i].x<<" "<<perimeter[i].y<<" "<<perimeter[i].fixed<<endl;
//	}
	
	//input tree coordinate
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		trees.push_back(Point(a,b,true));
		pool[Point(a,b,true)]=true;
	}
//	//perimeter coordinate check
//	for(int i=0;i<m;i++){
//		cout<<trees[i].x<<" "<<trees[i].y<<" "<<trees[i].fixed<<endl;
//	}

	shrink(perimeter,trees);
	
}
