package maths

func MaxInt(firstInteger int, secondInteger int) (maximum int) {
	if firstInteger > secondInteger {
		maximum = firstInteger
	} else {
		maximum = secondInteger
	}
	return maximum
}
