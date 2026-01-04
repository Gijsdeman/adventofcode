namespace _2025.Day09;

using Point = (long x, long y);
using Polygon = Utils.Polygon;

public class Day09 : Core.DayBase
{
    public override int Day => 9;

    private static bool ContainsRectangle(
        Polygon polygon,
        long minX,
        long maxX,
        long minY,
        long maxY
    )
    {
        if (
            !polygon.IsInside((minX, minY))
            || !polygon.IsInside((maxX, minY))
            || !polygon.IsInside((minX, maxY))
            || !polygon.IsInside((maxX, maxY))
        )
            return false;

        var vertices = polygon.GetEdges();
        int n = vertices.Count;
        for (int i = 0; i < n; i++)
        {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1) % n];

            if (SegmentCrossesRectangle(p1, p2, minX, maxX, minY, maxY))
                return false;
        }

        return true;
    }

    private static bool SegmentCrossesRectangle(
        Point p1,
        Point p2,
        long minX,
        long maxX,
        long minY,
        long maxY
    )
    {
        if (Polygon.SegmentsIntersect(p1, p2, (minX, minY), (maxX, minY)))
            return true;
        if (Polygon.SegmentsIntersect(p1, p2, (maxX, minY), (maxX, maxY)))
            return true;
        if (Polygon.SegmentsIntersect(p1, p2, (maxX, maxY), (minX, maxY)))
            return true;
        if (Polygon.SegmentsIntersect(p1, p2, (minX, maxY), (minX, minY)))
            return true;

        return false;
    }

    public override string Part1(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        var redTiles = new List<Point>();

        foreach (string line in lines)
        {
            var parts = line.Split(',');
            redTiles.Add((int.Parse(parts[0]), int.Parse(parts[1])));
        }

        long maxArea = 0;
        foreach (Point tile1 in redTiles)
        {
            foreach (Point tile2 in redTiles)
            {
                if (tile1 != tile2)
                {
                    long dx = Math.Abs(tile2.x - tile1.x) + 1;
                    long dy = Math.Abs(tile2.y - tile1.y) + 1;
                    maxArea = Math.Max(maxArea, dx * dy);
                }
            }
        }

        return maxArea.ToString();
    }

    public override string Part2(string input)
    {
        var lines = GetLines(input, StringSplitOptions.RemoveEmptyEntries);
        var redTiles = new List<Point>();

        foreach (string line in lines)
        {
            var parts = line.Split(',');
            redTiles.Add((int.Parse(parts[0]), int.Parse(parts[1])));
        }

        var polygon = new Polygon(redTiles);

        long maxArea = 0;
        foreach (Point tile1 in redTiles)
        {
            foreach (Point tile2 in redTiles)
            {
                if (tile1 != tile2)
                {
                    long minX = Math.Min(tile1.x, tile2.x);
                    long maxX = Math.Max(tile1.x, tile2.x);
                    long minY = Math.Min(tile1.y, tile2.y);
                    long maxY = Math.Max(tile1.y, tile2.y);

                    if (ContainsRectangle(polygon, minX, maxX, minY, maxY))
                    {
                        long dx = maxX - minX + 1;
                        long dy = maxY - minY + 1;
                        maxArea = Math.Max(maxArea, dx * dy);
                    }
                }
            }
        }

        return maxArea.ToString();
    }
}
