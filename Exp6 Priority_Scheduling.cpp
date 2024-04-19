#include <iostream>
using namespace std;

int main()
{
    int b[20], p[20], weight[20], tt[20], ptr[20], i, j, n;
    int total = 0, pos, temp, avg_weight, avg_tt;
    cout << "Total process: ";
    cin >> n;
    cout << n;
    cout << "\nBurst Time and priority:";
    for (i = 0; i < n; i++)
    {
        cout << "\nP[" << i + 1 << "]\n";
        cout << "Burst Time: ";
        cin >> b[i];
        cout << b[i] << endl;
        cout << "Priority: ";
        cin >> ptr[i];
        cout << ptr[i] << endl;
        p[i] = i + 1;
    }
    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (ptr[j] < ptr[pos])
                pos = j;
        }
        temp = ptr[i];
        ptr[i] = ptr[pos];
        ptr[pos] = temp;
        temp = b[i];
        b[i] = b[pos];
        b[pos] = temp;
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
    weight[0] = 0;
    for (i = 1; i < n; i++)
    {
        weight[i] = 0;
        for (j = 0; j < i; j++)
            weight[i] += b[j];
        total += weight[i];
    }
    avg_weight = total / n;
    total = 0;
    cout << "\nprocess\t Burst Time \tWaiting Time\tTurnaround Time";
    for (i = 0; i < n; i++)
    {
        tt[i] = b[i] + weight[i];
        total += tt[i];
        cout << "\nP[" << p[i] << "]\t\t " << b[i] << "\t\t " << weight[i] << "\t\t\t" << tt[i];
    }
    avg_tt = total / n;
    cout << "\n\nAvg Waiting Time=" << avg_weight;
    cout << "\nAvg Turnaround Time=" << avg_tt;
    return 0;
}