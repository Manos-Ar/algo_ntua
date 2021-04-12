#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

class build{
	public:
		build(){
			right=left=0;
			index_r=index_l=1;
		};
		int value;
		long long right,left;
		int index_r, index_l;
};

bool comp(const build &lhs, const build &rhs) { return lhs.right < rhs.right; }

stack <build> st;

build * right (int end, build *org){
	build *insert, *top;
	for(int i=0; i<end; i++){
		insert = &org[i];
		if(i==0){
			insert->right =(long long) insert->value;
			st.push(*insert);
		}
		else{
			top = &st.top();
			if(top->value > insert->value){
				insert->right =(long long) top->right + insert->value;
				st.push(*insert);
			}
			else if(top->value <= insert->value){
				insert->right = top->right;
				while(top->value <= insert->value && !st.empty()){
					insert->index_r += top->index_r;
					insert->right -=(long long) top->index_r*top->value;
					st.pop();
					if(!st.empty()) top = &st.top();
				}
				insert->right +=(long long) insert->value*insert->index_r;
				st.push(*insert);
			}
		}
	}
	return org;
}

build * left (int end, build *org){
	build *insert, *top;
	for(int i=end-1; i>-1; i--){
		insert = &org[i];
		if(i==end-1){
			insert->left =(long long) insert->value;
			st.push(*insert);
		}
		else{
			top = &st.top();
			if(top->value > insert->value){
				insert->left =(long long) top->left + insert->value;
				st.push(*insert);
			}
			else if(top->value <= insert->value){
				insert->left = top->left;
				while(top->value <= insert->value && !st.empty()){
					insert->index_l += top->index_l;
					insert->left -=(long long) top->index_l*top->value;
					st.pop();
					if(!st.empty()) top = &st.top();
				}
				insert->left +=(long long) insert->value*insert->index_l;
				st.push(*insert);
			}
		}
	}
	return org;
}



int main(){
	std::ios::sync_with_stdio(false);
	int N;
	cin >>N;
	build *H;
	H = new build[N];
	int tmp;
	for(int i=0; i<N; i++){
		cin>>tmp;
		H[i].value=tmp;
	}
	H = right(N,H);

	while(!st.empty()){
		st.pop();
	}
	H = left(N,H);

	for(int i=0; i<N; i++)
		H[i].right += H[i].left - H[i].value;
	build *point;
	point=min_element(H,H+N,comp);
	cout<<point->right<<endl;
}
