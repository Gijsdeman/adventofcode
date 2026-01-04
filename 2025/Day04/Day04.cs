namespace _2025.Day04;

public class Day04 : Core.DayBase
{
    public override int Day => 4;

    private static int CountSurrounding(char[][] grid, char targetChar, int row, int col)
    {
        int count = 0;
        for (int rowOffset = -1; rowOffset <= 1; rowOffset++)
        {
            for (int colOffset = -1; colOffset <= 1; colOffset++)
            {
                if (rowOffset == 0 && colOffset == 0)
                    continue;
                if (grid[row + rowOffset][col + colOffset] == targetChar)
                {
                    count++;
                }
            }
        }
        return count;
    }

    public override string Part1(string input)
    {
        char[][] grid = GetCharGrid(input, StringSplitOptions.RemoveEmptyEntries);
        grid = Utils.Grid.AddBorder(grid, '.');

        int validPositions = 0;
        for (int i = 1; i < grid.Length - 1; i++)
        {
            for (int j = 1; j < grid[i].Length - 1; j++)
            {
                if (grid[i][j] != '@')
                    continue;
                if (CountSurrounding(grid, '@', i, j) < 4)
                    validPositions++;
            }
        }

        return validPositions.ToString();
    }

    public override string Part2(string input)
    {
        char[][] grid = GetCharGrid(input, StringSplitOptions.RemoveEmptyEntries);
        grid = Utils.Grid.AddBorder(grid, '.');

        int validPositions = 0;

        while (true)
        {
            int removedThisRound = 0;
            char[][] nextGrid = Utils.Grid.Copy(grid);

            for (int row = 1; row < grid.Length - 1; row++)
            {
                for (int col = 1; col < grid[row].Length - 1; col++)
                {
                    if (grid[row][col] == '@' && CountSurrounding(grid, '@', row, col) < 4)
                    {
                        nextGrid[row][col] = '.';
                        removedThisRound++;
                    }
                }
            }

            if (removedThisRound == 0)
                break;

            validPositions += removedThisRound;
            grid = nextGrid;
        }

        return validPositions.ToString();
    }
}
