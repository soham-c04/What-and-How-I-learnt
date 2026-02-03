#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define f(n) for(int i=0;i<(n);i++)

// Time Complexity - O(NlogN)
// Space Complexity - O(N) [for creating tempL and tempR arrays]

const int INF = 2e9;    // Set INF > max(a_i) . This is just for ease of implementation

ll Inversions(int a[], int l, int r){
	if(l>=r) return 0;
	int mid = (l+r)/2;
	ll ans = Inversions(a, l, mid);
	ans += Inversions(a, mid+1, r);

	int Lsize = mid-l+1, Rsize = r-mid;
	int tempL[Lsize+1], tempR[Rsize+1];

	for(int i=0;i<Lsize;i++) tempL[i] = a[i+l];
	for(int i=0;i<Rsize;i++) tempR[i] = a[i+mid+1];
	tempL[Lsize] = tempR[Rsize] = INF;     // INF appended to last for ease of implementation

	for(int i=l, L=0, R=0; i<=r; i++){
		if(tempL[L] < tempR[R]){
			a[i] = tempL[L];
			L++;
		}
		else{
			a[i] = tempR[R];
			ans += Lsize-L;
			R++;
		}
	}
	
	return ans;
}

void Inversions(pair<pair<int,int>,int> output[], int l, int r){
	if(l>=r) return;
	int mid = (l+r)/2;
	Inversions(output, l, mid);
	Inversions(output, mid+1, r);

	int Lsize = mid-l+1, Rsize = r-mid;
	pair<pair<int,int>,int> tempL[Lsize+1], tempR[Rsize+1];

	for(int i=0;i<Lsize;i++) tempL[i] = output[i+l];
	for(int i=0;i<Rsize;i++) tempR[i] = output[i+mid+1];
	tempL[Lsize] = tempR[Rsize] = {{-1,0},INF};     // -INF appended to last for ease of implementation

	for(int i=l, L=0, R=0; i<=r; i++){
		if(tempL[L].second < tempR[R].second){
			output[i] = tempL[L];
			L++;
		}
		else{
			output[i] = tempR[R];
			output[i].first.second += Lsize-L;
			R++;
		}

		// For counting j > i, such that a[j] < a[i] :-

		/*
		// Change last value of tempL, tempR to INF, instead of INF.

		if(tempL[L].second < tempR[R].second){
			output[i] = tempR[R];
			R++;
		}
		else{
			output[i] = tempL[L];
			output[i].first.second += Rsize-R;
			L++;
		}
		*/
	}
}

int main(){
	int T=1,n;
//	cin>>T;
	while(T--){
		int n;
		cin>>n;
		int a[n];
		ai(a,n);

		pair<pair<int,int>,int> output[n];  // output[i] = {{original_index, disorder_of_a[i]}, value_a[i]}
		f(n) output[i] = {{i,0},a[i]};

		Inversions(output, 0, n-1);
		sort(output, output+n);     // Sorted because output[n] will be in descending order of a[i]. sorting it arranges them back in original order.

		cout<<Inversions(a, 0, n-1)<<"\n";
		f(n) cout<<output[i].first.second<<" ";
		cout<<"\n";
	}

	return 0;
}
