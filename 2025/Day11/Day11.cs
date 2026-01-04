namespace _2025.Day11;

using Graph = Dictionary<string, List<string>>;

public class Day11 : Core.DayBase
{
    public override int Day => 11;

    private static long CountPaths(
        Graph graph,
        string start,
        string end,
        HashSet<string> requiredNodes
    )
    {
        var requiredNodeToBit = new Dictionary<string, int>();
        int bit = 0;
        foreach (var node in requiredNodes)
            requiredNodeToBit[node] = 1 << bit++;

        int allRequiredBitsSet = (1 << requiredNodes.Count) - 1;
        var visited = new HashSet<string>();
        var memoization = new Dictionary<(string, int), long>();

        return Search(start, 0);

        long Search(string current, int visitedRequired)
        {
            if (current == end)
                return visitedRequired == allRequiredBitsSet ? 1 : 0;

            if (memoization.TryGetValue((current, visitedRequired), out var cached))
                return cached;

            if (!visited.Add(current))
                return 0;

            long count = 0;
            if (graph.TryGetValue(current, out var neighbors))
            {
                foreach (var next in neighbors)
                {
                    int nextVisitedRequired = visitedRequired;
                    if (requiredNodeToBit.TryGetValue(next, out var nodeBit))
                        nextVisitedRequired |= nodeBit;

                    count += Search(next, nextVisitedRequired);
                }
            }

            visited.Remove(current);
            return memoization[(current, visitedRequired)] = count;
        }
    }

    private static Graph BuildGraph(string input)
    {
        var graph = new Graph();

        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);

        foreach (string line in lines)
        {
            var parts = line.Split(":", StringSplitOptions.RemoveEmptyEntries);
            var node = parts[0];
            var neighbors = parts[1].Split(" ", StringSplitOptions.RemoveEmptyEntries).ToList();
            graph[node] = neighbors;
        }

        return graph;
    }

    public override string Part1(string input)
    {
        var graph = BuildGraph(input);
        var pathCount = CountPaths(graph, "you", "out", []);

        return pathCount.ToString();
    }

    public override string Part2(string input)
    {
        var graph = BuildGraph(input);
        var pathCount = CountPaths(graph, "svr", "out", ["fft", "dac"]);

        return pathCount.ToString();
    }
}
