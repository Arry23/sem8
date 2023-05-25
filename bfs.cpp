#include<bits/stdc++.h> 
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

// to find Serial Breadth first search from the current index
void breadth_first_search(vector<vector<bool>> graph, int index)
{
	vector<bool>visited(graph.size(), false); // to track the nodes that are visited
	queue<int> q; // to put nodes to be visited in bfs manner
	q.push(index); // pushing first node into the queue
	visited[index] = true;
	while( !q.empty() ) {
		auto ele = q.front();
		q.pop();
		cout<< ele << " " ;
		for(int i=0; i< graph.size(); i++) {
			if(graph[ele][i] == true && !visited[i]){ // if there is edge between
			// and it is not visited then pushing it in queue and marking visited
				q.push(i);
				visited[i] = true;
			}
		}
	}
	cout<< "\n";

}
// to find Parallel Breadth first search from the current index
void parallel_breadth_first_search(vector<vector<bool>> &graph, int index)
{
	vector<bool>visited(graph.size(), false); // to track the nodes that are visited
	queue<int> q;  // to put nodes to be visited in bfs manner
	q.push(index); // pushing first node into the queue
	visited[index] = true;
	int n = graph.size();
	while( !q.empty() ) {
		auto ele = q.front();
		q.pop();
		// The omp parallel for directive effectively combines the omp parallel 
		// and omp for directives. This directive lets you define a parallel
		// region containing a single for directive in one step.
		#pragma omp parallel for
		for(int i=0; i< n; i++) {
			if(graph[ele][i] == true && !visited[i]){
				q.push(i);
				visited[i] = true;
			}
		}
	}

}

int main(){
	cout<< "Enter the no. of nodes in graph ";
	int n;
	cin>> n;
	cout<<n<<endl;
	vector<vector<bool>> graph(n, vector<bool>(n, false));
	// taking graph input 
	// taking input for the lower half of main diagonal 
	for(int i=0; i<n; i++){
		for(int j = 0; j< i; j++){
			graph[i][j] = 1 - (rand() % 2);	
		}
	}
	// input for the upper half of main diagonal will be same for undirected graph
	for(int i=0; i<n; i++){
		for(int j =i+1; j< n; j++){
			graph[i][j] = graph[j][i];
		}
	}
	
	int index;
	cout<< "Enter the start index for the traversal: "<<endl;;
	cin>> index;
	
	// Returns a time point representing the current point in time.
	auto start_time = high_resolution_clock::now();
	
	breadth_first_search(graph, index);
	auto end_time = high_resolution_clock::now();
	// convering duration to nanoseconds 
	auto duration_time = duration_cast<microseconds>(end_time - start_time);	
	cout<< "Time taken with sequential BFS is " << duration_time.count() << " microseconds \n";

	start_time = high_resolution_clock::now();
	
	parallel_breadth_first_search(graph, index);

	end_time = high_resolution_clock::now();
	duration_time = duration_cast<microseconds>(end_time - start_time);	
	cout<< "Time taken with prarallel BFS is " << duration_time.count() << " microseconds \n";
	
}
