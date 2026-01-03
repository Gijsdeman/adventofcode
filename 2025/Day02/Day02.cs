namespace _2025.Day02;

public class Day02 : Core.DayBase
{
    public override int Day => 2;

    private static bool IsPalindrome(string s)
    {
        int half = s.Length / 2;
        return s[..half] == s[half..];
    }

    private static bool HasRepeatingPattern(ReadOnlySpan<char> s)
    {
        int len = s.Length;
        for (int patternLen = 1; patternLen <= len / 2; patternLen++)
        {
            if (len % patternLen == 0)
            {
                bool matches = true;
                for (int i = patternLen; i < len; i++)
                {
                    if (s[i] != s[i % patternLen])
                    {
                        matches = false;
                        break;
                    }
                }
                if (matches)
                    return true;
            }
        }
        return false;
    }

    private static long SumRange(long start, long end, Func<string, bool> predicate)
    {
        long sum = 0;
        for (long i = start; i <= end; i++)
        {
            string str = i.ToString();
            if (predicate(str))
                sum += i;
        }
        return sum;
    }

    public override string Part1(string input)
    {
        long result = 0;
        foreach (var range in input.Split(','))
        {
            var bounds = range.Split('-');
            long start = long.Parse(bounds[0]);
            long end = long.Parse(bounds[1]);
            result += SumRange(start, end, IsPalindrome);
        }
        return result.ToString();
    }

    public override string Part2(string input)
    {
        long result = 0;
        foreach (var range in input.Split(','))
        {
            var bounds = range.Split('-');
            long start = long.Parse(bounds[0]);
            long end = long.Parse(bounds[1]);
            result += SumRange(start, end, s => HasRepeatingPattern(s));
        }
        return result.ToString();
    }
}
