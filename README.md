# Matrix-Linear-System-Solver

This C++ program solves systems of linear equations by transforming a given matrix into its Row Echelon Form (REF) and Reduced Row Echelon Form (RREF). It then determines whether the system has a unique solution, infinitely many solutions, or no solution.

## Features

- **Input Matrix**: Accepts matrix input from the user.
- **REF and RREF Calculation**: Computes the Row Echelon Form and Reduced Row Echelon Form of the matrix.
- **Solution Analysis**: Determines the solution status of the system:
  - Unique solution
  - Infinitely many solutions
  - No solution

## Usage

1. **Compile the Program**:
   Use a C++ compiler like `g++` to compile the program:
   ```bash
   g++ source.cpp -o linear_solver
   ```

2. **Run the Program**:
   Execute the compiled program:
   - Windows
   ```bash
   linear_solver.exe
   ```
   - Linux & Mac
   ```bash
   chmod +x linear_solver
   ./linear_solver
   ```

3. **Input Matrix**:
   - Enter the number of rows and columns for the matrix.
   - Provide the matrix elements row by row.

4. **Output**:
   - The program will display the Row Echelon Form and Reduced Row Echelon Form of the matrix.
   - It will also provide information on the type of solution for the system of equations.

## Example

### Input
```
Please enter the Number of Rows in the Matrix: 3
Please enter the Number of Columns in the Matrix: 4
0 1 1 2
2 3 0 -2
3 3 6 9
```

### Output
```
===================================================
Row Echelon form:
    1   1.5     0 |   -1
    0     1     1 |    2
    0     0     1 |    2
===================================================
Reduced Row Echelon form:
    1     0     0 |   -1
    0     1     0 |    0
    0     0     1 |    2
===================================================
The Matrix has a unique solution:
X1 = -1, X2 = 0, X3 = 2
```

## Functions

- `matrix get_ref(matrix user_matrix)`: Converts the matrix to Row Echelon Form.
- `matrix get_rref(matrix in_matrix)`: Converts the matrix to Reduced Row Echelon Form.
- `int check_sol(matrix rref)`: Determines the solution type based on the RREF matrix.

## Dependencies

- C++ Standard Library

## Notes

- The program assumes that the input matrix has at least 2 columns.
- The precision for output values is set to 4 decimal places.