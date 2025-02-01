#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

/******************************************
Task 1.
******************************************/
void compute_stats(int array[], int size, double *average,
                   double *stddev)
{
    // double sum = 0;
    // for(int i = 0; i < size; i++) {
    //     sum += array[i];
    // }
    // *average = sum / size;

    // double sum_squared_diff = 0;
    // for(int i = 0; i < size; i++) {
    //     double diff = array[i] - *average;
    //     sum_squared_diff += diff * diff;
    // }

    // *stddev = sqrt(sum_squared_diff / (size - 1));

    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += array[i];
    }
    *average = sum / size;

    double variance = 0.0;
    for (int i = 0; i < size; ++i)
    {
        variance += (array[i] - *average) * (array[i] - *average);
    }
    variance /= (size - 1);
    *stddev = sqrt(variance);
}

/******************************************
Task 2.
******************************************/
void n_unique(const string &input, string &result, int nCopy)
{
    int char_count[26] = {0};
    result = "";

    for (int i = 0; i < input.length(); i++)
    {
        char c = input[i];

        if (!isalpha(c))
        {
            result += c;
            continue;
        }

        int char_index = c - 'a';

        if (char_count[char_index] < nCopy)
        {
            result += c;
            char_count[char_index]++;
        }
    }
}

int main()
{
    /******************************************
    Task 1.
    ******************************************/
    int sample[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // int sample[] = {727, 1086, 1091, 1361, 1490, 1956};
    double avg, stdd;

    compute_stats(sample, 8, &avg, &stdd);

    // Using C-Style printf for convenience
    printf("Average = %.4f, Std. Deviation = %.4f\n", avg, stdd);

    /******************************************
    Task 2.
    ******************************************/
    string task2Str = "abcdef!!abc, cba defa bcaba.";
    string result;

    n_unique(task2Str, result, 1);
    cout << "NCopy = 1, Result = " << result << endl;

    n_unique(task2Str, result, 2);
    cout << "NCopy = 2, Result = " << result << endl;

    n_unique(task2Str, result, 3);
    cout << "NCopy = 3, Result = " << result << endl;

    n_unique(task2Str, result, 4);
    cout << "NCopy = 4, Result = " << result << endl;

    n_unique("!!!*&%^ #$##$$!!", result, 2);
    cout << "NCopy = 2, Result = " << result << endl;

    return 0;
    return 0;
}
