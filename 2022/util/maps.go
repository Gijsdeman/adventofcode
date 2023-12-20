package util

func ReverseMap[K int | string, V int | string](forwardMap map[K]V) (reverseMap map[V]K) {
	reverseMap = make(map[V]K)
	for k, v := range forwardMap {
		reverseMap[v] = k
	}
	return reverseMap
}
