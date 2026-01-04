using _2025.Utils;

namespace _2025.Day10;

public class Day10 : Core.DayBase
{
    public override int Day => 10;

    private static (int targetIndicator, List<int[]> operations, int[] counterTargets) ParseManual(
        string manual
    )
    {
        string[] parts = manual.Split(' ', StringSplitOptions.RemoveEmptyEntries);

        string binaryStr = parts[0].Trim('[', ']').Replace('.', '0').Replace('#', '1');
        string reversedBinary = new string(binaryStr.Reverse().ToArray());
        int targetIndicator = Convert.ToInt32(reversedBinary, 2);

        var operations = new List<int[]>();
        for (int i = 1; i < parts.Length - 1; i++)
        {
            string operationStr = parts[i].Trim('(', ')');
            string[] indices = operationStr.Split(',', StringSplitOptions.RemoveEmptyEntries);
            operations.Add([.. indices.Select(int.Parse)]);
        }

        int[] counterTargets =
        [
            .. parts[^1]
                .Trim('{', '}')
                .Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse),
        ];

        return (targetIndicator, operations, counterTargets);
    }

    private static int FindMinimumButtonPressesForIndicators(
        int targetIndicator,
        List<int[]> operations
    )
    {
        HashSet<int> visited = [];
        Queue<(int indicator, int pressCount)> queue = new();
        queue.Enqueue((0, 0));

        while (queue.Count > 0)
        {
            var (currentIndicator, pressCount) = queue.Dequeue();

            if (currentIndicator == targetIndicator)
                return pressCount;

            if (visited.Add(currentIndicator))
            {
                foreach (int[] operation in operations)
                {
                    int newIndicator = currentIndicator;
                    foreach (int bitPosition in operation)
                    {
                        newIndicator ^= 1 << bitPosition;
                    }
                    queue.Enqueue((newIndicator, pressCount + 1));
                }
            }
        }

        return -1;
    }

    private static int FindMinimumButtonPressesForJoltage(
        List<int[]> operations,
        int[] counterTargets
    )
    {
        var (matrix, numOperations, numCounters) = BuildAugmentedMatrix(operations, counterTargets);

        int[] pivotColumns = LinearAlgebra.GaussianEliminationWithPivoting(
            matrix,
            numOperations,
            numCounters
        );

        List<int> freeVariables = LinearAlgebra.IdentifyFreeVariables(pivotColumns, numOperations);

        return SolveWithFreeVariables(
            matrix,
            operations,
            counterTargets,
            pivotColumns,
            freeVariables,
            numOperations,
            numCounters
        );
    }

    private static (double[,] matrix, int numOps, int numCounters) BuildAugmentedMatrix(
        List<int[]> operations,
        int[] counterTargets
    )
    {
        int numOperations = operations.Count;
        int numCounters = counterTargets.Length;
        double[,] matrix = new double[numCounters, numOperations + 1];

        for (int counterIdx = 0; counterIdx < numCounters; counterIdx++)
        {
            matrix[counterIdx, 0] = counterTargets[counterIdx];

            for (int opIdx = 0; opIdx < numOperations; opIdx++)
            {
                if (operations[opIdx].Contains(counterIdx))
                {
                    matrix[counterIdx, opIdx + 1] = 1;
                }
            }
        }

        return (matrix, numOperations, numCounters);
    }

    private static int SolveWithFreeVariables(
        double[,] matrix,
        List<int[]> operations,
        int[] counterTargets,
        int[] pivotColumns,
        List<int> freeVariables,
        int numOperations,
        int numCounters
    )
    {
        int minPresses = int.MaxValue;

        bool IsValid(int[] solution)
        {
            for (int i = 0; i < numCounters; i++)
            {
                int count = operations
                    .Select((op, idx) => op.Contains(i) ? solution[idx] : 0)
                    .Sum();
                if (count != counterTargets[i])
                    return false;
            }
            return true;
        }

        void TryAssignment(int[] freeVarValues)
        {
            var solution = LinearAlgebra.BackSubstitute(
                matrix,
                pivotColumns,
                freeVarValues,
                freeVariables,
                numOperations,
                numCounters
            );

            if (solution != null && IsValid(solution))
                minPresses = Math.Min(minPresses, solution.Sum());
        }

        if (freeVariables.Count == 0)
        {
            TryAssignment([]);
            return minPresses;
        }

        // Try zeros first for quick initial bound
        TryAssignment(new int[freeVariables.Count]);

        var values = new int[freeVariables.Count];

        void Enumerate(int idx, int partialSum)
        {
            if (idx == freeVariables.Count)
            {
                TryAssignment(values);
                return;
            }

            int budget =
                minPresses == int.MaxValue ? counterTargets.Sum() : minPresses - partialSum - 1;

            if (budget < 0)
                return;

            for (int v = 0; v <= budget; v++)
            {
                values[idx] = v;
                Enumerate(idx + 1, partialSum + v);
            }
        }

        Enumerate(0, 0);
        return minPresses;
    }

    public override string Part1(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        int totalPresses = 0;

        foreach (string line in lines)
        {
            var (targetIndicator, operations, _) = ParseManual(line);
            totalPresses += FindMinimumButtonPressesForIndicators(targetIndicator, operations);
        }

        return totalPresses.ToString();
    }

    public override string Part2(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        int totalPresses = 0;

        foreach (string line in lines)
        {
            var (_, operations, counterTargets) = ParseManual(line);
            totalPresses += FindMinimumButtonPressesForJoltage(operations, counterTargets);
        }

        return totalPresses.ToString();
    }
}
