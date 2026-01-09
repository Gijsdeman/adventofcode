package util

// Set is a generic set implementation using a map
type Set[T comparable] struct {
	items map[T]struct{}
}

// NewSet creates a new empty set
func NewSet[T comparable]() *Set[T] {
	return &Set[T]{items: make(map[T]struct{})}
}

// Add adds an item to the set
func (s *Set[T]) Add(item T) {
	s.items[item] = struct{}{}
}

// Contains checks if an item is in the set
func (s *Set[T]) Contains(item T) bool {
	_, ok := s.items[item]
	return ok
}

// Remove removes an item from the set
func (s *Set[T]) Remove(item T) {
	delete(s.items, item)
}

// Size returns the number of items in the set
func (s *Set[T]) Size() int {
	return len(s.items)
}

// Clear removes all items from the set
func (s *Set[T]) Clear() {
	s.items = make(map[T]struct{})
}

// Items returns a slice of all items in the set
func (s *Set[T]) Items() []T {
	result := make([]T, 0, len(s.items))
	for item := range s.items {
		result = append(result, item)
	}
	return result
}
