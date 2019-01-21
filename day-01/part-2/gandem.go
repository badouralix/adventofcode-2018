package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"time"
)

func run() int {
	var sum int
	scanner := bufio.NewScanner(os.Stdin)
	set := make(map[int]bool)
	set[0] = true
	s := make([]int, 0, 10000)

	for scanner.Scan() {
		i, _ := strconv.Atoi(scanner.Text())
		s = append(s, i)
		sum += i
		if _, ok := set[sum]; !ok {
			set[sum] = true
		} else {
			return sum
		}
	}

	var j int
	n := len(s)
	for {
		sum += s[j%n]
		if _, ok := set[sum]; !ok {
			set[sum] = true
		} else {
			return sum
		}
		j++
	}
}

func main() {
	start := time.Now()

	res := run()
	fmt.Printf("_duration:%f\n", time.Now().Sub(start).Seconds()*1000)
	fmt.Println(res)
}
