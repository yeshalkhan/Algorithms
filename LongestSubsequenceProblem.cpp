

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int LCDynamicProg(string a, string b,string& result)
{
    a.insert(a.begin(), ' ');    //adding a dummy character at 1st index
    b.insert(b.begin(), ' ');    
    int len1 = a.length(), len2 = b.length(), maxValue;
    vector<vector<int>> values(len1, vector<int>(len2));
    vector<vector<char>> arrows(len1, vector<char>(len2)); //2d vector of arrows is for showing direction of values. H for horizontal, d for down and D for Diagonal
    for (int i = 0; i < len1; i++)     //fill the first row 
    {
        values[i][0] = 0;
        arrows[i][0] = 'H';
    }
    for (int j = 0; j < len2; j++)     //fill the first column
    {
        values[0][j] = 0;
        arrows[0][j] = 'd';
    }
    for (int i = 1; i < len1; i++)
    {
        for (int j = 1; j < len2; j++)
        {
            if (a[i] == b[j])
            {
                values[i][j] = values[i - 1][j - 1] + 1;
                arrows[i][j] = 'D';
            }
            else
            {
                maxValue = max(values[i - 1][j], values[i][j - 1]);
                values[i][j] = maxValue;
                if (values[i - 1][j] == maxValue)
                    arrows[i][j] = 'd';
                else
                    arrows[i][j] = 'H';
            }
        }
    }
    int i = len1 - 1, j = len2 - 1;
    while (i >= 0 and j >= 0)
    {
        if (arrows[i][j] == 'D')
        {
            result.push_back(b[j]);
            i = i - 1;
            j = j - 1;
        }
        else if (arrows[i][j] == 'H')
            j = j - 1;
        else
            i = i - 1;
    }
    reverse(result.begin(), result.end());
    return values[len1 - 1][len2 - 1];
}

int LCHelper(int i, int j, string a, string b, vector<vector<bool>>& table)
{
    if (a[i] == '\0' || b[j] == '\0')
        return 0;
    if (a[i] == b[j])
    {
        table[i][j] = true;
        return 1 + LCHelper(i + 1, j + 1, a, b, table);
    }
    else
        return max(LCHelper(i + 1, j, a, b, table), LCHelper(i, j + 1, a, b, table));
}

int LCRecursion(string& result, string a, string b)
{
    vector<vector<bool>> table(a.length(), vector<bool>(b.length(), false));
    int len1 = a.length(), len2 = b.length();
    int lenLC = LCHelper(0, 0, a, b, table);;
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            if (table[i][j]==true)
                result.push_back(b[j]);
        }
    }
    return lenLC;
}

int main()
{
    string a, b, result;
    int length;
    cout << "Enter 1st string : ";
    cin >> a;
    cout << "Enter 2nd string : ";
    cin >> b;
    cout << "Using recusrion : " << endl;
    length = LCRecursion(result, a, b);
    cout << "Length of longest common subsequence : " << length << endl;
    cout << "String : " << result << endl;
    result = "";
    cout << "Using dynamic programming : " << endl;
    length = LCDynamicProg(a, b, result);
    cout << "Length of longest common subsequence : " << length << endl;
    cout << "String : " << result << endl;
}

