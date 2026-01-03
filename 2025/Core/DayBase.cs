namespace _2025.Core;

public abstract class DayBase
{
    public abstract int Day { get; }
    
    public abstract string Part1(string input);
    
    public abstract string Part2(string input);
    
    protected static string[] GetLines(string input, StringSplitOptions options = StringSplitOptions.None) => 
        input.Split('\n', options);
    
    protected static int[] GetIntegers(string input, StringSplitOptions options = StringSplitOptions.None) =>
        [.. input.Split('\n', options).Select(int.Parse)];
}
