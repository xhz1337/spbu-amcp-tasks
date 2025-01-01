#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (i % 2 == 0 and a[i] >= a[i + 1])
        {
            swap(a[i], a[i + 1]);
        }
        else if (i % 2 != 0 and a[i] <= a[i + 1])
        {
            swap(a[i], a[i + 1]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    system("pause");
    return 1;
}
// 1 2 3 4 5 6 7 8 9 10
// 2 1 4 3 6 5 8 7 10 9