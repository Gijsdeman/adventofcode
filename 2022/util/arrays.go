package util

func IntersectHash[T comparable](firstArray []T, secondArray []T) []T {
	set := make([]T, 0)
	hash := make(map[T]struct{})

	for _, item := range firstArray {
		// "Equivalent" to bool, does not take up any space
		hash[item] = struct{}{}
	}

	for _, item := range secondArray {
		_, contained := hash[item]
		if contained {
			set = append(set, item)
		}
	}

	return set
}
