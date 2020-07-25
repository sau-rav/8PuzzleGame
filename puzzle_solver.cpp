#include<bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define TIME cerr << "\nTime elapsed: " << setprecision(5) <<1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define PI 3.14159265358979323846
#define pb push_back
#define F first
#define S second #define lb lower_bound
#define ub upper_bound

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef map<int, int> mi;
typedef map<ll, ll> ml;
#define fr(i, n) for (int i = 0; i < n; i++)
#define frn(i, k, n) for (int i = k; i < n; i++)

vector<int> drow4{1, -1,  0,  0};
vector<int> dcol4{0,  0, -1,  1};
vector<string> stringMove{"U", "D", "R", "L"};

vi cost;
string start, endst;

vector<string> toVector(string str) {
	vector<string> v;
	int n = str.length();
	int k = sqrt(n);
	for(int i = 0; i < n; i += k) {
		v.push_back(str.substr(i, k));
	}
	return v;
}

pair<int, int> getStartLocation(vector<string> v) {
	int rows = v.size(), cols = v[0].length();
	fr(i, rows) {
		fr(j, cols) {
			if(v[i][j] == 'G') {
				return {i, j};
			}
		}
	}
	return {-1, -1};
}

string getString(vector<string> v) {
	string res = "";
	for(auto i : v) {
		res += i;
	}
	return res;
}

int changes(string s, string t) {
	auto p1 = getStartLocation(toVector(s));
	auto p2 = getStartLocation(toVector(t));
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

struct compare {
	bool operator() (pair<pair<string, string>, int> p1, pair<pair<string, string>, int> p2) {
		if(p1.second != p2.second) return p1.second > p2.second;
		else if((p1.first.second.length() + 1) / 3 != (p2.first.second.length() + 1) / 3){
			return (p1.first.second.length() + 1) / 3 > (p2.first.second.length() + 1) / 3;
		}
		return changes(p1.first.first, endst) > changes(p1.first.first, endst);
	}
};

vector<string> getPath(int n) {
	map<string, int> visited;
	priority_queue<pair<pair<string, string>, int>, vector<pair<pair<string, string>, int>>, compare> pq;
	pq.push({{start, ""}, 0});
	while(!pq.empty()) {
		string str = pq.top().first.first, strPath = pq.top().first.second;
		int strCost = pq.top().second;
		pq.pop();
		if(visited.count(str) > 0) continue;
		else visited[str]++;
		if(str == endst) {
			int steps = (strPath.length() + 1) / 3; 
			return {to_string(steps), to_string(strCost), strPath.substr(1)};
		}
		vector<string> strVec = toVector(str);
		int rows = n, cols = n;
		auto startLoc = getStartLocation(strVec);
		int strow = startLoc.first, stcol = startLoc.second;
		fr(i, 4) {
			int r = strow + drow4[i], c = stcol + dcol4[i];
			if(r >= 0 && r < rows && c >= 0 && c < cols) {
				vector<string> changeVec = strVec;
				swap(changeVec[r][c], changeVec[strow][stcol]);
				string changeStr = getString(changeVec);
				if(visited.count(changeStr) == 0) {
					int changeCost = strCost + cost[strVec[r][c] - '1'];
					string changePath = strPath + " " + strVec[r][c] + stringMove[i]; 
					pq.push({{changeStr, changePath}, changeCost});
				}
			}
		}
	}
	return {};
}

void solve(){
	int n = 8, m = 3;
	cin >> start >> endst;
	cost.resize(n);
	fr(i, n) cin >> cost[i];
	if(start == endst) {
		cout << "0 0" << endl;
		cout << endl;
		return;
	}
	vector<string> res = getPath(m);
	if(res.size() == 0) cout << "NOT POSSIBLE" << endl;
	else {
		cout << res[0] << " " << res[1] << endl;
		cout << res[2] << endl;
	}
}

int main(){
    FAST
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
}
