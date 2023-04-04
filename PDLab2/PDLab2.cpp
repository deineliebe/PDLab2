#include <iostream>

//Task 1
float** tableOfDifferences(int n, float x[])
{
    float** array = new float*[n];
    for (int i = 0; i < n; i++)
        array[i] = new float[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            array[i][j] = x[i] - x[j];
        }
        array[i][i] = - x[i];
        for (int j = i + 1; j < n; j++)
        {

            array[i][j] = x[i] - x[j];
        }
    }
    return array;
}

void multiplication(float (*x), float (*ls), int degree, int step, int n, float temp, int ex)
{
    if (step == ex) step++;
    if (step == n)
    {
        ls[n - degree - 1] += temp;
        temp = 1;
    }
    for (int j = step; j < n; j++)
    {
        multiplication(x, ls, degree + 1, step + 1, n, temp, ex);
        multiplication(x, ls, degree, step + 1, n, temp * x[j] * -1, ex);
        return;
    }
}

void task1(float (*x), float (*y), int n)
{
    float** differences = tableOfDifferences(n, x);
    float* ds = new float[n];
    float** ls = new float* [n];
    float* tempLs = new float[n];
    for (int i = 0; i < n; i++)
    {
        ls[i] = new float[n];
    }
    for (int i = 0; i < n; i++)
    {
        ds[i] = 1;
        for (int j = 0; j < i; j++)
        {
            ds[i] *= differences[i][j];
        }
        for (int j = i + 1; j < n; j++)
        {
            ds[i] *= differences[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            tempLs[k] = 0;
        }
        multiplication(x, tempLs, 0, 0, n, 1, i);
        for (int k = 0; k < n; k++)
        {
            ls[i][k] = tempLs[k];
        }
    }
    for (int k = 0; k < n; k++)
    {
        tempLs[k] = 0;
    }
    std::cout << "L" << n << " = ";
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tempLs[i] += ((y[j]) / ds[j]) * ls[j][i];
        }
        std::cout << tempLs[i] << "x^" << n - i - 1 << " + ";
    }
    for (int j = 0; j < n; j++)
    {
        tempLs[n - 1] += ((y[j]) / ds[j]) * ls[j][n - 1];
    }
    std::cout << tempLs[n - 1];
    std::cout << '\n';
}

//Task2
double langrage(float x1, float x2, float y1, float y2, float xt)
{
    float p0, p1;
    p0 = (x2 - xt) * y1;
    p1 = (x1 - xt) * y2;
    return (p0 - p1) / (x2 - x1);
}

float AitkenScheme(float xt, float(*x), float(*y), int n, double accuracy)
{
    double** scheme = new double* [n];
    for (int i = 0; i < n; i++)
    {
        scheme[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            scheme[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        scheme[i][0] = y[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            scheme[j][i + 1] = langrage(x[j - i - 1], x[j], scheme[j - 1][i], scheme[j][i], xt);
            if ((abs(scheme[j][i + 1] - scheme[j][i]) < accuracy) or (abs(scheme[j - 1][i] - scheme[j][i + 1]) < accuracy))
            {
                return scheme[j][i + 1];
            }
        }
    }
    return float('inf');
}

void task2(float xt, float(*x), float(*y), int n, double accuracy)
{
    float answer = AitkenScheme(xt, x, y, n, accuracy);
    if (answer != float('inf'))
    {
        std::cout << "Answer is " << answer << '\n';
    }
    else
    {
        std::cout << "Error\n";
    }
}

#include <iostream>

int main()
{
    std::cout << "This is the second lab of project design.\n\n";
    std::cout << "First task is to execute the Langrage polinom.\n";
    float x1[4] = { 0, 1, 2, 5 };
    float y1[4] = { 2, 3, 12, 147 };
    task1(x1, y1, 4);
    //Task two
    std::cout << "\nSecond task is to execute y=f(x) with the scheme of Aitken.\n";
    float xt = 1.020;
    float x2[8] = { 0.20, 0.80, 1.20, 1.70, 2.35, 3.00, 3.14, 3.61 };
    float y2[8] = { 10.2316, 10.9590, 11.4725, 12.1483, 13.0120, 14.0976, 16.2134, 19.0218 };
    task2(xt, x2, y2, 8, 0.001);
}
