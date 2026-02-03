#include <bits/stdc++.h>
#include <conio.h>  		// Only for getch()
using namespace std;

#define F first
#define S second

map<int, vector<pair<int,char>>> NFA, DFA;
int mx = 0;

void generateNFA(string &s, int start){
    int n = s.size();
    pair<int,int> prev = {-2,-2};
    int end = mx+1;
    mx++;
    for(int i=0;i<n;i++){
        if(s[i] == '+'){
        	NFA[start].push_back({prev.F,0});
        	NFA[prev.S].push_back({end,0});
            prev = {-2,-2};
        }
        else if(s[i] == '*'){
        	cout<<"Ambiguous * in expression.\n";
        	exit(1);
        }
        else if(s[i] == '('){
        	int cnt=1;
    		string rec = "";
    		int start1 = prev.S;
			for(++i;i<n;i++){
				rec.push_back(s[i]);
				if(s[i]==')'){
					cnt--;
					if(!cnt){
						rec.pop_back();
						if(prev.S == -2){
							prev = {mx+1,mx+1};
							start1 = prev.S;
							mx++;
						}
						prev.S = mx+1;
						generateNFA(rec, start1);
						break;
					}
				}
				else if(s[i]=='(') cnt++;
			}
			if(cnt>0){
				cout<<"Extra Opening Parenthesis.\n";
				exit(2);
			}
			
			if((i<n-1) && (s[i+1]=='*')){
            	NFA[start1].push_back({prev.S,0});
            	NFA[prev.S].push_back({start1,0});
	            i++;
	        }
        }
        else if(s[i] == ')'){
        	cout<<"Extra Closing Parenthesis.\n";
        	exit(3);
        }
        else if((i<n-1) && (s[i+1]=='*')){
        	if(prev.S == -2){
				prev = {mx+1,mx+1};
				mx++;
			}
            NFA[prev.S].push_back({prev.S,s[i]});
            i++;
        }
        else{
            if(prev.S == -2){
                prev = {mx+1,mx+2};
                NFA[prev.F].push_back({prev.S,s[i]});
                mx += 2;
            }
            else{
                NFA[prev.S].push_back({mx+1,s[i]});
                prev.S = mx+1;
                mx++;
            }
        }
    }
    if(prev.S == -2){
    	cout<<"Missing alphabet from expression.\n";
    	exit(4);
	}
	NFA[start].push_back({prev.F,0});
    NFA[prev.S].push_back({end,0});
}

void generateDFA(map<int, vector<pair<int,char>>> &NFA){
	typedef long long ll;
	int n = mx+1;
	
	vector<char> alphabets;
	map<char,ll> transition_table[n];
	for(auto &vec:NFA){
        for(auto [v,w]:vec.S){
        	transition_table[vec.F][w]|=1LL<<v;
        	if(w) alphabets.push_back(w);
		}
	}
	sort(alphabets.begin(),alphabets.end()); alphabets.resize(unique(alphabets.begin(),alphabets.end())-alphabets.begin());
	
	ll eps_closure[n]={0};
	
	function<void(int)> dfs = [&](int u) -> void{
		eps_closure[u] = 1LL<<u;
        for(ll V = transition_table[u][0]; V; V&=V-1){
        	int v = __builtin_ctzll(V);
			if(!eps_closure[v]) dfs(v);
			eps_closure[u]|=eps_closure[v];
		}
    };
    
	for(int i=0;i<n;i++) dfs(i);

	mx = 0;
	map<ll, int> vis;
	ll q0 = eps_closure[0];
	stack<ll> stk;
	stk.push(q0);
	vis[q0] = mx+1;
	mx++;
	int final = 0;
	while(!stk.empty()){
		ll S = stk.top();
		stk.pop();
		
		for(char w:alphabets){
			ll T = 0;
			for(ll U=S; U; U&=U-1){
	        	int u = __builtin_ctzll(U);
	        	for(ll TT=transition_table[u][w]; TT; TT&=TT-1){
		        	int t = __builtin_ctzll(TT);
		        	T|=eps_closure[t];
				}
			}
			
			if(T){
				if(!vis[T]){
					if(T&2){
						vis[T] = final-1;
						final--;
					}
					else{
						vis[T] = mx+1;
						mx++;
					}
					stk.push(T);
				}
				DFA[vis[S]-1].push_back({vis[T]-1,w});
			}
		}
	}
}

int main(){
	cout<<"Read the README.txt first.\n\n";
	
    string s;
    cout<<"Enter the regular expression: ";
    cin >> s;

	// NFA
	
    generateNFA(s, 0);

	cout<<"\nNFA:\n";

    for(auto &vec:NFA){
        string u = "q";
		if(vec.F == 0) u += "_i";
        else if(vec.F == 1) u += "_f";
        else u += to_string(vec.F-1);

        for(auto [V,w]:vec.S){
            string v = "q";
			if(V == 0) v += "_i";
            else if(V == 1) v += "_f";
            else v += to_string(V-1);
            
            cout<<u<<" "<<v<<" ";
            if(w) cout<<w<<"\n";
            else cout<<"E\n";
        }
    }
    
    // DFA

    generateDFA(NFA);

	cout<<"\nDFA:\n";

    for(auto vec:DFA){
        string u = "q";
		if(vec.F == 0) u = "S";
        else if(vec.F < 0) u = "F" + to_string(-vec.F-1);
        else u += to_string(vec.F);

        for(auto [V,w]:vec.S){
            string v = "q";
			if(V == 0) v = "S";
			else if(V < 0) v = "F" + to_string(-V-1);
            else v += to_string(V);

            cout<<u<<" "<<v<<" "<<w<<"\n";
        }
    }
	
	cout<<"\nPress Any Key to close.\n";
	getch();

	// Output and Simulation
	
	freopen("output.txt", "w", stdout);

	vector<string> blanks = {"\xE2\x80\x8B", "\xE2\x80\x8C", "\xE2\x80\x8D", "\xEF\xBB\xBF", "\xE2\xA0\x80", "\xE3\x85\xA4",
							 "\xE1\xA0\x8E", "\xE2\x81\xA0", "\xE2\x81\xA3", "(blank)", "(Blank)", "(BLANK)", "(blanK)", "(BLank)"};
	int blank = 0;
	
	cout<<"NFA:\n";

    for(auto vec:NFA){
        string u = "q";
		if(vec.F == 0) u += "_i";
        else if(vec.F == 1) u += "_f";
        else u += to_string(vec.F);

        for(auto [V,w]:vec.S){
            string v = "q";
			if(V == 0) v += "_i";
            else if(V == 1) v += "_f";
            else v += to_string(V);

            if((u!=v) || (blank == blanks.size())){
            	cout<<u<<" "<<v<<" ";
	            if(w) cout<<w;
	            else cout<<"\xCE\xB5";    // Epsilon
            	cout<<"\n";
	        }
			else{
				cout<<u<<" "<<blanks[blank]<<" ";
	            if(w) cout<<w;
	            else cout<<"\xCE\xB5";    // Epsilon
            	cout<<"\n";
				cout<<blanks[blank]<<" "<<v<<" ";
	            if(w) cout<<w;
	            else cout<<"\xCE\xB5";    // Epsilon
            	cout<<"\n";
				blank++;
			}
        }
    }
    
    blank = 0;

	cout<<"\nDFA:\n";

	for(auto vec:DFA){
        string u = "q";
		if(vec.F == 0) u = "S";
        else if(vec.F < 0) u = "F" + to_string(-vec.F-1);
        else u += to_string(vec.F);

        for(auto [V,w]:vec.S){
            string v = "q";
			if(V == 0) v = "S";
			else if(V < 0) v = "F" + to_string(-V-1);
            else v += to_string(V);

			if((u!=v) || (blank == blanks.size()))
            	cout<<u<<" "<<v<<" "<<w<<"\n";
			else{
				cout<<u<<" "<<blanks[blank]<<" "<<w<<"\n";
				cout<<blanks[blank]<<" "<<v<<" "<<w<<"\n";
				blank++;
			}
        }
    }
    
    return 0;
}
