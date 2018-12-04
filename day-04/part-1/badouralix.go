package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"sort"
	"strconv"
	"strings"
)

func run(s string) int {
	var sleepmaxminute int
	var sleepmaxguard int
	var sleepstart int
	var sleepend int
	var sleepmax int
	var guard int

	sleep := make(map[int][]int)
	sleeptotal := make(map[int]int)

	input := strings.Split(s, "\n")
	sort.Strings(input)

	for _, line := range input {
		switch {
		case strings.Contains(line, "sleep"):
			sleepstart, _ = strconv.Atoi(strings.Split(strings.Split(line, ":")[1], "]")[0])

		case strings.Contains(line, "wake"):
			sleepend, _ = strconv.Atoi(strings.Split(strings.Split(line, ":")[1], "]")[0])
			sleeptotal[guard] += (sleepend - sleepstart)

			if sleeptotal[guard] > sleepmax {
				sleepmax = sleeptotal[guard]
				sleepmaxguard = guard
			}

			for m := sleepstart; m < sleepend; m++ {
				sleep[guard][m]++
			}

		default:
			guard, _ = strconv.Atoi(strings.Split(strings.Split(line, "#")[1], " ")[0])
			if _, ok := sleep[guard]; !ok {
				sleep[guard] = make([]int, 60)
			}
			if _, ok := sleeptotal[guard]; !ok {
				sleeptotal[guard] = 0
			}
		}
	}

	for m := 0; m < 60; m++ {
		if sleep[sleepmaxguard][m] > sleep[sleepmaxguard][sleepmaxminute] {
			sleepmaxminute = m
		}
	}

	return sleepmaxguard * sleepmaxminute
}

func main() {
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	fmt.Println(run(string(input)))
}
