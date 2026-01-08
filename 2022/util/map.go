package util

// ReverseMap reverses a map with comparable keys and values
func ReverseMap[K comparable, V comparable](forwardMap map[K]V) (reverseMap map[V]K) {
	reverseMap = make(map[V]K)
	for k, v := range forwardMap {
		reverseMap[v] = k
	}
	return reverseMap
}
