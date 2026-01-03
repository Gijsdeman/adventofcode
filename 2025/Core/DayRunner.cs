using System.Reflection;
using System.Diagnostics;

namespace _2025.Core;

public class DayRunner
{
    private readonly Dictionary<int, DayBase> _days;

    public DayRunner()
    {
        _days = DiscoverDays();
    }

    private static Dictionary<int, DayBase> DiscoverDays()
    {
        var dayType = typeof(DayBase);
        var assembly = Assembly.GetExecutingAssembly();
        
        var days = assembly.GetTypes()
            .Where(t => t.IsClass && !t.IsAbstract && t.IsSubclassOf(dayType))
            .Select(t => (DayBase)Activator.CreateInstance(t)!)
            .ToDictionary(d => d.Day);

        return days;
    }

    public bool HasDay (int day)
    {
        return _days.ContainsKey(day);
    }

    public void RunDay(int day, string inputPath, string part)
    {
        if (!_days.TryGetValue(day, out var dayInstance))
        {
            Console.WriteLine($"Day {day} not found.");
            return;
        }
        
        var input = LoadInput(inputPath);
        if (string.IsNullOrEmpty(input))
        {
            Console.WriteLine($"No input found for day {day}.");
            return;
        }

        if (part == "0" || part == "1")
        {
            var timer = Stopwatch.StartNew();
            var part1Result = dayInstance.Part1(input);
            timer.Stop();
            Console.WriteLine($"part 1: {timer.ElapsedMilliseconds}ms");
            Console.WriteLine($"{part1Result}");
        }

        if (part == "0" || part == "2")
        {
            var timer = Stopwatch.StartNew();
            var part2Result = dayInstance.Part2(input);
            timer.Stop();
            Console.WriteLine($"part 2: {timer.ElapsedMilliseconds}ms");
            Console.WriteLine($"{part2Result}");
        }
    }

    private static string LoadInput(string inputPath)
    {
        if (!string.IsNullOrEmpty(inputPath) && File.Exists(inputPath))
        {
            return File.ReadAllText(inputPath);
        }

        return string.Empty;
    }
}
