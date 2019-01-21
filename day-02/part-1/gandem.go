package main

import (
	"bufio"
	"fmt"
	"os"
	"time"
)

func run() int {
	var i int
	scanner := bufio.NewScanner(os.Stdin)
	var set [26]int
	var numThrees int
	var numTwos int
	var exTwo bool
	var exThree bool

	for scanner.Scan() {
		s := scanner.Text()

		for i < len(s) {
			set[s[i]-'a']++
			i++
		}
		i = 0

		for i < 26 {
			if set[i] == 2 && !exTwo {
				exTwo = true
			}
			if set[i] == 3 && !exThree {
				exThree = true
			}
			set[i] = 0
			i++
		}
		i = 0

		if exTwo {
			numTwos++
		}
		if exThree {
			numThrees++
		}
		exTwo = false
		exThree = false
	}

	return numTwos * numThrees
}

func main() {
	start := time.Now()

	res := run()
	fmt.Printf("_duration:%f\n", time.Now().Sub(start).Seconds()*1000)
	fmt.Println(res)
}
