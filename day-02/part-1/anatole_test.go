package main

import "testing"

var cases = map[string]struct{ twos, threes bool }{
	"abcdef": {false, false},
	"bababc": {true, true},
	"abbcde": {true, false},
	"abcccd": {false, true},
	"aabcdd": {true, false},
	"abcdee": {true, false},
	"ababab": {false, true},
}

func TestCountInWord(t *testing.T) {
	for input, expected := range cases {
		t.Run(input, func(t *testing.T) {
			twos, threes := countInWord(input)
			if (twos != expected.twos) || (threes != expected.threes) {
				t.Fatal()
			}
		})
	}
}

func TestChecksum(t *testing.T) {
	strings := []string{}
	for w := range cases {
		strings = append(strings, w)
	}
	res := checksum(strings)
	if res != 12 {
		t.Fatal()
	}
}
