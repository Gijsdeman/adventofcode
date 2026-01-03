namespace _2025.Day03;

public class Day03 : Core.DayBase
{
    public override int Day => 3;

    private static (char maxChar, int position) FindMaxInRange(
        ReadOnlySpan<char> span,
        int startIndex,
        int endIndex
    )
    {
        char maxChar = '0';
        int maxPosition = startIndex;

        for (int j = startIndex; j < endIndex; j++)
        {
            if (span[j] > maxChar)
            {
                maxChar = span[j];
                maxPosition = j;
            }
        }

        return (maxChar, maxPosition);
    }

    private static long CalculateMaxJoltage(ReadOnlySpan<char> bank, int numberOfBatteries)
    {
        long result = 0;
        int startIndex = 0;

        for (int i = 0; i < numberOfBatteries; i++)
        {
            int endIndex = bank.Length - (numberOfBatteries - i - 1);
            var (maxBattery, maxPosition) = FindMaxInRange(bank, startIndex, endIndex);

            result = result * 10 + (maxBattery - '0');
            startIndex = maxPosition + 1;
        }

        return result;
    }

    public override string Part1(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        long result = 0;
        foreach (string bank in lines)
        {
            result += CalculateMaxJoltage(bank, 2);
        }

        return result.ToString();
    }

    public override string Part2(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        long result = 0;

        foreach (string bank in lines)
        {
            result += CalculateMaxJoltage(bank, 12);
        }

        return result.ToString();
    }
}
