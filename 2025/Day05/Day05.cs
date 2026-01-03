namespace _2025.Day05;

using Range = (long start, long end);
using SweepEvent = (long position, int delta);

public class Day05 : Core.DayBase
{
    public override int Day => 5;

    private static (List<SweepEvent> sweepEvents, List<long> freshIds) SplitRangesAndIds(
        string[] rows
    )
    {
        var freshIds = new List<long>();
        var sweepEvents = new List<SweepEvent>();

        foreach (var row in rows)
        {
            if (row.Contains('-'))
            {
                var parts = row.Split('-');
                long rangeStart = long.Parse(parts[0]);
                long rangeEnd = long.Parse(parts[1]);
                sweepEvents.Add((rangeStart, 1));
                sweepEvents.Add((rangeEnd, -1));
            }
            else
            {
                freshIds.Add(long.Parse(row));
            }
        }

        return (sweepEvents, freshIds);
    }

    private static List<Range> MergeOverlappingRanges(List<SweepEvent> sweepEvents)
    {
        sweepEvents = [.. sweepEvents.OrderBy(e => e.position).ThenByDescending(e => e.delta)];

        var mergedRanges = new List<Range>();
        long mergedRangeStart = 0;
        int activeRanges = 0;

        foreach (var (position, delta) in sweepEvents)
        {
            int previousActiveRanges = activeRanges;
            activeRanges += delta;

            if (previousActiveRanges == 0 && activeRanges == 1)
            {
                mergedRangeStart = position;
            }
            else if (previousActiveRanges == 1 && activeRanges == 0)
            {
                mergedRanges.Add((mergedRangeStart, position));
            }
        }

        return mergedRanges;
    }

    public override string Part1(string input)
    {
        string[] lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        var (sweepEvents, freshIds) = SplitRangesAndIds(lines);
        var mergedFreshRanges = MergeOverlappingRanges(sweepEvents);

        int totalFreshIds = 0;
        foreach (long id in freshIds)
        {
            foreach (var (start, end) in mergedFreshRanges)
            {
                if (id >= start && id <= end)
                {
                    totalFreshIds++;
                    break;
                }
            }
        }

        return totalFreshIds.ToString();
    }

    public override string Part2(string input)
    {
        string[] lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        var (sweepEvents, _) = SplitRangesAndIds(lines);
        var mergedFreshRanges = MergeOverlappingRanges(sweepEvents);

        long totalFreshIds = 0;
        foreach (var (start, end) in mergedFreshRanges)
        {
            totalFreshIds += end - start + 1;
        }

        return totalFreshIds.ToString();
    }
}
