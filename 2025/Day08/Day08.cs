namespace _2025.Day08;

using Junction = (int x, int y, int z);

public class Day08 : Core.DayBase
{
    public override int Day => 8;

    private class UnionFind
    {
        private readonly Dictionary<Junction, Junction> parent = [];
        private readonly Dictionary<Junction, int> size = [];

        public void Add(Junction point)
        {
            parent[point] = point;
            size[point] = 1;
        }

        public Junction Find(Junction point)
        {
            if (parent[point] != point)
                parent[point] = Find(parent[point]);
            return parent[point];
        }

        public bool Union(Junction p1, Junction p2)
        {
            Junction root1 = Find(p1);
            Junction root2 = Find(p2);

            if (root1 == root2)
                return false;

            if (size[root1] < size[root2])
                (root1, root2) = (root2, root1);

            parent[root2] = root1;
            size[root1] += size[root2];
            return true;
        }

        public List<int> GetComponentSizes()
        {
            var rootSizes = new Dictionary<Junction, int>();
            foreach (var point in parent.Keys)
            {
                Junction root = Find(point);
                rootSizes[root] = size[root];
            }
            return [.. rootSizes.Values.OrderDescending()];
        }

        public int GetSize(Junction point) => size[Find(point)];
    }

    private static long Distance(Junction p1, Junction p2)
    {
        long dx = p2.x - p1.x;
        long dy = p2.y - p1.y;
        long dz = p2.z - p1.z;
        return dx * dx + dy * dy + dz * dz;
    }

    private static List<(
        Junction junction1,
        Junction junction2,
        long distance
    )> GetSortedConnections(List<Junction> junctions)
    {
        var connections = new List<(Junction junction1, Junction junction2, long distance)>();
        for (int i = 0; i < junctions.Count; i++)
        {
            for (int j = i + 1; j < junctions.Count; j++)
            {
                long dist = Distance(junctions[i], junctions[j]);
                connections.Add((junctions[i], junctions[j], dist));
            }
        }

        connections.Sort((a, b) => a.distance.CompareTo(b.distance));
        return connections;
    }

    private static string AdaptedKruskal(List<Junction> points, int maxIterations)
    {
        var connections = GetSortedConnections(points);
        var union = new UnionFind();

        foreach (var point in points)
            union.Add(point);

        for (int i = 0; i < connections.Count && i < maxIterations; i++)
        {
            var (junction1, junction2, _) = connections[i];

            if (union.Union(junction1, junction2))
            {
                if (union.GetSize(junction1) == points.Count)
                    return (junction1.x * junction2.x).ToString();
            }
        }

        var componentSizes = union.GetComponentSizes();
        return componentSizes.Take(3).Aggregate(1, (acc, size) => acc * size).ToString();
    }

    public override string Part1(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        var points = new List<Junction>();

        foreach (string line in lines)
        {
            var coords = line.Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse)
                .ToArray();
            var point = (coords[0], coords[1], coords[2]);
            points.Add(point);
        }

        return AdaptedKruskal(points, 1000);
    }

    public override string Part2(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        var points = new List<Junction>();

        foreach (string line in lines)
        {
            var coords = line.Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse)
                .ToArray();
            var point = (coords[0], coords[1], coords[2]);
            points.Add(point);
        }

        return AdaptedKruskal(points, int.MaxValue);
    }
}
