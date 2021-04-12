#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stdbool.h>
#include <math.h>
#include <vector>
using namespace std;

unsigned long long int V,E;
struct Edge{
		Edge(){
			num = 0;
			set = false;
		};
		void set_values(unsigned long long int s,unsigned long long int d,unsigned long long int w){
			this->src = s;
			this->dest = d;
			this->weight = w;
		} 
		unsigned long long int src, dest, weight, num;
		bool set;
};

struct Subset{
	Subset(){};
	unsigned long long int parent, rank;
};
struct List{
	List(){
		set_name = false;
		num_children = 0;
	}
	unsigned long long int name;
	unsigned long long int num_children;
	bool set_name;
	vector<List*> next;
	vector<Edge*> edge;
};

unsigned long long int Find(Subset *ver,unsigned long long int i){
	unsigned long long int j = i;
	while(ver[i].parent!=i)
		i = ver[i].parent;
	ver[j].parent = i;

	return ver[i].parent;
}	

void Union(Subset *ver, unsigned long long int parent1,unsigned long long int parent2){
	if(ver[parent1].rank > ver[parent2].rank)
		ver[parent2].parent = parent1;
	else if(ver[parent2].rank > ver[parent1].rank)
		ver[parent1].parent = parent2;
	else {
		ver[parent2].parent = parent1;
		ver[parent1].rank++;
	}
}

void MSP (Edge *edges, unsigned long long int V, unsigned long long int E, Edge *result){
	Edge *edge;
	Subset *subset = new Subset[V];
	unsigned long long int n=0;
	unsigned long long int x,y;
	for(unsigned long long int i=0; i<V; i++){
		subset[i].parent = i;
		subset[i].rank = 0;
	}
	for(unsigned long long int m=0; m<E; m++){
		
		if(n==V-1) break;
		edge = &edges[m];
		x = Find(subset, edge->src);
		y = Find(subset, edge->dest);
		if(x!=y){
			Union(subset, x, y);
			result[n] = *edge;
			n++; 
		}
	}
	return;
}

void make_lists(List *list, Edge *result){
	Edge *edge;
	for(unsigned long long int i=0; i<V-1; i++){
			edge = &result[i];
			if(list[edge->dest].set_name == false){
				list[edge->dest].set_name = true;
				list[edge->dest].name =edge->dest;
			}
			if(list[edge->src].set_name == false){
				list[edge->src].set_name = true;
				list[edge->src].name =edge->src;
			}	
			list[edge->src].next.push_back(&list[edge->dest]);
			list[edge->src].edge.push_back(edge);
			list[edge->dest].next.push_back(&list[edge->src]);
			list[edge->dest].edge.push_back(edge);
		}
}

void DFS(List *list, unsigned long long int parent, unsigned long long int name){
	List *current_node = &list[name];
	if(current_node->next.size()==1 && parent!=name){
		current_node->edge[0]->num = V-1;
		current_node->edge[0]->set = true;
		return;
	}
	List *next_node;
	Edge *next_edge;
	for(unsigned long long int i=0; i<current_node->next.size(); i++){
		next_node = current_node->next[i];
		if(next_node->name != parent)
			DFS(list, name, next_node->name); 
	}
	for(unsigned long long int i=0; i<current_node->next.size(); i++){
		next_node = current_node->next[i];
		next_edge = current_node->edge[i];
		if(next_node->name != parent){
			current_node->num_children += next_node->num_children+1;
			if(next_edge->set == false){
				next_edge->num = (next_node->num_children+1)*(V-1-next_node->num_children);
				next_edge->set = true;
			}
		}
	}
}
void binary(vector<unsigned long long int> &bit, Edge *edges){
	unsigned long long int j;
	for(unsigned long long int i=0; i<V-1; i++){
		j = edges[i].weight;
		bit[j] += edges[i].num;
		while(bit[j]>1){
			if(j < bit.size()-2){
				bit[j+1] += bit[j]/2;
				bit[j] = bit[j]%2;
				j++;
			}
			else{
				bit.push_back(0);
				bit[j+1] += bit[j]/2;
				bit[j] = bit[j]%2;
				j++;
			}
		}		
	}

}

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	unsigned long long int s, d, w, root;
	Edge *edges, *start;
	Edge *msp;
	bool flag=false;
	
	cin >>V>>E;
	
	edges = new Edge[E];	//graph edges
	msp = new Edge[V-1];	//msp edges
	List *list = new List[V];	//list of neighbors for each vertex in msp
	vector<unsigned long long int> bit(E,0); //binary result
		
	for(unsigned long long int i=0; i<E; i++){
		cin >>s>>d>>w;
		edges[w].set_values(s-1,d-1,w);
	}
	MSP(edges, V, E, msp); //kruskal
	delete[] edges;

	make_lists(list, msp); // make lists

	start = &msp[(V-1)/2];
	root = start->src; //find root for dfs 
	DFS(list, root, root); //dfs
	
	binary(bit, msp); //binary representation
	
	for (vector<unsigned long long int>::iterator i = bit.end(); i-- != bit.begin(); ) {
	 if(*i == 1 ) flag = true;
	 if(flag == true) cout<<*i; //output
	}
	cout<<endl;
}
