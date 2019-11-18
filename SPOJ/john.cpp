#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
#include <unordered_map>
#include <assert.h>

using namespace std;

const int INF = (int)1e9;

vector<pair<int, int>> getCoordinate(vector<int> height, vector<int> distance, int n)
{
    vector<pair<int, int>> coordinate;

    int OFF_DISTANCE = 0;
    int DIFF_DISTANCE = 0;

    for (int i = 0; i < n; i++)
    {
        DIFF_DISTANCE = (i > 0) ? distance[i - 1] : 0; //val perbedaan distance sebelumnya akan digunakan jika n>0 karena titik pertama sudah pasti x = 1.

        pair<int, int> p;
        p.first = (i == 0) ? 1 : i + DIFF_DISTANCE + OFF_DISTANCE; // X=1 jika index pertama, sisanya akan ditambah dari perbedaan distance + koordinat maksimal.
        p.second = height[i];

        coordinate.push_back(p);

        if (i > 0)
        {
            OFF_DISTANCE += distance[i - 1] - 1; //Maksimal koordinat akan bertambah seiring bertambahnya distance.
        }
    }

    return coordinate;
}

vector<int> getDropLeft(const vector<pair<int, int>> coordinate)
{
    int n = coordinate.size();
    vector<int> dropLeft(n, 1);
    vector<int> prev;

    for (int i = 0; i < coordinate.size(); i++)
    {
        while (prev.size() > 0 && coordinate[prev.back()].first >= coordinate[i].first - coordinate[i].second)
        {
            // cout << "first cond" << endl;
            prev.pop_back();
            // for (int i = 0; i < prev.size(); i++)
            // {
            //     cout << "prev after pop back " << prev[i] << endl;
            // }
        }

        if (prev.size() > 0)
        {
            // cout << "2nd cond prev back " << prev.back() << endl;
            dropLeft[i] = prev.back() + 2;
        }

        prev.push_back(i);

        // for (int i = 0; i < prev.size(); i++)
        // {
        //     cout << "prev after push " << prev[i] << endl;
        // }

        // cout << "------------------------ iteration " << i + 1 << " Done" << endl;
    }
    //	  cout << "drop ";
    //    for(int i=0;i<dropLeft.size();i++) cout << dropLeft[i];

    //    cout << endl;

    return dropLeft;
}

vector<int> getDropRight(const vector<pair<int, int>> coordinate)
{
    int n = coordinate.size();
    vector<int> dropLeft(n, n);
    vector<int> prev;

    for (int i = coordinate.size() - 1; i >= 0; i--)
    {
        while (prev.size() > 0 && coordinate[prev.back()].first <= coordinate[i].first + coordinate[i].second)
        {
            //	cout << "first cond" << endl;
            prev.pop_back();
            //			for(int i=0;i<prev.size();i++){
            //        		cout << "prev after pop back " << prev[i] << endl;
            //			}
        }

        if (prev.size() > 0)
        {
            //			cout << "2nd cond prev back " << prev.back() << endl;
            dropLeft[i] = prev.back();
        }

        prev.push_back(i);

        //		for(int i=0;i<prev.size();i++){
        //			cout << "prev after push " << prev[i] << endl;
        //		}

        //		cout << "------------------------ iteration " << i+1 << " Done" << endl;
    }
    //	  cout << "drop ";
    //    for(int i=0;i<dropLeft.size();i++) cout << dropLeft[i];

    //    cout << endl;

    return dropLeft;
}

vector<pair<int, int>> path;
unordered_map<int, bool> sudah;
bool masuk = false;

void backtrack(int dp[][2], int i)
{
    if (dp[i][0] != 0 && dp[i][0] != i)
    {
        sudah[dp[i][0]] = true;
        printf("%d L\n", dp[i][0]);
        masuk = true;
        path.push_back({i, dp[i][0]});
        if (dp[i][0] != i)
            backtrack(dp, dp[i][0]);
    }
    else if (dp[i][1] != 0 && dp[i][1] != i)
    {
        sudah[dp[i][1]] = true;
        printf("%d P\n", dp[i][1]);
        masuk = true;
        path.push_back({dp[i][1], i});
        if (dp[i][1] != i)
            backtrack(dp, dp[i][1]);
    }
    else
    {
        //		printf("DONE %d %d\n", dp[i][0], dp[i][1]);
    }
}

pair<int, int> bla[1005];
vector<pair<int, pair<int, int>>> mystep;
int getAnswer(vector<int> dropLeft, vector<int> dropRight)
{
    int n = dropLeft.size();

    stack<pair<int, string>> answer;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    vector<pair<int, int>> v;
    v.push_back(make_pair(0, 0)); //Inisiasi.

    int dpstep[n + 1][2];
    memset(dpstep, 0, sizeof dpstep);

    for (int i = 0; i < n; i++)
    {
        int x = i + 1;
        int low = dropLeft[i];
        int high = dropRight[i];
        int cur = dp[i];

        while (v.size() > 1)
        {
            pair<int, int> p = v[v.size() - 2];

            if (p.first >= low - 1)
            {
                v.pop_back();
            }
            else
            {
                break;
            }
        }

        // dp[x] = min(v.back().second + 1, dp[x]);
        if (v.back().second + 1 < dp[x])
        {
            // Left is zero
            dpstep[x][0] = v.back().first + 1;
            dp[x] = v.back().second + 1;
            bla[x - 1] = make_pair(0, v.back().first + 1);
            mystep.push_back(make_pair(v.back().first + 1, make_pair(x, 0)));
            // cout << v.back().first + 1 << " -> L " << x << endl;
        }

        while (!v.empty() && v.back().second >= dp[x])
        {
            v.pop_back();
        }

        v.push_back(make_pair(x, dp[x]));
        //dp[high] = min(dp[high], cur + 1);
        if (cur + 1 < dp[high])
        {
            // Right is one
            dp[high] = cur + 1;
            dpstep[high][1] = i + 1;
            bla[i] = make_pair(1, high);
            mystep.push_back(make_pair(high, make_pair(i + 1, 1)));
            // cout << high << " -> P " << i + 1 << endl;
        }
    }

    int now = 1;
    // for (int i = 0; i <= n; i++)
    // {
    //     cout << dp[n] << " ";
    // }
    // cout << endl;
    cout << dp[n] << endl;
    // for (int i = n; i >= 1; i--)
    // {
    //     bool isAvaiable = true;
    //     for (int j = 0; j < path.size(); j++)
    //     {
    //         if (i <= path[j].second && i >= path[j].first)
    //         {
    //             isAvaiable = false;
    //             break;
    //         }
    //     }
    //     if (isAvaiable)
    //     {
    //         masuk = false;
    //         backtrack(dpstep, i);
    //         if (masuk == false && sudah[i] == false)
    //             printf("%d P\n", i);
    //     }
    // }
    int count = 0;
    int tepe = mystep[0].first;
    // pair<int, int> tehe = mystep[0].second;
    // cout << "Asasf" << endl;
    // for (int i = 1; i < n; i++)
    // {
    //     if (mystep[i].first <= tepe)
    //         continue;
    //     if (mystep[i].second.first != tehe.first)
    //     {
    //         if (tehe.second == 1)
    //             cout << tehe.second << " " << tehe.first << endl;
    //         else
    //             cout << tehe.second << " " << i << endl;
    //     }
    //     tepe = mystep[i].first;
    //     tehe = mystep[i].second;
    // }
    // // if (mystep[n - 1].first > tepe)
    // // {
    // if (tehe.second == 1)
    //     cout << tehe.second << " " << tehe.first << endl;
    // else
    //     cout << tehe.second << " " << n << endl;

    // cout << "bla" << endl;
    tepe = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (bla[i].first == 0 && bla[i].first == bla[i + 1].first && bla[i].second >= bla[i + 1].second)
        {
            continue;
        }
        if (tepe >= bla[i].second)
            continue;
        tepe = bla[i].second;
        count++;
        cout << i + 1 << " " << (bla[i].first ? "P" : "L") << endl;
    }
    if (tepe < bla[n - 1].second)
    {
        count++;
        cout << n << " " << (bla[n - 1].first ? "P" : "L") << endl;
    }
    assert(count <= dp[n]);
    // }
    //	backtrack(dpstep,n);

    //	for(int i = 0; i <= n; i++) {
    //		printf("%d : %d\n", i, dp[i]);
    //	}
    return 0;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        path.clear();
        sudah.clear();

        vector<int> height(n);
        vector<int> distance(n - 1);

        for (int i = 0; i < n; i++)
            scanf("%d", &height[i]);
        for (int i = 0; i < n - 1; i++)
            scanf("%d", &distance[i]);

        //Bikin koordinat sesuai dengan tinggi, jarak, n.
        vector<pair<int, int>> coordinate = getCoordinate(height, distance, n);

        // Debug vector
        //		for(int i=0;i<coordinate.size();i++)
        //			cout << "first " << coordinate[i].first << " second " << coordinate[i].second << endl;
        //
        //		int maxN = coordinate[coordinate.size()-1].first;

        vector<int> dropLeft = getDropLeft(coordinate);
        vector<int> dropRight = getDropRight(coordinate);
        // cout << "dropLeft = {";
        // for (int i = 0; i < dropLeft.size(); i++)
        //     cout << dropLeft[i];
        // cout << "}" << endl;

        // cout << "dropRight = {";
        // for (int i = 0; i < dropRight.size(); i++)
        //     cout << dropRight[i];
        // cout << "}";

        int ans = getAnswer(dropLeft, dropRight);

        //		printf("%d\n", ans);
        //		while(!answer.empty()){
        //			cout << answer.top().first << " " << answer.top().second << endl;
        //			answer.pop();
        //		}
        //
        //Debug dropLeft + dropRight.
    }
}