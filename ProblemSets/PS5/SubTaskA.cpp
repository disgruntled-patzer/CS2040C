#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

// write your matric number here: A0164750E
// write your name here: Lau Yan Han
// write list of collaborators here: Pretty much everyone in the CS2040C telegram chat
// year 2018/19 Sem1 hash code: IEXVAR3BOJ4VIYLO (do NOT delete this line)

//#define VMAX 1000
typedef pair<int, int> ii;

class PS5{
	private:
		int V; // number of vertices in the graph (number of junctions in Singapore map)
		int Q; // number of queries
		vector<vector<ii>> AdjList; // the weighted graph (Singapore Map): First int is adjacent node, second int is weight (i.e. distance of the path)
		vector<vector<int>> distance; // A vector of all nodes; within each node stores the shortest distance from that node to all other nodes
		//int distance[VMAX][VMAX - 1]; //Original implementation of distance list in a simple array

	public:

		//Clear and reassign memory to the distance list for each test case
		void distance_assign(){
			/*for (int i = 0; i < VMAX; ++i){
				for (int j; j < VMAX - 1; ++j){
					distance[i][j] = -1;
				}
			}*/
			distance.assign(V, vector<int>()); //Assign the outer vector to contain V vectors
			for (int i = 0; i < V; ++i){ //Max no of nodes = VMAX
				for (int j = 0; j < V; ++j){ //Max no of nodes that source node can connect to = VMAX - 1
					distance[i].push_back(-1); //Use -1 as placeholder
				}
			}
		}
		
		//Breadth first search algorithm that calculates distance from source to all other nodes
		void BFS(int source){
			bool *visited = new bool[V]; //Variable length array to mark whether a node has been visited or not
			for (int i = 0; i < V; ++i){
				visited[i] = false;
			}

			queue<ii> search; //BFS queue. First int stores the node itself, second int stores its distance from source node

			//Initialize the source node data
			visited[source] = true; //Mark source as visited
			distance[source][source] = 0; //Distance from source to source is obviously zero...
			search.push(make_pair(source, 0)); //Then push source node into the BFS queue

			while (!search.empty()){
				
				auto curr = search.front(); //Next node to be processed
				int curr_node = get<0>(curr); //Break up the curr into its node and distance components to make code tracing easier
				int curr_distance = get<1>(curr);
				search.pop();

				//Traverse through the curr node's adjacent nodes to see which have not been visited
				for (auto it = AdjList[curr_node].begin(); it != AdjList[curr_node].end(); ++it){
					int temp_node = it->first;
					if (!visited[temp_node]){ //If node hasn't been visited
						int temp_distance = curr_distance + it->second; //Get this node's distance from the source node
						distance[source][temp_node] = temp_distance; //Store this distance value
						visited[temp_node] = true; //Mark as visited
						//printf("Node %d, distance %d, ", temp_node, temp_distance);
						search.push(make_pair(temp_node, temp_distance)); //Finally push this node and its distance into BFS queue
					}
				}
			}

			delete visited;
		}

		//For each node, take it as the source node and calculate shortest distance to every other node
		//This data is stored in the "distance" 2D vector
		void PreProcess() {

			for (int i = 0; i < V; ++i){
				//printf("BFS from node %d: ", i);
				BFS(i); //Perform BFS for every node
				//printf("\n");
			}
		}

		//Ask for the shortest from s to t, without exceeding k number of nodes (For SubtaskA, k is ignored)
		int Query(int s, int t, int k) {

			int ans = distance[s][t]; //Distance from source(s) to destination(t) was processed in the PreProcess BFS calls
			return ans;
		}

		//Main driver function to input data (modified from skeleton code)
		void inputdata(){
			int TC;
			scanf("%d", &TC);

			while (TC--) {
				int j, k, w;
				scanf("%d", &V);
				
				//Reset and reassign memory for AdjList and distance list
				AdjList.assign(V, vector<ii>());
				distance_assign();

				//Insert paths and their respective weights
				for (int i = 0; i < V; i++) {
					scanf("%d", &k); //k = Number of edges that this particular node i has
					while (k--) {
						scanf("%d %d", &j, &w); //j = adjacent node, w = weight
						AdjList[i].emplace_back(j, w); // store the adjacent node and weight info into the AdjList
					}
				}

				PreProcess(); //Call BFS from each node as the source

				//Handle queries
				int source, destination, required_k;
				scanf("%d", &Q);
				while (Q--) {
					scanf("%d %d %d", &source, &destination, &required_k);
					printf("%d\n", Query(source, destination, required_k));
				}

				if (TC)
					printf("\n");
			}
		}
};


int main() {

	PS5 SubTaskA;
	SubTaskA.inputdata();

	return 0;
}
