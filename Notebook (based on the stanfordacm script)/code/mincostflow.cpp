#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define DEBUG true
#define MAXN 301
#define INF 1e9

int n, source, destiny;
vector<int> adj[MAXN];
int capacity[MAXN][MAXN];
int cost[MAXN][MAXN];
vector<int> dist;
vector<int> parent;
vector<bool> in_queue;

void add_edge(int a, int b, int c, int d)
{
  adj[a].pb(b); // aresta normal
  capacity[a][b] = c;
  cost[a][b] = d;
  adj[b].pb(a); // aresta do grafo residual
  capacity[b][a] = 0;
  cost[b][a] = -d;
}
bool dijkstra(int s) // rodando o dijkstra, terei o caminho de custo minimo
{                    // que eu consigo passando pelas arestas que possuem capacidade > 0
  dist.assign(MAXN, INF);
  parent.assign(MAXN, -1);
  in_queue.assign(MAXN, false);
  dist[s] = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    in_queue[u] = false;
    for (auto const &v : adj[u])
    {
      if (capacity[u][v] && dist[v] > dist[u] + cost[u][v])
      {
        dist[v] = dist[u] + cost[u][v];
        parent[v] = u;
        if (!in_queue[v])
        {
          in_queue[v] = true;
          q.push(v);
        }
      }
    }
  }
  return dist[destiny] != INF; // se eu cheguei em destiny por esse caminho, ainda posso passar fluxo
}
int min_cost_flow()
{
  int flow = 0, cost = 0;
  while (dijkstra(source)) // rodo um dijkstra para saber qual o caminho que irei agora
  {
    int curr_flow = INF, curr = destiny;
    while (curr != source) // com isso, vou percorrendo o caminho encontrado para achar a aresta "gargalo"
    {
      curr_flow = min(curr_flow, capacity[parent[curr]][curr]);
      curr = parent[curr];
    }
    flow += curr_flow;                 // fluxo que eu posso passar por esse caminho = custo da aresta "gargalo"
    cost += curr_flow * dist[destiny]; // quanto eu gasto para passar esse fluxo no caminho encontrado
    curr = destiny;
    while (curr != source) // apos achar a aresta gargalo, passamos o fluxo pelo caminho encontrado
    {
      capacity[parent[curr]][curr] -= curr_flow;
      capacity[curr][parent[curr]] += curr_flow;
      curr = parent[curr];
    }
  }
  return cost; // ao final temos a resposta :)
}
signed main()
{
  int n;
  cin >> n;
  int v[n][n];
  source = 0, destiny = (2 * n) + 1;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> v[i][j];
      add_edge(i + 1, j + n + 1, 1, v[i][j]);
    }
  }
  for (int i = 1; i <= n; i++)
    add_edge(source, i, 1, 0);
  for (int i = n + 1; i <= n + n; i++)
    add_edge(i, destiny, 1, 0);
  cout << min_cost_flow() << endl;
}
