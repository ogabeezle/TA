#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    int x, y;
    while (a--)
    {
        cin >> x >> y;
    }
    int i = 0;
    bool done = 1;
    while (i < b)
    {
        int xx = b - i;
//        cout << "\\begin{landscape}\n"<<
//                "\t\\begin{table}[]\n"<<
//                    "\t\t\\begin{tabular}{|c|lllll|c|}\n"<<
//                    "\t\t\\hline\n"<<
//                    "\t\tNo & \\multicolumn{5} {c|} {Data Masukan} & Hasil Keluaran \\\\ \\hline";
        for (int j = 0; j < 24 && i < b; j++)
        {
        	cout<<"\n\t\t";
            for (int k = 0; k < 6; k++)
            {
                cin >> x >> y;
                i++;
                cout << x << " " << y ;
				if(k!=5) cout<< " & ";
				else cout<<"\\\\";
            }
        }
//        cout << " \\hline\n"<<        "\t\t\\end{tabular}\n"<<
//                    "\t\\end{table}\n"<<
//                "\\end {landscape}\n ";
    }
}

