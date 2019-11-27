/* Algorithm for Minimum Cost Flow */
/* O( F V E ) */


struct edge { int to, cap, cost, rev; };
typedef vector<edge> vertex;
typedef vector<vertex> graph;


void compute_flow_dist(int s, vector<int>& dist, vector<pair<int, int>>& prev, graph& g)
{
	fill(dist.begin(), dist.end(), inf);

	dist[s] = 0;
	bool updated = true;

	while(updated) {

		updated = false;

		for(int v = 0; v < (int)g.size(); ++v) {

			if(dist[v] >= inf)
				continue;

			for(int i = 0; i < (int)g.size(); ++i) {

				const auto& e = g[v][i];
				const int cap = e.cap;
				const int cost = e.cost;
				const int w = e.to;

				if(cap <= 0 || dist[w] <= dist[v] + cost)
					continue;

				dist[w] = dist[v] + cost;
				prev[w] = {v, i};
				updated = true;
			}
		}
	}
}

int min_cost_flow(int s, int t, int flow, graph& g)
{
	int sum = 0;
	vector<int> dist(g.size());
	vector<pair<int, int>> prev(g.size());

	while(flow > 0) {

		compute_flow_dist(s, dist, prev, g);

		if(dist[t] >= inf)
			return -1;

		int d = flow;
		for(int v = t; v != s; v = prev[v].first) {
			const int w = prev[v].first;
			const int idx = prev[v].second;
			d = min(d, g[w][idx].cap);
		}

		flow -= d;
		sum += d * dist[t];

		for(int v = t; v != s; v = prev[v].first) {
			const int w = prev[v].first;
			const int idx = prev[v].second;
			auto& e = g[w][idx];
			e.cap -= d;
			g[v][e.rev].cap += d;
		}
	}

	return sum;
}
