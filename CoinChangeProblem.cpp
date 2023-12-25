
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool isGreedyPossible(vector<float>& denValues, int numOfDen)
{
    //greedy algorithm can be applied if denomiantions are multiples of each other
    float dividend = denValues[0];
    for (auto elem : denValues)
    {
        if (fmod(dividend, elem) != 0)
            return false;
    }
}

void printDenominations(vector<float>& result, vector<string>& denStrings, int numOfDen)
{
    cout << "Denominations used are : " << endl;
    for (int i = 0; i < numOfDen; i++)
    {
        if (result[i] != 0)
        {
            cout << result[i] << " " << denStrings[i];
            if (result[i] > 1)
                cout << "s";
            cout << endl;
        }
    }
}

int coinChangeGreedy(vector<float>& denValues, vector<string>& denStrings, int numOfDen, float totalSum)
{
    if (!isGreedyPossible(denValues, numOfDen))
        return -1;
    int quotient, total = 0;
    vector<float> result(numOfDen, 0);   //for printing denominations
    for (int i = 0; i < numOfDen; i++)
    {
        if (totalSum >= denValues[i])
        {
            quotient = totalSum / denValues[i];
            totalSum = totalSum - quotient * denValues[i];
            total += quotient;
            result[i] = quotient;
        }
    }
    if (totalSum != 0)  //if sum can't be constructed
        return -1;
    printDenominations(result, denStrings, numOfDen);
    return total;
} 

int coinChangeDP(vector<float>& denValues, vector<string>& denStrings, int numOfDen, float totalSum)
{
    vector<float> revDenValues = denValues;
    reverse(revDenValues.begin(), revDenValues.end());  //reverse the denomination values
    vector<float> result(numOfDen, 0);   //for printing denominations
    vector<vector<float>> table(numOfDen, vector<float>(totalSum + 1));       //a 2d array where no of rows = number of denominations and no of columns = total sum + 1
    int total;
    for (int i = 0; i < numOfDen; i++)         //fill the first column with zeros
        table[i][0] = 0;
    for (int j = 0; j <= totalSum; j++)        //fill the first row
    {
        if (j < revDenValues[0])
            table[0][j] = 0;
        else
            table[0][j] = 1 + (j - revDenValues[0]);
    }
    for (int i = 1; i < numOfDen; i++)
    {
        for (int j = 1; j <= totalSum; j++)
        {
            if (j < revDenValues[i])
                table[i][j] = table[i - 1][j];
            else
                table[i][j] = min(table[i - 1][j], 1 + table[i][j - revDenValues[i]]);
        }

    }
    int i = numOfDen - 1, j = totalSum;
    total = table[i][j];
    while (i >= 0 && j > 0)
    {
        if (i != 0 && table[i][j] == table[i - 1][j])
                i = i - 1;
        else
        {
            j = j - revDenValues[i];
            result[i] += 1;
            totalSum -= revDenValues[i];
        }
    }
    if (totalSum < 0)  //if sum can't be constructed
        return -1;
    reverse(result.begin(), result.end());
    printDenominations(result, denStrings, numOfDen);
    return total;
}

int main()
{
    ifstream file;
    file.open("Coins.txt");
    if (file)
    {
        string currency, currSymbol, denString;
        int numOfDen; 
        float denValue, totalSum, ans;
        file >> currency;
        file >> currSymbol;
        file >> numOfDen;
        vector<float> denValues;
        vector<string> denStrings;
        for (int i = 0; i < numOfDen; i++)
        {
            file >> denString;
            file >> denValue;
            denValues.push_back(denValue);
            denStrings.push_back(denString);
        }
        cout << "Enter the value for which coin-change is required (in cents) : ";
        cin >> totalSum;
        ans = coinChangeGreedy(denValues, denStrings, numOfDen, totalSum);
        if (ans != -1)
            cout << "Total denominations used : " << ans << endl;
        else
        {
            cout << "This problem can't be solved with greedy algorithm. Here's the solution with dynamic programming : " << endl;
            ans = coinChangeDP(denValues, denStrings, numOfDen, totalSum);
            if (ans == -1)
                cout << "Sum can't be constructed for this problem" << endl;
            else
                cout << "Total denominations used : " << ans << endl;
        }

        
    }

}

