#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <numeric>

/* debug macros */
#ifdef WAFDAYO
#define DBG_LINE() {std::cerr<<"\e[2m[L"<<__LINE__<<"]\e[m ";}
#define DBG_PRINT(s,t,u) {std::cerr<<(s)<<" \e[2m=\e[m \e[1m"<<(t)<<"\e[m"<<(u);}
#define SELECT_7TH(x1,x2,x3,x4,x5,x6,x7,...) x7
#define dbg1(x1) DBG_PRINT(#x1,x1,std::endl)
#define dbg2(x1,x2) DBG_PRINT(#x1,x1,", ")dbg1(x2)
#define dbg3(x1,x2,x3) DBG_PRINT(#x1,x1,", ")dbg2(x2,x3)
#define dbg4(x1,x2,x3,x4) DBG_PRINT(#x1,x1,", ")dbg3(x2,x3,x4)
#define dbg5(x1,x2,x3,x4,x5) DBG_PRINT(#x1,x1,", ")dbg4(x2,x3,x4,x5)
#define dbg6(x1,x2,x3,x4,x5,x6) DBG_PRINT(#x1,x1,", ")dbg5(x2,x3,x4,x5,x6)
#define dbg(...) DBG_LINE()\
SELECT_7TH(__VA_ARGS__,dbg6,dbg5,dbg4,dbg3,dbg2,dbg1)(__VA_ARGS__)
#else
#define dbg(...) {}
#endif

/* utility functions */
struct read_item{read_item(){};
template<class T>operator T(){T t;std::cin>>t;return t;}};
char splf(int i,int n){return(i+1<n)?' ':'\n';};
template<bool up>
struct _RI{int i;_RI(int a):i(a){}
int operator*(){return i;}void operator++(){i+=(up?1:-1);}
bool operator!=(const _RI& r){return up?i<r.i:i>=r.i;}};
template<bool up>
struct _RX{_RI<up> x,y;_RI<up> begin(){return x;}_RI<up> end(){return y;}
_RX(int a,int b):x(up?a:(a-1)),y(b){}_RX(int a):_RX(up?0:a,up?a:0){}};
typedef _RX<true> range;
typedef _RX<false> revrange;

/* types and constants */
typedef long long i64;
// const i64 inf = (i64)1.05e18;
// const int inf = (int)1.05e9;

using namespace std;

int main() {

	return 0;
}

/* wafdayo~~~ */
