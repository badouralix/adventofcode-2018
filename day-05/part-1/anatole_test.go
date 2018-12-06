package main

import (
	"strconv"
	"testing"
)

func TestAreOpposite(t *testing.T) {
	tc := []struct {
		r1, r2 rune
		exp    bool
	}{
		{'a', 'A', true},
		{'a', 'b', false},
		{'a', 'a', false},
		{'a', 'B', false},
	}

	for i, c := range tc {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			if areOpposite(c.r1, c.r2) != c.exp {
				t.Fatal()
			}
		})
	}
}

func TestReduce(t *testing.T) {
	if reduce("dabAcCaCBAcCcaDA") != 10 {
		t.Fatal()
	}
}
