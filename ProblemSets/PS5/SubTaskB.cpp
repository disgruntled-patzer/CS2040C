#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <utility>
using namespace std;

// write your matric number here: A0164750E
// write your name here: Lau Yan Han
// write list of collaborators here: Pretty much everyone in the CS2040C telegram chat
// year 2018/19 Sem1 hash code: IEXVAR3BOJ4VIYLO (do NOT delete this line)

#define max_s 10 // 0 <= s <= 9
typedef pair<int, int> ii;

class PS5{
	private:
		int V; // number of vertices in the graph (number of junctions in Singapore map)
		int Q; // number of queries
		vector<vector<ii>> AdjList; // the weighted graph (Singapore Map): First int is adjacent node, second int is weight (i.e. distance of the path)
		vector<vector<int>> distance; // A vector of all nodes; within each node stores the shortest distance from that node to all other nodes

	public:

		//Clear and reassign memory to the distance list for each test case
		void distance_assign(){
			distance.assign(max_s, vector<int>()); //Assign the outer vector to contain max_s vectors (no. of sources <= 9)
			for (int i = 0; i < max_s; ++i){
				for (int j = 0; j < V; ++j){ //Max no of nodes that source node can connect to = VMAX - 1
					distance[i].push_back(-1); //Use -1 as placeholder
				}
			}
		}
		
		//Dijkstra's algorithm that calculates shortest distance from source to all other nodes
		void findpaths(int source){
			bool *visited = new bool[V]; //Variable length array to mark whether node has been visited or not
			for (int i = 0; i < V; ++i){
				visited[i] = false;
			}

			/*Dijkstra's PQ. First int stores the distance from source node, second int stores the node itself
			Note: Distance is stored first to exploit sorting properties of Set.
			greater<ii> stores the lowest weight node at the top of the queue (i.e. MinHeap instead of MaxHeap*/
			priority_queue<ii, vector<ii>, greater<ii>> priority;

			//Insert the source node
			distance[source][source] = 0;
			priority.push(make_pair(0, source));

			while (!priority.empty()){

				auto curr = priority.top(); //Extract the next node that should be processed (the node with smallest weight)
				int curr_node = get<1>(curr);
				int curr_distance = get<0>(curr);
				priority.pop();
				
				if (visited[curr_node] == true){
					continue; //Part of "lazy deletion" method: If node was processed earlier, then no need to reprocess it
				}
				visited[curr_node] = true;

				//Scan through all the adjacent nodes of the current node
				for (auto it = AdjList[curr_node].begin(); it != AdjList[curr_node].end(); ++it){
					int temp_node = it->first; //Node: For AdjList, first int is NODE while second int is WEIGHT
					int temp_weight = it->second; //Which is opposite that of the "priority" set!
					
					/*Relax operations are done here. Conditions for relax are:
					1. Current distance to temp_node is infinity (-1), OR
					2. The new calculated distance is shorter than the current distance to temp node*/
					if (distance[source][temp_node] == -1 || distance[source][temp_node] > curr_distance + temp_weight){
						distance[source][temp_node] = curr_distance + temp_weight; //Update the new distance
						
						/*Then "update" the distance inside the priority queue. But note this is "lazy update"
						which means a new updated node is inserted instead of the original node updated!
						The old nodes will only be deleted later on when they reach the top of the queue
						and are revealed to be already visited*/
						auto new_node = make_pair(distance[source][temp_node], temp_node);
						priority.push(new_node);
					}
				}
			}

			delete visited;
		}

		//For each node, take it as the source node and calculate shortest distance to every other node
		//This data is stored in the "distance" 2D vector
		void PreProcess(int V) {

			for (int i = 0; i < max_s && i < V; ++i){ //i is equal or less than either max_s (9) or no of nodes (V)
				findpaths(i); //Perform Dijkstra for every node
			}
		}

		//Ask for the shortest from s to t, without exceeding k number of nodes (For SubtaskB, k is ignored)
		int Query(int s, int t, int k) {

			int ans = distance[s][t]; //Distance from source(s) to destination(t) was processed in Preprocess function
			return ans;
		}

		//Main driver function to input data (modified from skeleton code)
		void inputdata(){
			int TC;
			scanf("%d", &TC);

			while (TC--) {
				int j, k, w;
				scanf("%d", &V);
				
				AdjList.assign(V, vector<ii>()); //Reset and reassign memory for AdjList and distance list
				distance_assign();

				//Insert paths and their respective weights
				for (int i = 0; i < V; i++) {
					scanf("%d", &k); //k = Number of edges that this particular node i has
					while (k--) {
						scanf("%d %d", &j, &w); //j = adjacent node, w = weight
						AdjList[i].emplace_back(j, w); // store the adjacent node and weight info into the AdjList
					}
				}

				PreProcess(V); //Call BFS from each node as the source

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

	PS5 SubTaskB;
	SubTaskB.inputdata();

	return 0;
}
