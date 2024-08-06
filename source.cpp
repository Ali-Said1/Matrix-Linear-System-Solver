#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef vector<vector<double>> matrix;

matrix get_ref(matrix);
matrix get_rref(matrix);
int check_sol(matrix);

int main()
{
    cout << "====Welcom to Linear Systems solver====\n";

    int r, c; // number of rows and columns
    cout << "Please enter the Number of Rows in the Matrix: ";
    cin >> r;
    cout << "Please enter the Number of Columns in the Matrix: ";
    cin >> c;

    const int rows = r, cols = c;

    if (!rows)
    {
        cout << "Number of Rows can't be zero in the matrix.\n";
        return 1;
    }
    if (cols < 2)
    {
        cout << "Number of Columns can't be less than 2 in the matrix.\n";
        return 1;
    }

    matrix original_matrix;
    // Getting user input
    for (int i = 0; i < rows; i++)
    {
        original_matrix.push_back(vector<double>{});
        for (int j = 0; j < cols; j++)
        {
            double input;
            cin >> input;
            original_matrix.at(i).push_back(input);
        }
    }

    matrix ref = get_ref(original_matrix);

    cout << "\n===================================================\n";
    cout << "Row Echelon form: \n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j == cols - 1)
            {
                cout << "|";
            }
            cout << setw(5) << setprecision(4);
            cout << (fabs(ref.at(i).at(j)) < 0.0001 ? 0 : ref.at(i).at(j));
            cout << " ";
        }
        cout << "\n";
    }

    matrix rref = get_rref(ref);

    cout << "===================================================\n";
    cout << "Reduced Row Echelon form: \n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j == cols - 1)
            {
                cout << "|";
            }
            cout << setw(5) << setprecision(4);
            cout << (fabs(rref.at(i).at(j)) < 0.0001 ? 0 : rref.at(i).at(j));
            cout << " ";
        }
        cout << "\n";
    }
    cout << "=================================================== \n";

    int solution = check_sol(rref);

    if (solution == 0)
    {
        cout << "The Matrix has a uniqe solution:\n";
        for (int i = 0; i < rref.size(); i++)
        {
            cout << setprecision(4);
            cout << "X" << i + 1 << " = ";
            cout << (fabs(rref.at(i).back()) < 0.0001 ? 0 : rref.at(i).back());
            if (i < rref.size() - 1)
            {
                cout << ", ";
            }
        }
    }
    else if (solution == 1)
    {
        cout << "The Matrix has infinitely many solutions.\n";
    }
    else
    {
        cout << "The Matrix has no solution.";
    }
    return 0;
}

// Creating Zereoes under each leading one
matrix get_ref(matrix user_matrix)
{
    int rows = user_matrix.size();
    int cols = user_matrix.at(0).size();
    int col_start = 0;
    for (int i = 0; i < rows; i++)
    {
        if (col_start == cols - 1)
            break;
        if (user_matrix.at(i).at(col_start) == 0)
        {
            for (int k = i + 1; k < rows; k++)
            {
                if (user_matrix.at(k).at(col_start) != 0)
                {
                    user_matrix.at(k).swap(user_matrix.at(i));
                    break;
                }
            }
        }

        if (user_matrix.at(i).at(col_start) == 0)
        {
            // no leading one at current position
            i--;
            col_start++;
            continue;
        }

        double divisor = user_matrix.at(i).at(col_start);
        for (int j = col_start; j < cols; j++)
        {
            user_matrix.at(i).at(j) /= divisor; // Craeting leading one at current row
        }

        for (int l = i + 1; l < rows; l++)
        {
            double subtraction_cf = user_matrix.at(l).at(col_start);
            for (int j = col_start; j < cols; j++)
            {
                user_matrix.at(l).at(j) -= user_matrix.at(i).at(j) * subtraction_cf;
            }
        }
        col_start++;
    }
    return user_matrix;
}

// Creating Zereoes on the whole column of each leading one
matrix get_rref(matrix in_matrix)
{

    int cols = in_matrix.at(0).size();

    for (int i = in_matrix.size() - 1; i > 0; i--)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            if (in_matrix.at(i).at(j) == 1)
            {
                for (int l = 0; l < i; l++)
                {
                    double substraction_cf = in_matrix.at(l).at(j);
                    for (int k = j; k < cols; k++)
                    {
                        in_matrix.at(l).at(k) -= in_matrix.at(i).at(k) * substraction_cf;
                    }
                }
                break;
            }
        }
    }

    return in_matrix;
}

int check_sol(matrix rref)
{
    int rows = rref.size();
    int unknowns = rref.at(0).size() - 1;
    int non_zero_rows{}, leading_ones{};

    vector<double> zero_row(rref.at(0).size(), 0);

    for (int i = 0; i < rows; i++)
    {
        // checking if the row is a zero row
        if (rref.at(i) == zero_row)
        {
            continue;
        }
        non_zero_rows++;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < unknowns; j++)
        {
            if (rref.at(i).at(j))
            {
                leading_ones++;
                break;
            }
        }
    }

    if (leading_ones == non_zero_rows && non_zero_rows == unknowns)
    {
        return 0;
    }

    if (leading_ones == non_zero_rows && non_zero_rows < unknowns)
    {
        return 1;
    }
    if (leading_ones < non_zero_rows)
    {
        return 2;
    }
}