package util

import "fmt"

// Stack is a generic stack implementation using a slice
type Stack[T any] struct {
	items []T
}

// NewStack creates a new empty stack
func NewStack[T any]() *Stack[T] {
	return &Stack[T]{items: make([]T, 0)}
}

// Push adds an item to the top of the stack
func (s *Stack[T]) Push(item T) {
	s.items = append(s.items, item)
}

// PushN adds multiple items to the top of the stack
// Items are pushed in order (first item goes on first, last item on top)
func (s *Stack[T]) PushN(items []T) {
	s.items = append(s.items, items...)
}

// Pop removes and returns the top item from the stack
// Returns the zero value if the stack is empty
func (s *Stack[T]) Pop() T {
	if s.IsEmpty() {
		var zero T
		return zero
	}
	item := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return item
}

// PopN removes and returns the top N items from the stack
// Returns items in top-to-bottom order (first item is the top)
func (s *Stack[T]) PopN(n int) []T {
	if n <= 0 {
		return []T{}
	}
	if n > len(s.items) {
		n = len(s.items)
	}

	items := make([]T, n)
	start := len(s.items) - n
	copy(items, s.items[start:])
	s.items = s.items[:start]

	// Reverse to get top-to-bottom order
	for i := 0; i < n/2; i++ {
		items[i], items[n-1-i] = items[n-1-i], items[i]
	}

	return items
}

// Peek returns the top item without removing it
// Returns the zero value if the stack is empty
func (s *Stack[T]) Peek() T {
	if s.IsEmpty() {
		var zero T
		return zero
	}
	return s.items[len(s.items)-1]
}

// IsEmpty returns true if the stack has no items
func (s *Stack[T]) IsEmpty() bool {
	return len(s.items) == 0
}

// Size returns the number of items in the stack
func (s *Stack[T]) Size() int {
	return len(s.items)
}

// Print prints the stack contents from bottom to top
func (s *Stack[byte]) Print() {
	fmt.Print("[")
	for i, item := range s.items {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(item)
	}
	fmt.Println("]")
}
