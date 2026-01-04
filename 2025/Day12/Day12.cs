namespace _2025.Day12;

public class Day12 : Core.DayBase
{
    public override int Day => 12;

    public override string Part1(string input)
    {
        var shapeAreas = new Dictionary<int, int>();
        int currentShape = 0;
        int validBoxes = 0;

        foreach (var line in GetLines(input, StringSplitOptions.RemoveEmptyEntries))
        {
            if (line.EndsWith(':'))
            {
                shapeAreas[currentShape = int.Parse(line[..^1])] = 0;
                continue;
            }

            if (line.Contains('#'))
            {
                shapeAreas[currentShape] += line.Count(c => c == '#');
                continue;
            }

            var (dimensions, counts) = (
                line.Split(':')[0].Split('x').Select(int.Parse).ToArray(),
                line.Split(':')[1]
                    .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                    .Select(int.Parse)
            );

            var totalArea = counts.Select((count, id) => count * shapeAreas[id]).Sum();
            if (totalArea <= dimensions[0] * dimensions[1])
                validBoxes++;
        }

        return validBoxes.ToString();
    }

    public override string Part2(string input)
    {
        return "";
    }
}
