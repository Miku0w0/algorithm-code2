#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isInsertionSort(const vector<int> &orig, const vector<int> &mid)
{
    int n = orig.size();
    int i = 1;
    while (i < n && mid[i - 1] <= mid[i])
        i++;
    // i = 已经有序的前缀长度
    for (int j = i; j < n; j++)
    {
        if (mid[j] != orig[j])
            return false;
    }
    return true;
}

void nextInsertionSort(vector<int> &seq)
{
    int n = seq.size();
    int i = 1;
    while (i < n && seq[i - 1] <= seq[i])
        i++;
    if (i < n)
    {
        int key = seq[i];
        int j = i - 1;
        while (j >= 0 && seq[j] > key)
        {
            seq[j + 1] = seq[j];
            j--;
        }
        seq[j + 1] = key;
    }
}

void nextHeapSort(vector<int> &seq)
{
    int n = seq.size();
    int heapSize = n;
    // 找到已经排序的后缀
    while (heapSize > 1 && seq[heapSize - 1] >= seq[heapSize - 2])
        heapSize--;
    // 交换堆顶和最后一个元素
    swap(seq[0], seq[heapSize - 1]);
    heapSize--;
    // 堆化
    int i = 0;
    while (true)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < heapSize && seq[left] > seq[largest])
            largest = left;
        if (right < heapSize && seq[right] > seq[largest])
            largest = right;
        if (largest != i)
        {
            swap(seq[i], seq[largest]);
            i = largest;
        }
        else
            break;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> orig(n), mid(n);
    for (int i = 0; i < n; i++)
        cin >> orig[i];
    for (int i = 0; i < n; i++)
        cin >> mid[i];

    if (isInsertionSort(orig, mid))
    {
        cout << "Insertion Sort\n";
        nextInsertionSort(mid);
    }
    else
    {
        cout << "Heap Sort\n";
        nextHeapSort(mid);
    }

    for (int i = 0; i < n; i++)
    {
        if (i)
            cout << " ";
        cout << mid[i];
    }
    cout << "\n";
    return 0;
}
