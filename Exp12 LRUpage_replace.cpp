#include <iostream>
using namespace std;
int main()
{
    int nopages, nofaults, page[20], i, count = 0;
    cout << "\n\t Enter no of pages for which you want to calculate page faults:>";
    cin >> nopages;
    cout << "\n\t Enter the Reference String:";
    for (i = 0; i < nopages; i++)
    {
        cout << "\t";
        cin >> page[i];
    }
    cout << "\n\t Enter the Numer of frames:";
    cin >> nofaults;
    int frame[nofaults], fcount[nofaults];
    for (i = 0; i < nofaults; i++)
    {
        frame[i] = -1;
        fcount[i] = 0;
    }
    i = 0;
    while (i < nopages)
    {
        int j = 0, flag = 0;
        while (j < nofaults)
        {
            if (page[i] == frame[j])
            {
                flag = 1;
                fcount[j] = i + 1;
            }
            j++;
        }
        j = 0;
        cout << "\n\t***\n";
        cout << "\t" << page[i] << "-->";
        if (flag == 0)
        {
            int min = 0, k = 0;
            while (k < nofaults - 1)
            {
                if (fcount[min] > fcount[k +
                                         1])

                    min = k + 1;
                k++;
            }
            frame[min] = page[i];
            fcount[min] = i + 1;
            count++;
            while (j < nofaults)
            {
                cout << "\t|" << frame[j] << "|";
                j++;
            }
        }
        i++;
    }
    cout << "\n\t***\n";
    cout << "\n\t Page Fault:" << count << "\n";
    return 0;
}