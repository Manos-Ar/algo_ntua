#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stdbool.h>
#include <vector>

using namespace std;

struct Node {
  Node(){};
  Node(int n);
  int name, inside, outside;
  bool parent_in;
  Node *parent;
  vector<Node*> children;
};
Node::Node(int n){
    name = n;
    if(n==1)  parent = NULL;
    inside=0;
    outside=0;
    parent_in=false;
  }
  
void tree (Node *node){
  if(node->children.empty())
    {
      node->parent_in=true;
    }
  bool var=false;
  for(int i=0; i<(int)node->children.size(); i++){
    tree(node->children[i]);
  }
  for(int i=0; i<(int)node->children.size(); i++){
    node->inside+=node->children[i]->inside;
    var|=node->children[i]->parent_in;
  }
  if(var) node->inside++;
  else node->parent_in=true;
  return;
}

vector<vector<int>> cal (vector<vector<int>> &dp, vector<int> &child0, vector<int> &child1, int K){
	
	int child_size = child0.size(), father_size = dp[0].size();
	vector<int> dp0_edges(child_size);
	vector<int> dp1_edges(child_size);
	for(int i=0; i<child_size; i++){
			dp0_edges[i]=max(child0[i],child1[i]+1); 
			dp1_edges[i]=max(child0[i],child1[i]);
		}
	vector<int> new_dp0(child_size+father_size-1,-2),new_dp1(child_size+father_size-1,-2);
	for(int i=0; i<father_size; i++){
		for(int j=0; j<child_size; j++){
			new_dp0[i+j] = max(new_dp0[i+j], dp[0][i]+dp0_edges[j]);
			new_dp1[i+j] = max(new_dp1[i+j], dp[1][i]+dp1_edges[j]); 
		}
	}
	if((int)new_dp0.size() > K+1) new_dp0.erase(new_dp0.begin()+K+1, new_dp0.end());
	if((int)new_dp1.size() > K+1) new_dp1.erase(new_dp1.begin()+K+1, new_dp1.end());
	dp[0].assign(new_dp0.begin(), new_dp0.end());
	dp[1].assign(new_dp1.begin(), new_dp1.end());
	return dp;
} 

vector<vector<int>> least_nodes(Node *node, int num){
	vector<vector<int>> dp;
	vector<int> in; 
	vector<int> out;
	in = {-2,(int) node->children.size()};
	out = {0, 0};
	dp.push_back(out);
	dp.push_back(in);
	
	
	vector<vector<vector<int>>> children;
	for(int i=0; i<(int)node->children.size(); i++){
		children.push_back(least_nodes(node->children[i], num));
	}
	for(int i=0; i<(int)node->children.size(); i++){
		dp = cal(dp, children[i][0], children[i][1], num);
	}
	
	return dp;
}



int main(){
  std::ios::sync_with_stdio(false);
  int N, K, name1, name2;

  cin >> N>> K;
  Node *nodes = new Node[N];
  for(int i=0; i<N; i++){
    nodes[i] = Node(i+1);
  }
  for(int i=0; i<N-1; i++){
    cin >>name1 >> name2;
    name1--;
    name2--;
    nodes[name1].children.push_back(&nodes[name2]);
    nodes[name2].parent = &nodes[name1];
  }
  if(K==N-1){
  	tree(&nodes[0]);
  	cout<<nodes[0].inside<<endl;
	}
	else{
		vector<vector<int>> dp;
		dp = least_nodes(&nodes[0], K);
		int i=0, result;
		
		while(1){
			result = max(dp[0][i], dp[1][i]);
			if(result >= K) break;
			i++;
		}
		cout<<i<<endl;
	}
}

