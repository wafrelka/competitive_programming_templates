/* Dinic Algorithm for Maximum Flow */
/* generic case: O( E V^2 ) */
/* network with unit capacities: O( min{E V^(2/3), E^(3/2)} ) */
/* network with each vertex (except for s, t)
    having a single (entering or outgoing) edge of capacity 1: O( E sqrt(V) ) */


struct edge { int to, cap, rev; };
typedef vector<edge> vertex;
typedef vector<vertex> graph;


void compute_level(int s, vector<int>& level, graph& g)
{
	level.resize(g.size());
	fill(level.begin(), level.end(), -1);

	queue<int> q;
	level[s] = 0;
	q.push(s);

	while(!q.empty()) {

		const int v = q.front();
		q.pop();

		for(const auto& e : g[v]) {

			const int w = e.to;
			const int c = e.cap;

			if(c <= 0 || level[w] != -1)
				continue;
			level[w] = level[v] + 1;
			q.push(w);
		}
	}
}

int compute_flow_path(int v, int t, int f, vector<int>& iter, vector<int>& level, graph& g)
{
	if(v == t)
		return f;

	for(int& i = iter[v]; i < (int)g[v].size(); ++i) {

		auto& e = g[v][i];
		const int c = e.cap;
		const int w = e.to;

		if(c <= 0 || level[v] >= level[w])
			continue;

		const int d = compute_flow_path(w, t, min(f, c), iter, level, g);
		if(d <= 0)
			continue;
		e.cap -= d;
		g[w][e.rev].cap += d;
		return d;
	}

	return 0;
}

int max_flow(int s, int t, graph& g)
{
	int flow = 0;
	vector<int> level(g.size());
	vector<int> iter(g.size());

	while(true) {

		compute_level(s, level, g);
		if(level[t] == -1)
			break;
		fill(iter.begin(), iter.end(), 0);
		while(true) {
			const int f = compute_flow_path(s, t, inf, iter, level, g);
			flow += f;
			if(f <= 0)
				break;
		}
	}

	return flow;
}
