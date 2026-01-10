package util

import "fmt"

// Queue is a generic FIFO queue implementation using a slice
type Queue[T any] struct {
	items []T
	head  int
}

// NewQueue creates a new empty queue
func NewQueue[T any]() *Queue[T] {
	return &Queue[T]{items: make([]T, 0), head: 0}
}

// Enqueue adds an item to the back of the queue
func (q *Queue[T]) Enqueue(item T) {
	q.items = append(q.items, item)
}

// Dequeue removes and returns the front item from the queue
// Returns the zero value if the queue is empty
func (q *Queue[T]) Dequeue() T {
	if q.IsEmpty() {
		var zero T
		return zero
	}
	item := q.items[q.head]
	q.head++

	// Reset when queue is empty or head gets too large
	if q.head > len(q.items)/2 && q.head > 100 {
		q.items = q.items[q.head:]
		q.head = 0
	}

	return item
}

// Peek returns the front item without removing it
// Returns the zero value if the queue is empty
func (q *Queue[T]) Peek() T {
	if q.IsEmpty() {
		var zero T
		return zero
	}
	return q.items[q.head]
}

// IsEmpty returns true if the queue has no items
func (q *Queue[T]) IsEmpty() bool {
	return q.head >= len(q.items)
}

// Size returns the number of items in the queue
func (q *Queue[T]) Size() int {
	return len(q.items)
}

// Print prints the queue contents from front to back
func (q *Queue[T]) Print() {
	fmt.Print("[")
	for i, item := range q.items {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(item)
	}
	fmt.Println("]")
}
