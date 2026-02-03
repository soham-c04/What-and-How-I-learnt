#include <bits/stdc++.h>
//#define long long ll;
using namespace std;
long long int findDiff(long long int N1, long long int N2)
{
    stringstream s1,s2;
	s1<<N1;
	s2<<N2;
	string str1,str2;
	s1>>str1;
	s2>>str2;
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    int diff = n1 - n2;
    int carry = 0;
    for (int i = n2 - 1; i >= 0; i--) {
        int sub = ((str1[i + diff] - '0') - (str2[i] - '0')
                   - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }
    for (int i = n1 - n2 - 1; i >= 0; i--) {
        if (str1[i] == '0' && carry) {
            str.push_back('9');
            continue;
        }
        int sub = ((str1[i] - '0') - carry);
        if (i > 0 || sub > 0)
            str.push_back(sub + '0');
        carry = 0;
    }
    reverse(str.begin(), str.end());
    stringstream rev;
    rev<<str;
    long long int ans;
    rev>>ans;
    return ans;
}
int main() {
	long long int n1=pow(10,17),n2=99999999999999999;
	cout<<n1-n2;
	cout<<findDiff(n1,n2)-5;
	return 0;
}
