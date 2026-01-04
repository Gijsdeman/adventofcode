namespace _2025.Utils;

public static class LinearAlgebra
{
    public static int[] GaussianEliminationWithPivoting(
        double[,] matrix,
        int numVariables,
        int numEquations
    )
    {
        int[] pivotColumns = new int[numEquations];
        Array.Fill(pivotColumns, -1);

        int currentRow = 0;

        for (int col = 1; col <= numVariables && currentRow < numEquations; col++)
        {
            int pivotRow = currentRow;
            for (int row = currentRow + 1; row < numEquations; row++)
            {
                if (Math.Abs(matrix[row, col]) > Math.Abs(matrix[pivotRow, col]))
                    pivotRow = row;
            }

            if (Math.Abs(matrix[pivotRow, col]) < 1e-10)
                continue;

            if (pivotRow != currentRow)
            {
                for (int j = 0; j <= numVariables; j++)
                {
                    (matrix[currentRow, j], matrix[pivotRow, j]) = (
                        matrix[pivotRow, j],
                        matrix[currentRow, j]
                    );
                }
            }

            pivotColumns[currentRow] = col;

            double pivotValue = matrix[currentRow, col];
            for (int j = 0; j <= numVariables; j++)
                matrix[currentRow, j] /= pivotValue;

            for (int row = 0; row < numEquations; row++)
            {
                if (row != currentRow && Math.Abs(matrix[row, col]) > 1e-10)
                {
                    double factor = matrix[row, col];
                    for (int j = 0; j <= numVariables; j++)
                        matrix[row, j] -= factor * matrix[currentRow, j];
                }
            }

            currentRow++;
        }

        return pivotColumns;
    }

    public static List<int> IdentifyFreeVariables(int[] pivotColumns, int numVariables)
    {
        List<int> freeVariables = [];
        HashSet<int> pivotColumnSet = [.. pivotColumns.Where(p => p != -1)];

        for (int col = 1; col <= numVariables; col++)
        {
            if (!pivotColumnSet.Contains(col))
                freeVariables.Add(col - 1);
        }

        return freeVariables;
    }

    public static int[]? BackSubstitute(
        double[,] matrix,
        int[] pivotColumns,
        int[] freeVariableValues,
        List<int> freeVariableIndices,
        int numVariables,
        int numEquations
    )
    {
        int[] solution = new int[numVariables];

        for (int i = 0; i < freeVariableIndices.Count; i++)
            solution[freeVariableIndices[i]] = freeVariableValues[i];

        for (int row = 0; row < numEquations; row++)
        {
            if (pivotColumns[row] == -1)
                continue;

            double value = matrix[row, 0];
            for (int col = 1; col <= numVariables; col++)
            {
                if (col != pivotColumns[row])
                    value -= matrix[row, col] * solution[col - 1];
            }

            if (value < -0.5 || Math.Abs(value - Math.Round(value)) > 0.1)
                return null;

            solution[pivotColumns[row] - 1] = (int)Math.Round(value);
        }

        return solution.All(x => x >= 0) ? solution : null;
    }
}
