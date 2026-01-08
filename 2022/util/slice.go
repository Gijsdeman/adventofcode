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
