#include <bits/stdc++.h>
using namespace std;

vector<string> code, deadcode;
vector<int> leader;
map<string, int> labels;
vector<vector<int>> blocks, cfg;
vector<bool> is_dead;

void createBlocks() {
    leader.clear();
    leader.push_back(0);

    for(int i=0;i<code.size();i++){
        string line = code[i];

        int pos = line.find("goto");
        if(pos!=string::npos){
            string label=line.substr(pos + 4);
            label.erase(remove_if(label.begin(), label.end(), ::isspace), label.end());
            if(!label.empty() && label.back() == ':') label.pop_back();

            if(labels.count(label)) leader.push_back(labels[label]);

            if(i+1<code.size()) leader.push_back(i + 1);
        }

        if(line.back() == ':') leader.push_back(i);
    }

    sort(leader.begin(), leader.end());
    leader.erase(unique(leader.begin(), leader.end()), leader.end());

    blocks.clear();
    for(int i=0;i<leader.size();i++) {
        int start=leader[i];
        int end=(i+1<leader.size()) ? leader[i+1]-1:code.size()-1;

        vector<int> block;
        for(int j=start;j<=end;j++) block.push_back(j);
        blocks.push_back(block);
    }
}

void createCFG() {
    cfg.assign(blocks.size(), {});
    map<int, int> lineToBlock;
    for(int i=0;i<blocks.size();i++) for(int l:blocks[i]) lineToBlock[l]=i;

    for(int i=0;i<blocks.size();i++){
        string lastInstr=code[blocks[i].back()];

        int pos=lastInstr.find("goto");
        if (pos!=string::npos) {
            string label=lastInstr.substr(pos + 4);
            label.erase(remove_if(label.begin(), label.end(), ::isspace), label.end());
            if(label.back()==':') label.pop_back();

            if(labels.count(label)) cfg[i].push_back(lineToBlock[labels[label]]);

            if(lastInstr.find("if") != string::npos && i + 1 < blocks.size()) cfg[i].push_back(i + 1);
        }
		else if(i+1<blocks.size()) cfg[i].push_back(i+1);
    }
}

void printCFG(){
    cout<<"\n--- Basic Blocks ---\n";
    for(int i=0;i<blocks.size();i++){
        cout<<"Block "<<i<<":\n";
        for(int l:blocks[i]) cout<<"   "<<code[l]<<"\n";
    }

    cout<<"\n--- CFG ---\n";
    for(int i=0;i<cfg.size();i++){
        cout<<"Block "<<i<<" -> ";
        for(int to:cfg[i]) cout<<to<<" ";
        cout<<"\n";
    }
}

bool isNumber(const string &s) {
    if (s.empty()) return false;
    char *end = nullptr;
    strtod(s.c_str(), &end);
    return (*end == '\0');
}

string evaluateExpression(string a, string op, string b) {
    if (!isNumber(a) || !isNumber(b)) return a + " " + op + " " + b;

    double x = stod(a), y = stod(b), res;
    if (op == "+") res = x + y;
    else if (op == "-") res = x - y;
    else if (op == "*") res = x * y;
    else if (op == "/") {
        if (y == 0) return a + " / " + b;
        res = x / y;
    }
	else return a + " " + op + " " + b;

    stringstream ss;
    if (fabs(res - (int)res) < 1e-9) ss << (int)res;
    else ss << res;
    return ss.str();
}

void constantPropagationAndFolding() {
    cout << "\n---- Constant Propagation & Folding ----\n";

    for(int bi=0;bi<blocks.size();bi++){
        map<string, string> constVal;
        vector<string> newBlock;

        for(int l:blocks[bi]){
            string line=code[l];

            if(line.back() == ':' || line.find("goto") != string::npos || line.find("if") != string::npos){
                newBlock.push_back(line);
                continue;
            }

            stringstream ss(line);
            string lhs, eq, rhs1, op, rhs2;
            ss >> lhs >> eq >> rhs1 >> op >> rhs2;

            if(eq != "="){
                newBlock.push_back(line);
                continue;
            }

            if(constVal.count(rhs1)) rhs1=constVal[rhs1];
            if(constVal.count(rhs2)) rhs2=constVal[rhs2];

            string newLine=line;

            if(rhs2.empty()){
                newLine=lhs+" = "+rhs1;
                if(isNumber(rhs1)) constVal[lhs] = rhs1;
                else constVal.erase(lhs);
            }
			else{
                string folded=evaluateExpression(rhs1, op, rhs2);
                newLine=lhs+" = "+folded;
                if(isNumber(folded)) constVal[lhs] = folded;
                else constVal.erase(lhs);
            }

            newBlock.push_back(newLine);
        }

        for(int i=0;i<blocks[bi].size();i++) code[blocks[bi][i]] = newBlock[i];
    }
}


void deadCodeElimination(){
	int n = blocks.size();
	is_dead.resize(n, true);
	stack<int> dfs;
	dfs.push(0);
	is_dead[0] = false;
	while(dfs.size()){
		int u=dfs.top();
		dfs.pop();
		for(int v:cfg[u]){
			if(is_dead[v]){
				is_dead[v] = false;
				dfs.push(v);
			}
		}
	}

	cout<<"\n---- Dead Code ----\n";
	vector<string> optimized;
	for(int i=0;i<n;i++){
		if(is_dead[i]){
			for(int l:blocks[i]) cout<<code[l]<<"\n";
		}
		else{
			for(int l:blocks[i]) optimized.push_back(code[l]);
		}
	}
	swap(code,optimized);
}

int main(){
	freopen("3ac.txt","r",stdin);
	string line;
    int line_no = 0;

    while (getline(cin, line)) {
        if (!line.empty()) {
            code.push_back(line);
            if (line.back()==':') {
                string label = line.substr(0, line.size() - 1);
                labels[label] = line_no;
            }
            line_no++;
        }
    }

	createBlocks();
	createCFG();
	printCFG();
	constantPropagationAndFolding();
	deadCodeElimination();
	
	cout<<"\n====== Optimized 3-address code =======\n\n";
	for(string &s:code) cout<<s<<"\n";
	cout<<"\n";
	
	return 0;
}
