package core

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
)

type InputFetcher struct {
	sessionCookie string
	baseURL       string
	client        *http.Client
}

func NewInputFetcher(sessionCookie string, year int) *InputFetcher {
	return &InputFetcher{
		sessionCookie: sessionCookie,
		baseURL:       fmt.Sprintf("https://adventofcode.com/%d/day", year),
		client:        &http.Client{},
	}
}

// FetchInput downloads the input for a specific day
func (f *InputFetcher) FetchInput(day int) (string, error) {
	url := fmt.Sprintf("%s/%d/input", f.baseURL, day)

	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return "", fmt.Errorf("failed to create request: %w", err)
	}

	req.Header.Add("Cookie", fmt.Sprintf("session=%s", f.sessionCookie))

	resp, err := f.client.Do(req)
	if err != nil {
		return "", fmt.Errorf("failed to fetch input: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return "", fmt.Errorf("failed to fetch input: status code %d", resp.StatusCode)
	}

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return "", fmt.Errorf("failed to read response: %w", err)
	}

	return string(body), nil
}

// FetchAndSaveInput downloads and saves the input for a specific day
func (f *InputFetcher) FetchAndSaveInput(day int, path string) error {
	input, err := f.FetchInput(day)
	if err != nil {
		return err
	}

	dir := filepath.Dir(path)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return fmt.Errorf("failed to create directory: %w", err)
	}

	if err := os.WriteFile(path, []byte(input), 0644); err != nil {
		return fmt.Errorf("failed to write file: %w", err)
	}

	return nil
}
