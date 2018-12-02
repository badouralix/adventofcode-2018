package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func checksum(s []string) int {
	count2 := 0
	count3 := 0
	for _, w := range s {
		twos, threes := countInWord(w)
		if twos {
			count2++
		}
		if threes {
			count3++
		}
	}
	return count2 * count3
}

// returns true, false if the word contains a letter that appears twice
// and no letter that appears three times
func countInWord(w string) (twos, threes bool) {
	counter := map[rune]int{}
	for _, r := range w {
		if _, ok := counter[r]; !ok {
			counter[r] = 0
		}
		counter[r]++
	}

	for _, count := range counter {
		if count == 2 {
			twos = true
		}
		if count == 3 {
			threes = true
		}
	}
	return
}

func main() {
	b, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	s := strings.Split(string(b), "\n")
	fmt.Println(checksum(s))
}
