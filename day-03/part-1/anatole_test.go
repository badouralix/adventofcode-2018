package main

import (
	"reflect"
	"strconv"
	"testing"
)

func TestParseInputs(t *testing.T) {
	in := []string{
		"#1 @ 432,394: 29x14",
		"#2 @ 57,42: 12x16",
		"#3 @ 138,913: 22x20",
	}

	expected := []claim{
		{432, 394, 29, 14},
		{57, 42, 12, 16},
		{138, 913, 22, 20},
	}

	res := parseInputs(in)

	if !reflect.DeepEqual(res, expected) {
		t.Fatal()
	}
}

func TestAddToMap(t *testing.T) {
	cases := []struct {
		x, y   int
		m      map[int]map[int]bool
		exists bool
	}{
		{2, 3, map[int]map[int]bool{}, false},
		{2, 3, map[int]map[int]bool{2: map[int]bool{3: true}}, true},
	}

	for i, tc := range cases {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			if tc.exists != addToMap(tc.x, tc.y, tc.m) {
				t.Fatal()
			}
		})
	}
}

func TestLen2(t *testing.T) {
	cases := []struct {
		m   map[int]map[int]bool
		res int
	}{
		{map[int]map[int]bool{}, 0},
		{map[int]map[int]bool{1: map[int]bool{3: true, 4: true, 5: true, 6: true}, 2: map[int]bool{3: true, 4: true, 5: true, 6: true}}, 8},
	}

	for i, tc := range cases {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			if tc.res != len2(tc.m) {
				t.Fatal()
			}
		})
	}
}

func TestRun(t *testing.T) {
	in := []string{
		"#1 @ 1,3: 4x4",
		"#2 @ 3,1: 4x4",
		"#3 @ 5,5: 2x2",
	}

	if run(in) != 4 {
		t.Fatal()
	}
}
