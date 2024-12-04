#include <bits/stdc++.h>



using namespace std;


map<string, string> opposite = {
    {"north east", "north west"},
    {"north west", "north east"}
};
ofstream outFile("/home/cun/Documents/LatexLab/extra2/periodicTable/rows.tex", ios::app);

string pattern = R"(%ENAME
\node[draw, fill=COLOR!30, minimum width=3cm, minimum height=2.5cm, anchor=DIRECT] (cell) at (POSITION) {};
\node[draw, fill=COLOR!50, circle, inner sep=1mm, anchor=OPP_DIRECT] at ([xshift=MOVEcm, yshift=-0.2cm]cell.OPP_DIRECT) {\textbf{ORDINAL}};
\node[anchor=OPP_DIRECT] at ([yshift=-1cm]cell.OPP_DIRECT) {\small ATOMIC_W};
\node[anchor=DIRECT] at ([]cell.DIRECT) {\textbf{\Huge SYMBOL}};
\node[anchor=DIRECT] at ([yshift=-1.5cm]cell.DIRECT) {\textit{ENAME}};
\node[anchor=DIRECT] at ([yshift=-2cm]cell.DIRECT) {\textbf{\small RNAME}};)";

vector<string> getData(string line) {
    istringstream stream(line);
    string word;
    vector<string> res;
    while(stream >> word) res.push_back(word);
    return res;
}

void getDirectAndPositions(double& x, string& color, string& direct, string& move, stack<string>& status) {
    if(color != "cyan") {
        direct = "north west";
        move = to_string(-0.2);
        if(!status.empty() && status.top() != "cyan") {
            x += 3;
        }
    } else {
        direct = "north east";
        move = to_string(0.2);
        if(status.empty() || status.top() == "cyan") {
            x += 3;
        } else {
            x += 6;
        }
    }
    if(!status.empty()) status.pop();
    status.push(color);
}

void replaceAll(string &str, string from, string &to) {
    if (from.empty()) return;
    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }
}

void processOneLine(double& x, double& y, string line, stack<string>& status) {
    if(line.empty()) return;
    string res = pattern;
        vector<string> data = getData(line);
        string color = data[0];
        string ordinal = data[1];
        string atomic_w = data[2];
        string symbol = data[3];
        string eName = data[4];
        string rName = data[5];
        string direct = "";
        string opp_direct = "";
        string move = "";
        string pos = "";

        getDirectAndPositions(x, color, direct, move, status);
        opp_direct = opposite[direct];
        pos = to_string(x) + ',' + to_string(y);

        replaceAll(res, "OPP_DIRECT", opp_direct);
        replaceAll(res, "DIRECT", direct);
        replaceAll(res, "COLOR", color);
        replaceAll(res, "ORDINAL", ordinal);
        replaceAll(res, "ATOMIC_W", atomic_w);
        replaceAll(res, "SYMBOL", symbol);
        replaceAll(res, "ENAME", eName);
        replaceAll(res, "RNAME", rName);
        replaceAll(res, "POSITION", pos);
        replaceAll(res, "MOVE", move);
        outFile << res << endl;
        outFile << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.inp", "r", stdin);
    double x, y; cin >> x >> y;
    cin.ignore();

    string line;
    stack<string> status;
    int counter = 0;
    while(getline(cin, line)) {
        counter++;
        if(counter == 11) {
            while(!status.empty()) status.pop();
            counter = 0;
            x = -37.5;
            y -= 2.5;
            continue;
        }
        processOneLine(x, y, line, status);
    }
    return 0;
}
