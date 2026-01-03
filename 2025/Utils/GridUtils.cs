namespace _2025.Utils;

public static class GridUtils
{
    public static void Print(char[][] grid)
    {
        foreach (var row in grid)
        {
            Console.WriteLine(new string(row));
        }
    }

    public static char[][] Copy(char[][] grid)
    {
        return grid.Select(row => row.ToArray()).ToArray();
    }

    public static char[][] AddBorder(char[][] grid, char borderChar)
    {
        if (grid.Length == 0)
            return [];

        int width = grid[0].Length;
        int height = grid.Length;

        var borderedGrid = new char[height + 2][];

        borderedGrid[0] = [.. Enumerable.Repeat(borderChar, width + 2)];
        for (int i = 0; i < height; i++)
        {
            borderedGrid[i + 1] = new char[width + 2];
            borderedGrid[i + 1][0] = borderChar;
            Array.Copy(grid[i], 0, borderedGrid[i + 1], 1, width);
            borderedGrid[i + 1][width + 1] = borderChar;
        }
        borderedGrid[height + 1] = [.. Enumerable.Repeat(borderChar, width + 2)];

        return borderedGrid;
    }
}
