#include <message.h>
#include ".h"

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
using namespace std;

typedef long long i64;
const int inf = (int)1.05e9;

void worker(int id, int worker_count, int master_id)
{
	const int n = 1e9;
	const int left = round(((double)n / worker_count) * id);
	const int right = round(((double)n / worker_count) * (id + 1));

	PutLL(master_id, left);
	PutLL(master_id, right);
	Send(master_id);
}

void master(int id, int worker_count)
{
	for(int i = 0; i < worker_count; ++i) {
		i64 a, b;
		Receive(i);
		a = GetLL(i);
		b = GetLL(i);
	}

	i64 ans = 0;

	printf("%lld\n", ans);
}

int main()
{
	const int node_count = NumberOfNodes();
	const int master_id = node_count - 1;
	const int id = MyNodeId();

	if(id == master_id) {
		master(id, node_count - 1);
	} else {
		worker(id, node_count - 1, master_id);
	}
}
