namespace _2025.Core;

public class DayGenerator
{
    public static async Task<bool> GenerateDayAsync(
        int day,
        string workspaceRoot,
        string sessionCookie
    )
    {
        var dayFolder = Path.Combine(workspaceRoot, $"Day{day:D2}");
        var dayFile = Path.Combine(dayFolder, $"Day{day:D2}.cs");
        var inputFile = Path.Combine(dayFolder, "input");
        var exampleFile = Path.Combine(dayFolder, "example");

        Directory.CreateDirectory(dayFolder);

        var template = GenerateDayTemplate(day);
        await File.WriteAllTextAsync(dayFile, template);
        await File.WriteAllTextAsync(exampleFile, string.Empty);

        var fetcher = new InputFetcher(sessionCookie);
        await fetcher.FetchAndSaveInputAsync(day, inputFile);

        return true;
    }

    private static string GenerateDayTemplate(int day)
    {
        return $@"namespace _2025.Day{day:D2};

public class Day{day:D2} : Core.DayBase
{{
    public override int Day => {day};

    public override string Part1(string input)
    {{
        // Implement your solution here
        var lines = GetLines(input);
        return ""Not implemented yet"";
    }}

    public override string Part2(string input)
    {{
        // Implement your solution here
        var lines = GetLines(input);
        return ""Not implemented yet"";
    }}
}}
";
    }
}
