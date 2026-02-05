#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

int main(){
	ordered_set os;
	os.insert(1);
	os.insert(2);
	os.insert(7);
	os.insert(3);
	cout<<os.order_of_key(3)<<" "<<os.order_of_key(4)<<" number of elements strictly less than key\n"; 
	cout<<*os.find_by_order(3)<<" element\n";
	return 0;
}
