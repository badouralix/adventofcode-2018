package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func tooFar(s, t []rune) bool {
	flag := false

	for i, l := range s {
		if t[i] != l {
			if flag {
				return true
			} else {
				flag = true
			}
		}
	}

	return false
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
			if !tooFar([]rune(s), []rune(t)) {
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
