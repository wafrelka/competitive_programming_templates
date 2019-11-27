/* Algorithm for Centroid Decomposition */


typedef vector<int> vertex;
typedef vector<vertex> graph;


int compute_subtree_size(int v, int from, vector<int>& subtree_size,
	vector<bool>& centroid, graph& g)
{
	int c = 1;
	for(const auto& e : g[v]) {
		const int w = e;
		if(w == from || centroid[w])
			continue;
		c += compute_subtree_size(w, v, subtree_size, centroid, g);
	}
	subtree_size[v] = c;
	return c;
}

pair<int, int> search_centroid(int v, int from, int size,
	vector<int>& subtree_size, vector<bool>& centroid, graph& g)
{
	pair<int, int> ans = {(int)g.size() * 2, -1};
	int sum = 1, ma = 0;

	for(const auto& e : g[v]) {

		const int w = e;
		if(w == from || centroid[w])
			continue;

		ans = min(ans, search_centroid(w, v, size, subtree_size, centroid, g));
		ma = max(ma, subtree_size[w]);
		sum += subtree_size[w];
	}

	ma = max(ma, size - sum);
	ans = min(ans, {ma, v});
	return ans;
}

void solve_subproblem(int v, vector<int>& subtree_size, vector<bool>& centroid, graph& g)
{
	compute_subtree_size(v, -1, subtree_size, centroid, g);
	const int c = search_centroid(v, -1, subtree_size[v], subtree_size, centroid, g).second;
	centroid[c] = true;

	for(const auto& e : g[c]) {
		const int w = e;
		if(centroid[w])
			continue;
		solve_subproblem(w, subtree_size, centroid, g);
	}

	// TODO

	centroid[c] = false;
}
