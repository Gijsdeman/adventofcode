namespace _2025.Core;

public class InputFetcher
{
    private const string BaseUrl = "https://adventofcode.com/2025/day";
    private readonly HttpClient _httpClient;

    public InputFetcher(string sessionCookie)
    {
        _httpClient = new HttpClient();
        _httpClient.DefaultRequestHeaders.Add("Cookie", $"session={sessionCookie}");
    }

    public async Task<string> FetchInputAsync(int day)
    {
        try
        {
            var response = await _httpClient.GetAsync($"{BaseUrl}/{day}/input");
            response.EnsureSuccessStatusCode();
            return await response.Content.ReadAsStringAsync();
        }
        catch (Exception ex)
        {
            throw new Exception($"Failed to fetch input for day {day}: {ex.Message}");
        }
    }

    public async Task FetchAndSaveInputAsync(int dayNum, string path)
    {
        try
        {
            var input = await FetchInputAsync(dayNum);
            
            var directory = Path.GetDirectoryName(path);
            if (directory != null && !Directory.Exists(directory))
            {
                Directory.CreateDirectory(directory);
            }
            
            await File.WriteAllTextAsync(path, input);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}
