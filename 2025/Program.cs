using _2025.Core;

var runner = new DayRunner();

var dayEnv = Environment.GetEnvironmentVariable("DAY") ?? "0";
var partEnv = Environment.GetEnvironmentVariable("PART") ?? "0";
var exampleEnv = Environment.GetEnvironmentVariable("EXAMPLE") ?? "F";
var cwdEnv = Environment.GetEnvironmentVariable("CWD") ?? Directory.GetCurrentDirectory();
var sessionCookie = Environment.GetEnvironmentVariable("SESSION");

if (!int.TryParse(dayEnv, out var day) || day < 1 || day > 12)
{
    Console.WriteLine($"Invalid DAY environment variable: {dayEnv}");
    return;
}

if (!int.TryParse(partEnv, out var part) || part < 0 || part > 2)
{
    Console.WriteLine($"Invalid PART environment variable: {partEnv}");
    return;
}

if (exampleEnv != "T" && exampleEnv != "F")
{
    Console.WriteLine($"Invalid EXAMPLE environment variable: {exampleEnv}");
    return;
}

if (string.IsNullOrEmpty(sessionCookie))
{
    Console.WriteLine("Set SESSION environment variable to fetch inputs");
    return;
}

var dayFolder = $"Day{day:D2}";
var outputType = exampleEnv == "T" ? "example" : "input";
var inputPath = Path.Combine(cwdEnv, dayFolder, outputType);

Console.WriteLine($"year 2025, day {day}");

if (exampleEnv == "F" && !File.Exists(inputPath))
{
    var fetcher = new InputFetcher(sessionCookie);
    await fetcher.FetchAndSaveInputAsync(day, inputPath);
}

if (!runner.HasDay(day))
{
    await DayGenerator.GenerateDayAsync(day, cwdEnv, sessionCookie);
} else {
    runner.RunDay(day, inputPath, partEnv);
}