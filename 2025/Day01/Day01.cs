namespace _2025.Day01;

public class Day01 : Core.DayBase
{
    public override int Day => 1;

    private static int ParseSteps(string line) => 
        int.Parse(line[1..]) * (line[0] == 'L' ? -1 : 1);

    private static int Wrap(int position, int size)
    {
        position %= size;
        return position < 0 ? position + size : position;
    }

    public override string Part1(string input)
    {
        int position = 50;
        int password = 0;

        foreach (var line in GetLines(input, StringSplitOptions.RemoveEmptyEntries))
        {
            position = Wrap(position + ParseSteps(line), 100);
            if (position == 0) password++;
        }

        return password.ToString();
    }

    public override string Part2(string input)
    {
        int position = 50;
        int password = 0;

        foreach (var line in GetLines(input, StringSplitOptions.RemoveEmptyEntries))
        {
            int steps = ParseSteps(line);
            int fullRotations = Math.Abs(steps) / 100;
            int newPositionRaw = position + (steps % 100);
            
            password += fullRotations;
            if (position != 0 && (newPositionRaw <= 0 || newPositionRaw >= 100))
                password++;

            position = Wrap(newPositionRaw, 100);
        }

        return password.ToString();
    }
}
