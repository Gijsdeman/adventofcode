package util

// IntersectMultiple returns the intersection of multiple arrays
func IntersectMultiple[T comparable](slice ...[]T) []T {
	if len(slice) == 0 {
		return []T{}
	}
	result := slice[0]
	for i := 1; i < len(slice); i++ {
		result = IntersectHash(result, slice[i])
	}
	return result
}

// IntersectHash returns the intersection of two arrays using a hash map for efficiency
func IntersectHash[T comparable](firstSlice []T, secondSlice []T) []T {
	set := make([]T, 0)
	hash := make(map[T]struct{})

	for _, item := range firstSlice {
		hash[item] = struct{}{}
	}

	for _, item := range secondSlice {
		_, contained := hash[item]
		if contained {
			set = append(set, item)
		}
	}

	return set
}

// Reverse reverses a slice in place
func Reverse[T any](slice []T) {
	for i := 0; i < len(slice)/2; i++ {
		slice[i], slice[len(slice)-1-i] = slice[len(slice)-1-i], slice[i]
	}
}

// AddBorder adds a border of the specified character around a grid
func AddBorder(grid [][]rune, borderChar rune) [][]rune {
	if len(grid) == 0 {
		return grid
	}

	oldHeight := len(grid)
	oldWidth := len(grid[0])
	newHeight := oldHeight + 2
	newWidth := oldWidth + 2

	bordered := make([][]rune, newHeight)

	// Top border row
	bordered[0] = make([]rune, newWidth)
	for i := range bordered[0] {
		bordered[0][i] = borderChar
	}

	// Middle rows with left and right borders
	for i := 0; i < oldHeight; i++ {
		bordered[i+1] = make([]rune, newWidth)
		bordered[i+1][0] = borderChar
		copy(bordered[i+1][1:], grid[i])
		bordered[i+1][newWidth-1] = borderChar
	}

	// Bottom border row
	bordered[newHeight-1] = make([]rune, newWidth)
	for i := range bordered[newHeight-1] {
		bordered[newHeight-1][i] = borderChar
	}

	return bordered
}
