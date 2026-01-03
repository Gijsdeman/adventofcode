using System.Dynamic;

namespace _2025.Day07;

public class Day07 : Core.DayBase
{
    public override int Day => 7;

    public override string Part1(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);

        var currentPositions = new HashSet<int> { lines[0].IndexOf('S') };
        var nextPositions = new HashSet<int>();
        int splitCount = 0;

        foreach (string line in lines.Skip(1))
        {
            nextPositions.Clear();
            foreach (int position in currentPositions)
            {
                if (line[position] == '^')
                {
                    splitCount++;
                    if (position > 0)
                        nextPositions.Add(position - 1);
                    if (position < line.Length - 1)
                        nextPositions.Add(position + 1);
                }
                else
                {
                    nextPositions.Add(position);
                }
            }

            (currentPositions, nextPositions) = (nextPositions, currentPositions);
        }

        return splitCount.ToString();
    }

    public override string Part2(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);

        long[] beams = new long[lines[0].Length];
        beams[lines[0].IndexOf('S')] = 1;

        foreach (string line in lines.Skip(1))
        {
            int splitterPosition = line.IndexOf('^');
            while (splitterPosition != -1)
            {
                long beamCount = beams[splitterPosition];
                if (beamCount > 0)
                {
                    beams[splitterPosition] = 0;
                    beams[splitterPosition - 1] += beamCount;
                    beams[splitterPosition + 1] += beamCount;
                }
                splitterPosition = line.IndexOf('^', splitterPosition + 1);
            }
        }

        return beams.Sum().ToString();
    }
}
