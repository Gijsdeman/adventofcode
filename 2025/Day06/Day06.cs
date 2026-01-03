namespace _2025.Day06;

public class Day06 : Core.DayBase
{
    public override int Day => 6;

    public override string Part1(string input)
    {
        string[] lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        string[] operators = lines[^1].Split(' ', StringSplitOptions.RemoveEmptyEntries);
        long[] columnResults = [.. operators.Select(s => s == "*" ? 1L : 0L)];

        foreach (string line in lines.SkipLast(1))
        {
            string[] rowNumbers = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            for (int i = 0; i < rowNumbers.Length; i++)
            {
                long value = long.Parse(rowNumbers[i]);
                if (operators[i] == "*")
                    columnResults[i] *= value;
                else
                    columnResults[i] += value;
            }
        }

        return columnResults.Sum().ToString();
    }

    public override string Part2(string input)
    {
        string[] lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        string[] operators = lines[^1].Split(' ', StringSplitOptions.RemoveEmptyEntries);
        long[] columnResults = [.. operators.Select(s => s == "*" ? 1L : 0L)];
        string[] columnNumbers = new string[lines[0].Length];

        foreach (string line in lines.SkipLast(1))
        {
            for (int i = 0; i < columnNumbers.Length; i++)
            {
                columnNumbers[i] += line[i];
            }
        }

        int columnPointer = 0;
        foreach (string columnNumber in columnNumbers)
        {
            if (string.IsNullOrWhiteSpace(columnNumber))
            {
                columnPointer++;
                continue;
            }

            long value = long.Parse(columnNumber);
            if (operators[columnPointer] == "*")
                columnResults[columnPointer] *= value;
            else
                columnResults[columnPointer] += value;
        }

        return columnResults.Sum().ToString();
    }
}
