#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int k = 1001;
    int fake_k = 0;
    vector<int> a(n);
    vector<int> c(k, 0);
    vector<int> temp(k);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        c[a[i]]++;
        if (a[i] > fake_k)
            fake_k = a[i];
    }
    ++fake_k;
    for (int i = 1; i < fake_k; i++)
    {
        sum += c[i];
        temp[i] = sum;
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int l;
        cin >> l;
        int r;
        cin >> r;
        if (l > fake_k or r < 0)
            cout << 0 << "\n";
        else if (l > 0 and l <= fake_k and r > fake_k)
            cout << temp[fake_k - 1] - temp[l - 1] << "\n";
        else if (l > 0 and l <= fake_k and r <= fake_k)
            cout << temp[r] - temp[l - 1] << "\n";
        else if (l <= 0 and r >= 0 and r <= fake_k)
            cout << temp[r] - temp[0] << "\n";
        else if (l <= 0 and r > fake_k)
            cout << temp[fake_k - 1] - temp[0] << "\n";
    }
    return 1;
}
