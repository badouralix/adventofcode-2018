package main

import (
	"strconv"
	"strings"
	"fmt"
	"io/ioutil"
	"os"
)

func run(s string) string {
	nTwo := 0
	nThree := 0

	for _, id := range strings.Split(s, "\n") {
		letterCount := make(map[rune]int)
		foundTwo := false
		foundThree := false

		for _, letter := range id {
			letterCount[letter]++
		}

		for _, count := range letterCount {
			if count == 2 && ! foundTwo {
				nTwo++
				foundTwo = true
			} else if count == 3 && ! foundThree {
				nThree++
				foundThree = true
			}

			if foundTwo && foundThree {
				break
			}
		}
	}

	return strconv.Itoa(nTwo * nThree)
}

func main() {
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	fmt.Println(run(string(input)))
}
