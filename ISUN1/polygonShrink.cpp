#include<bits/stdc++.h>
using namespace std;
#define pb(x) push_back(x)
#define pob(x) pop_back(x)
#define FOR(i,n) for(int i=0;i<n;i++)
#define gc(x) getchar(x)

double readdouble(){
		double val;
        char ch;int bo=0;val=0;
        for (ch=gc();ch<'0'||ch>'9';ch=gc())if (ch=='-')bo=1;
        for (;ch>='0'&&ch<='9';val=val*10+ch-'0',ch=gc());
        if (ch=='.'){
            double tmp=1;
            for (ch=gc();ch>='0'&&ch<='9';tmp/=10.0,val+=tmp*(ch-'0'),ch=gc());
        }
        if (bo)val=-val;
        return val;
}



const double EPS=0.0;
const double PI=acos(-1.0);
const double INF=1E9;
double between_d(double x,double l,double r) {
	return (min(l,r)<=x+EPS && x<=max(l,r)+EPS);
}
double same_d(double x,double y) {
	return between_d(x,y,y);
}
double dabs(double x) {
	if (x<EPS) return -x; return x;
}
int sign(double x) {
	return (0.0<x)-(x<0.0);
}
/*Point*/
struct point {
	double x,y;
	bool fixed;
	point() {
		x=y=0.0;
		fixed=0;
	}
	point(double _x,double _y,bool _fixed=false) {
		x=_x; y=_y; fixed=_fixed;
	}
	bool operator< (point other) const {
		if (y<other.y+EPS) return true;
		if (y+EPS>other.y) return false;
		return x<other.x+EPS;
	}
	bool operator== (point other) const {
		return same_d(x,other.x)&&same_d(y,other.y);
	}
	string print(){
		return to_string(x)+" "+to_string(y)+" "+to_string(fixed)+"\n";
	}
};
double e_dist(point P1,point P2) {
	return hypot(P1.x-P2.x,P1.y-P2.y);
}
double m_dist(point P1,point P2) {
	return dabs(P1.x-P2.x)+dabs(P1.y-P2.y);
}
bool pointBetween(point P,point L,point R) {
	return (e_dist(L,P)+e_dist(P,R)==e_dist(L,R));
}
point mid(point P,point Q) {
	return point((P.x+Q.x)/2,(P.y+Q.y)/2);
}
/*Vector*/
struct vec {
	double x,y;
	vec() {
		x=y=0.0;
	}
	vec(double _x,double _y) {
		x=_x; y=_y;
	}
	vec(point A) {
		x=A.x; y=A.y;
	}
	vec(point A,point B) {
		x=B.x-A.x; y=B.y-A.y;
	}
};
vec scale(vec v,double s) {
	return vec(v.x*s,v.y*s);
}
vec flip(vec v) {
	return vec(-v.x,-v.y);
}
double dot(vec u,vec v) {
	return (u.x*v.x+u.y*v.y);
}
double cross(vec u,vec v) {
	return (u.x*v.y-u.y*v.x);
}
double norm_sq(vec v) {
	return (v.x*v.x+v.y*v.y);
}
point translate(point P,vec v) {
	return point(P.x+v.x,P.y+v.y);
}
point rotate(point P,point O,double angle) {
	vec v(O); P=translate(P,flip(v));
	return translate(point(P.x*cos(angle)-P.y*sin(angle),P.x*sin(angle)+P.y*cos(angle)),v);
}
double angle(point A,point O,point B) {
	vec OA(O,A), OB(O,B);
	return acos(dot(OA,OB)/sqrt(norm_sq(OA)*norm_sq(OB)));
}
double orientation(point O,point P,point Q) {
	vec OP(O,P), OQ(O,Q);
	double c=cross(OP,OQ);
	return c;
}
/*Line*/
struct line {
	double a,b,c;
	line() {
		a=b=c=0.0;
	}
	line(double _a,double _b,double _c) {
		a=_a; b=_b; c=_c;
	}
	line(point P1,point P2) {
		if (P2<P1) {
			point T; T=P1; P1=P2; P2=T;
		}
		if (same_d(P1.x,P2.x)) a=1.0, b=0.0, c=-P1.x;
		else a=-(P1.y-P2.y)/(P1.x-P2.x), b=1.0, c=-(a*P1.x)-P1.y;
	}
	line (point P,double slope) {
		if (same_d(slope,INF)) a=1.0, b=0.0, c=-P.x;
		else a=-slope, b=1.0, c=-(a*P.x)-P.y;
	}
	bool operator== (line other) const {
		return same_d(a,other.a)&&same_d(b,other.b)&&same_d(c,other.c);
	}
	double slope() {
		if (same_d(b,0.0)) return INF;
		return -(a/b);
	}
};
bool paralel(line L1,line L2) {
	return same_d(L1.a,L2.a)&&same_d(L1.b,L2.b);
}
bool intersection(line L1,line L2,point &P) {
	if (paralel(L1,L2)) return false;
	P.x=(L2.b*L1.c-L1.b*L2.c)/(L2.a*L1.b-L1.a*L2.b);
	if (same_d(L1.b,0.0)) P.y=-(L2.a*P.x+L2.c);
	else P.y=-(L1.a*P.x+L1.c);
	return true;
}
double pointToLine(point P,point A,point B,point &C) {
	vec AP(A,P), AB(A,B);
	double u=dot(AP,AB)/norm_sq(AB);
	C=translate(A,scale(AB,u));
	return e_dist(P,C);
}
double lineToLine(line L1,line L2) {
	if (!paralel(L1,L2)) return 0.0;
	return dabs(L2.c-L1.c)/sqrt(L1.a*L1.a+L1.b*L1.b);
}
/*Line Segment*/
struct segment {
	point P,Q;
	line L;
	segment() {
		point T1; P=Q=T1;
		line T2; L=T2;
	}
	segment(point _P,point _Q) {
		if (_Q<_P) {
			point T1=_P; _P=_Q; _Q=T1;
		}
		P=_P; Q=_Q;
		line T2(_P,_Q); L=T2;
	}
	bool operator== (segment other) const {
		return P==other.P&&Q==other.Q;
	}
};
bool onSegment(point P,segment S) {
	if (orientation(S.P,S.Q,P)!=0.0) return false;
	return between_d(P.x,S.P.x,S.Q.x) && between_d(P.y,S.P.y,S.Q.y);
}

/*Polygon CW*/
struct polygon {
	vector<point> P;
	polygon() {
		P.clear();
	}
	polygon(vector<point> &_P) {
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
		FOR(i,P.size()) {
			ret+=e_dist(P[i],P[next(i)]);
		}
		return ret;
	}
	double area() {
		double ret=0;
		FOR(i,P.size()) {
			ret+=P[i].x*(P[prev(i)].y-P[next(i)].y);
		}
		return ret/2;
	}
};

polygon convexHull(vector<point> &pts){
    sort(pts.begin(),pts.end());
    vector<point> hull; 
    for(int i=0;i<2;i++){
        int start=(int)hull.size();
        for(auto pt:pts){
            while((int)hull.size()>=start+2&&orientation(hull[(int)hull.size()-1],hull[(int)hull.size()-2],pt)<=0.0)hull.pob();
            hull.pb(pt);
        }
        hull.pop_back();
        reverse(pts.begin(),pts.end());
    }
    if((int)hull.size()==2&&hull[0]==hull[1])hull.pob();
    return polygon(hull);
}

int inSimplePolygon(point P,polygon &A) { //-1 inside,0 onsegment, 1 outside
	int ret=0;
	FOR(i,A.P.size()) {
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

bool s_intersection(segment S1,segment S2) {
	int o1=sign(orientation(S1.P,S1.Q,S2.P));
	int o2=sign(orientation(S1.P,S1.Q,S2.Q));
	int o3=sign(orientation(S2.P,S2.Q,S1.P));
	int o4=sign(orientation(S2.P,S2.Q,S1.Q));
	if (o1!=o2 && o3!=o4) return true;
	if (o1==0 && onSegment(S2.P,S1)) return true;
	if (o2==0 && onSegment(S2.Q,S1)) return true;
	if (o3==0 && onSegment(S1.P,S2)) return true;
	if (o4==0 && onSegment(S2.Q,S2)) return true;
	return false;
}



bool isIntersect(vector<point> hull,point a, point b){
//	cout<<a.print()<<b.print()<<endl;
	bool flag=false;
	bool found=false;
//	cout<<"asdasd"<<endl;
	for(int i=2;i<hull.size();i++){
		if(hull[i].fixed) found=1;
		if(!found) continue;
		if((a==hull[i])||(b==hull[i])||(a==hull[i-1])||(b==hull[i-1])) continue;
//		cout<<hull[i].print()<<hull[i-1].print();
		if(s_intersection(segment(a,b),segment(hull[i],hull[i-1]))){
			flag=true;
			break;
		}
	}
//	cout<<flag<<endl;
	return flag;
}

//code start here
map<point,bool> pool;
bool pointget;

void fixing(vector<point>&hull){
	if(!pointget){
		pointget=true;
		return;
	}
	for(int i=hull.size()-1;i>=0;i--){
		if(hull[i].fixed) break;
		pool.erase(hull[i]);
		hull[i].fixed=true;
		pool[hull[i]]=true;
	}
}

void remove(vector<point>&hull, point pt){
	point start=hull[hull.size()-2];
	pool[start]=true;
	point end=pt;
	pool[end]=true;
	pool.erase(hull[hull.size()-1]);
	polygon temp=polygon();
	temp.P.pb(hull[hull.size()-2]);
	temp.P.pb(hull[hull.size()-1]);
	temp.P.pb(pt);
	vector<point> points;
//	cout<<"ini segitiga"<<endl;
//	cout<<temp.P[0].print()<<temp.P[1].print()<<temp.P[2].print()<<endl;
	for(auto it:pool){
		point a=it.first;
//		cout<<a.print();
		if(inSimplePolygon(it.first,temp)!=1) {
			points.pb(it.first);
//			cout<<it.first.x<<it.first.y<<it.first.fixed<<endl;
		}
	}
	hull.pob(); 
//	cout<<"masuk"<<endl;
	temp=convexHull(points);
//	cout<<"keluar"<<endl;
	for(int j=0;j<temp.P.size();j++){
		if(temp.P[j]==start){
			bool done=0;
			if(temp.P[temp.next(j)]==end){
				while(1){
					j=temp.prev(j);
					if(temp.P[j]==end) break;
					while(!done&&(int)hull.size()>=2&&!hull[hull.size()-1].fixed&&(orientation(hull[(int)hull.size()-1],hull[(int)hull.size()-2],temp.P[j])<=0.0||isIntersect(hull,hull[hull.size()-1],temp.P[j]))){
						remove(hull,temp.P[j]);
					}
					done=1;
					if(temp.P[j].fixed){
						fixing(hull);
					}
					hull.pb(temp.P[j]);
				}
			}
			else{
				int a=100;
				while(a--){
					j=temp.next(j);
//					cout<<temp.P[j].print()<<endl;
					if(temp.P[j]==end) break;
					while(!done&&(int)hull.size()>=2&&!hull[hull.size()-1].fixed&&(orientation(hull[(int)hull.size()-1],hull[(int)hull.size()-2],temp.P[j])<=0.0||isIntersect(hull,hull[hull.size()-1],temp.P[j]))){
						remove(hull,temp.P[j]);
					}
					done=1;
					if(temp.P[j].fixed){
						fixing(hull);
					}
					hull.pb(temp.P[j]);
				}
			}
			break;
		}
	}
}

polygon shrink(polygon &perimeter){
	int hasTree=-1;
	vector<point> hull;
	vector<point> adder;
	for(int i=0;i<perimeter.P.size();i++){
		point pt=perimeter.P[i];
		if(!pointget) adder.pb(pt);
		while((int)hull.size()>=2&&!hull[hull.size()-1].fixed&&(orientation(hull[(int)hull.size()-1],hull[(int)hull.size()-2],pt)<=0.0||isIntersect(hull,hull[hull.size()-1],pt))){
			remove(hull,pt);
		}
        hull.pb(pt);
	}
	vector<point> fixedhull(hull);
	
	int count;
	for(count=0;count<fixedhull.size();count++){
		if(fixedhull[count].fixed){
			count++;
			break;
		}
	}
	
//	cout<<"\n\n\n\n"<<count<<endl;
	
	for(int i=0;i<adder.size();i++){
//		cout<<i<<endl;
		while((int)fixedhull.size()>=2&&!fixedhull[fixedhull.size()-1].fixed&&(orientation(fixedhull[(int)fixedhull.size()-1],fixedhull[(int)fixedhull.size()-2],adder[i])<=0.0||isIntersect(fixedhull,fixedhull[fixedhull.size()-1],adder[i]))){
//			cout<<"masuk"<<endl;
			remove(fixedhull,adder[i]);
//			cout<<"keluar"<<endl;
		}
        fixedhull.pb(adder[i]);
	}
	return polygon(fixedhull);
}

int main(){
//	cout<<s_intersection(segment(point(0,0),point(1,1)),segment(point(0,0),point(0,1)))<<endl;
	int kase=1;
	int n,m;
	while(cin>>n){
		cin>>m;
		pointget=0;
		pool.clear();
		polygon perimeter;
		vector<point> trees;
		
		//input perimeter coordinate
		for(int i=0;i<n;i++){
			double a=readdouble(),b=readdouble();
//			cin>>a>>b;
			perimeter.P.push_back(point(a,b,false));
			pool[point(a,b,false)]=true;
		}
		//perimeter coordinate check
//		for(int i=0;i<n;i++){
//			cout<<perimeter.P[i].x<<" "<<perimeter.P[i].y<<" "<<perimeter.P[i].fixed<<endl;
//		}
		
		//input tree coordinate
		for(int i=0;i<m;i++){
			double a=readdouble(),b=readdouble();
//			cin>>a>>b;
			trees.push_back(point(a,b,true));
			pool[point(a,b,true)]=true;
		}
		//perimeter coordinate check
//		for(int i=0;i<m;i++){
//			cout<<trees[i].x<<" "<<trees[i].y<<" "<<trees[i].fixed<<endl;
//		}
		
		polygon hasil=shrink(perimeter);
//		cout<<"\t\t\tasdasd"<<endl;
		pointget=0;
//		for(int i=0;i<hasil.P.size();i++){
//			cout<<hasil.P[i].x<<"|"<<hasil.P[i].y<<" ";//<<hasil.P[i].fixed<<" ";
////			pool[hasil.P[i]]=true;
//		}cout<<endl;
		for(int i=0;i<n;i++){
			point a=point(perimeter.P[i].x,perimeter.P[i].y,true);
			point b=point(perimeter.P[i].x,perimeter.P[i].y,false);
			if(!pool[a]&&!pool[b])pool[b]=true;
		}
		
//		hasil=shrink(perimeter);
//		cout<<"asdasd"<<endl;
		for(int i=0;i<hasil.P.size();i++){
			if(!hasil.P[i].fixed){
				hasil.P.erase(hasil.P.begin()+i);i--;
				continue;
			}
			cout<<hasil.P[i].x<<"|"<<hasil.P[i].y<<" ";
		}
		printf("Case #%d: %.3lf\n",kase++,hasil.perimeter());
	}
}

