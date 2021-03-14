/* One Path Algorithm for Strongly Connected Components */


typedef vector<int> vertex;
typedef vector<vertex> graph;


void scc_visit(int v, vector<vector<int>>& scc, stack<int>& st, vector<bool>& in_st,
	vector<int>& low, vector<int>& num, int& idx, graph& g)
{
	low[v] = num[v] = ++idx;
	st.push(v);
	in_st[v] = true;

	for(const auto& e : g[v]) {

		const int w = e;

		if(num[w] == 0) {
			scc_visit(w, scc, st, in_st, low, num, idx, g);
			low[v] = min(low[v], low[w]);
		} else if(in_st[w]) {
			low[v] = min(low[v], num[w]);
		}
	}

	if(low[v] != num[v])
		return;

	scc.push_back(vector<int>());
	while(true) {
		const int w = st.top();
		st.pop();
		in_st[w] = false;
		scc.back().push_back(w);
		if(v == w)
			break;
	}

}

vector<vector<int>> compute_scc(graph& g)
{
	const int n = g.size();
	vector<int> num(n), low(n);
	stack<int> st;
	vector<bool> in_st(n);
	int idx = 0;
	vector<vector<int>> scc;

	for(int v = 0; v < n; ++v) {
		if(num[v] == 0)
			scc_visit(v, scc, st, in_st, low, num, idx, g);
	}

	return move(scc);
}
