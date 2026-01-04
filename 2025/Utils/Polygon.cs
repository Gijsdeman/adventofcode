namespace _2025.Utils;

using Point = (long x, long y);

public class Polygon(List<Point> vertices)
{
    private readonly List<Point> vertices = vertices;

    public bool IsInside(Point point)
    {
        bool inside = false;
        int n = vertices.Count;
        for (int i = 0, j = n - 1; i < n; j = i++)
        {
            Point p1 = vertices[i];
            Point p2 = vertices[j];

            if (
                ((p1.y > point.y) != (p2.y > point.y))
                && (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)
            )
            {
                inside = !inside;
            }
        }

        return inside;
    }

    public static bool SegmentsIntersect(Point a1, Point a2, Point b1, Point b2)
    {
        long d1 = Cross(b1, b2, a1);
        long d2 = Cross(b1, b2, a2);
        long d3 = Cross(a1, a2, b1);
        long d4 = Cross(a1, a2, b2);

        return ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0))
            && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0));
    }

    private static long Cross(Point o, Point a, Point b)
    {
        return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
    }

    public List<Point> GetEdges() => vertices;
}
