#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
bitset<1000> vis;

// Adj Matrix
//   for each line: |V| entries, 0 or the weight
// Adj List
//   for each line: num neighbors, list of neighbors + weight pairs
// Edge List
//   for each line: a-b of edge(a,b) and weight
int V, E, total_neighbors, id, weight, a, b;
int AdjMat[100][100];
vector<vii> AdjList;
priority_queue< pair<int, ii> > EdgeList;   // one way to store Edge List

void dfsAL(int p, int u) {
  vis[u] = 1;
  cout << u << " ";
  for(auto v: AdjList[u]) {
    if (!vis[v.first]) {
      dfsAL(u,v.first);
    }
  }
}

void dfsAM(int p, int u) {
  vis[u] = 1;
  cout << u << " ";
  for(int i = 0; i < V; i++) {
    if (!vis[i]) {
      dfsAM(u,i);
    }
  }
}

void bfsAL(int src) {
  vis.reset();
  vis[src] = 1;
  queue<int> qu;
  qu.push(src);
  while (!qu.empty()) {
    int cur = qu.front();
    cout << cur << " ";
    qu.pop();
    for (auto v: AdjList[cur]) {
      if (!vis[v.first]) {
        vis[v.first] = 1;
        qu.push(v.first);
      }
    }
  }
}

void bfsAM(int src) {
   vis.reset();
  vis[src] = 1;
  queue<int> qu;
  qu.push(src);
  while (!qu.empty()) {
    int cur = qu.front();
    vis[cur] = 1;
    cout << cur << " ";
    qu.pop();
    for (int i = 0; i < V; i++) {
      if (!vis[i]) {
        vis[i] = 1;        
        qu.push(i);
      }
    }
  }
}

int main() {

  freopen("in_07.txt", "r", stdin);

  scanf("%d", &V);                         // we must know this size first!

  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      scanf("%d", &AdjMat[i][j]);

  printf("Neighbors of vertex 0:\n");
  for (int j = 0; j < V; j++)                                     // O(|V|)
    if (AdjMat[0][j])
      printf("Edge 0-%d (weight = %d)\n", j, AdjMat[0][j]);

  scanf("%d", &V);
  AdjList.assign(V, vii()); // quick way to initialize AdjList with V entries of vii
  for (int i = 0; i < V; i++) {
    scanf("%d", &total_neighbors);
    for (int j = 0; j < total_neighbors; j++) {
      scanf("%d %d", &id, &weight);
      AdjList[i].push_back(ii(id - 1, weight));    // some index adjustment
    }
  }

  printf("Neighbors of vertex 0:\n");
  for (vii::iterator j = AdjList[0].begin(); j != AdjList[0].end(); j++)
    // AdjList[0] contains the required information
    // O(k), where k is the number of neighbors
    printf("Edge 0-%d (weight = %d)\n", j->first, j->second);

  scanf("%d", &E);
  for (int i = 0; i < E; i++) {
    scanf("%d %d %d", &a, &b, &weight);
    EdgeList.push(make_pair(-weight, ii(a, b))); // trick to reverse sort order
  }

  // edges sorted by weight (smallest->largest)
  for (int i = 0; i < E; i++) {
    pair<int, ii> edge = EdgeList.top(); EdgeList.pop();
    // negate the weight again
    printf("weight: %d (%d-%d)\n", -edge.first, edge.second.first, edge.second.second);
  }

  vis.reset();
  dfsAL(-1, 0);
  cout << endl << endl;

  vis.reset();
  dfsAM(-1, 0);
  cout << endl << endl;

  bfsAL(0);
  cout << endl << endl;

  bfsAM(0);
  cout << endl << endl;
  return 0;
}
