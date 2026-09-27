#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    // 01
    // Analyze the code:
    // Loop runs n times, the time complexity is O(n)
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    cout << sum << endl;
    cout << endl;
    // 02
    // i doubles at each iteration:
    // 1, 2, 4, 8, ...
    // Therefore, the number of iterations grows logarithmically.
    // Time Complexity: O(log n)
    for (int j = 1; j < n; j *= 2)
    {
        cout << j << endl;
    }
    cout <<endl;
    // 03
    // Analyze the code:
    // Outer loop runs n times, inner loop runs log(n) times, the time complexity is O(n log n)
    for (int k = 0; k < n; k++)
    {
        for (int l = 1; l < n; l *= 2)
        {
            cout << k << " " << l << endl;
        }
    }
    cout <<endl;
    // 04
    // Analyze the code:
    // the time complexity is O(n^2)
    for(int m = 0; m < n; m ++ ){
        for(int p = 0; p < m ; p++){
            cout << p << endl;
        }   
    }
    cout <<endl;
    // 05
    // Analyze the code:
    // loop runs sqrt(n) times, the time complexity is O(sqrt(n))
    for (int q = 0; q * q < n; q++) {
        cout << q << endl;
    }
    return 0;
}