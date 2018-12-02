package main

import (
	"strings"
	"fmt"
	"io/ioutil"
	"os"
)

func hamming(s, t []rune) int {
	dist := 0

	for i, l := range s {
		if t[i] != l {
			dist++
		}
	}

	return dist
}

func merge(s, t []rune) []rune {
	var result []rune

	for i, l := range s {
		if t[i] == l {
			result = append(result, l)
		}
	}

	return result
}

func run(s string) string {
	ids := strings.Split(s, "\n")

	for i, s := range ids {
		for _, t := range ids[i+1:] {
			if hamming([]rune(s), []rune(t)) == 1 {
				return string(merge([]rune(s), []rune(t)))
			}
		}
	}

	return ""
}

func main() {
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	fmt.Println(run(string(input)))
}
