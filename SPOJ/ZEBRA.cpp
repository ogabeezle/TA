#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.0);

int findMaxGuests(vector<double> &arrl, vector<double> &exit, bool arr[])
{
	// Sort arrival and exit arrays
	int n = arrl.size();
	sort(arrl.begin(), arrl.end());
	sort(exit.begin(), exit.end());
	//	cout<<n<<endl;
	// guests_in indicates number of guests at a time
	int guests_in = 0, maxi = 0;
	for (int i = 0; i < n; i++)
	{
		cout << arrl[i] << " " << exit[i] << endl;
	}
	//	cout<<"asdfasdgasdgasgsadgsad"<<endl;
	int i = 0, j = 0;

	for (int k = -20000; k <= 20000; k++)
	{
		if (arr[k + 20000])
			continue;
		while (i < n && arrl[i] <= k)
		{
			//			cout<<"in "<< arrl[i]<<endl;
			i++;
			guests_in++;
		}
		while (j < n && exit[j] < k)
		{
			//			cout<<"out "<< exit[j]<<endl;
			j++;
			guests_in--;
		}
		maxi = max(guests_in, maxi);
	}
	return maxi;
}

long long int fact[100];
void init()
{
	fact[0] = 1;
	for (int i = 1; i < 21; i++)
	{
		fact[i] = fact[i - 1] * i;
		// cout << fact[i] << endl;
	}
}

double cSIN(double radian, int aprox)
{
	float result = 0.0;

	for (int x = 1; x < aprox; x++)
	{
		double firstPart = (x + 1) % 2 == 0 ? 1 : -1;
		double secondPart = pow(radian, ((2 * x) - 1));
		double thirdPart = fact[(2 * x) - 1];
		cout << firstPart << " " << secondPart << " " << thirdPart << endl;
		result = result + firstPart * (secondPart / thirdPart);
		// cout << result << endl;
	}

	return result;
}

double cCOS(double x)
{
	double t = -x * x / 2;
	double sum = 1 + t;
	for (int i = 2; i < 20; ++i)
	{
		// cout << sum << endl;
		t *= -x * x / (2 * i * (2 * i - 1));
		sum += t;
	}
	return sum;
}

double roundEps(double xt)
{
	if (xt < 0)
	{
		xt *= -1;
		if (xt - floor(xt) < 1e-9)
			xt = -floor(xt);
	}
	else
	{
		if (xt - floor(xt) < 1e-9)
			xt = floor(xt);
	}

	return xt;
}
double cTAN(double x)
{
	return cSIN(x, 10) / cCOS(x);
}

int main()
{
	init();
	cout << cCOS(45.0 * pi / 180) << endl;
	cout << cSIN(45.0 * pi / 180, 8) << endl;
	cout << 20.0 - 20 * cTAN(45 * pi / 180) << endl;
	int tc;
	cin >> tc;
	bool arr[40005];
	bool done[10001];
	while (tc--)
	{
		memset(arr, 0, sizeof arr);
		map<double, vector<pair<double, double>>> group;
		memset(done, 0, sizeof done);
		int n;
		double v, w, x, t, a;
		cin >> n >> w >> v;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> t >> a;
			arr[(int)x + 20000] = 1;
			if (!done[(int)t])
			{
				vector<pair<double, double>> temp;
				group[t] = temp;
				done[(int)t] = 1;
			}
			group[t].push_back(make_pair(x, a));
		}

		int maxi = 0;
		for (auto it = group.begin(); it != group.end(); it++)
		{
			int ti = it->first;
			if (w - (ti * v) > 1e-9)
				continue;
			double vh = sqrt(1 - ((double)w / (ti * v) * (double)w / (ti * v))) * v;
			double vhr = -vh;
			vector<pair<double, double>> temp = it->second;
			vector<double> start, startr;
			vector<double> end, endr;
			for (int i = 0; i < temp.size(); i++)
			{
				int xi = temp[i].first;
				int ai = temp[i].second;
				double vih = w * cTAN((double)ai * pi / 60 / 180);
				cout << vih << endl;
				double xt;
				if (vih - vh < 0.0)
				{
					xt = (xi + vih - vh * ti);
					start.push_back(xt);
					end.push_back(xi);
				}
				else
				{
					xt = (xi + vih - vh * ti);
					end.push_back(xt);
					start.push_back(xi);
				}
				if (vih - vhr < 0.0)
				{
					xt = (xi + vih - vhr * ti);
					startr.push_back(xt);
					endr.push_back(xi);
				}
				else
				{
					xt = (xi + vih - vhr * ti);
					endr.push_back(xt);
					startr.push_back(xi);
				}
				cout << xt << endl;
				// maxi = max(maxi, findMaxGuests(startr, endr));
				// cout << findMaxGuests(start, end) - 1 << endl;
				// cout << temp[i].first << " " << temp[i].second << endl;
			}
			maxi = max(maxi, findMaxGuests(start, end, arr));
			maxi = max(maxi, findMaxGuests(startr, endr, arr));
		}
		cout << maxi << endl;
	}
}
