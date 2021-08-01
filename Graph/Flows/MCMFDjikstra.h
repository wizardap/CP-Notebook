/*
  Source : skyvn97
  Modified by WizardAP
  Verification :
      - https://oj.vnoi.info/problem/kway
*/
/*
    Warning ! :
      + Create a fake source and fake sink to use this template
      + Can't use with negative weight 
*/
const LL inf = 1e18;
struct MCMF
{
	struct Edge
	{
		int u, v;
		LL  cap, cost, flow;
		Edge(int u = 0, int v = 0, LL cap = 0, LL cost = 0): u(u), v(v), cap(cap), cost(cost), flow(0) {};
		LL rem() { return cap - flow;}
	};
	vi<vi<int>> adj;
	vi<Edge> eds;
	vi<int> trace;
	vi<LL> dist;
	int n;
	priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>>> pq;
	MCMF(int _n = 0)
	{
		n = _n;
		adj.assign(n + 7, vi<int>());
		eds.clear();
		trace.assign(n + 7, -1);
		dist.assign(n + 7, inf);
	}
	void addEdge(int u, int v, LL cap, LL cost)
	{
		adj[u].pb(sz(eds)); eds.pb(Edge(u, v, cap, cost));
		adj[v].pb(sz(eds)); eds.pb(Edge(v, u, 0, -cost));
	}
	bool path(int s, int t)
	{
		for (int i = 0; i <= n; i++) {
			dist[i] = inf;
			trace[i] = -1;
		}
		assert(pq.empty());
		dist[s] = 0;
		pq.push(make_pair(dist[s], s));
		while (!pq.empty())
		{
			int u = pq.top().sd;
			LL du = pq.top().ft;
			pq.pop();
			if (du != dist[u]) continue;
			rof(id, adj[u])
			if (eds[*id].rem() > 0)
			{
				int v = eds[*id].v;
				LL w = eds[*id].cost;
				if (minimize(dist[v], dist[u] + w))
				{
					pq.push(make_pair(dist[v], v));
					trace[v] = *id;
				}
			}
		}
		return trace[t] != -1;
	}
	pair<LL, LL> answer(int s, int t)
	{
		LL totflow = 0, totcost = 0;
		while (path(s, t))
		{
			LL minflow = inf;
			for (int u = t; u != s; u = eds[trace[u]].u) minimize(minflow, eds[trace[u]].rem());
			for (int u = t; u != s; u = eds[trace[u]].u) {
				eds[trace[u]].flow += minflow;
				eds[trace[u] ^ 1].flow -= minflow;
			}
			totflow += minflow;
			totcost += minflow * dist[t];
		}
		return make_pair(totflow, totcost);
	}
} ;
