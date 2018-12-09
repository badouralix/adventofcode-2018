package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
	"time"
)

type node struct {
	before *node
	after  *node
	val    int
}

func run(s string) interface{} {
	// Your code goes here
	parsed := strings.Split(s, " ")
	players, _ := strconv.Atoi(parsed[0])
	last, _ := strconv.Atoi(parsed[len(parsed)-2])
	last *= 100
	fmt.Println(players, last)
	marbles := &node{val: 0}
	playerScores := make([]int, players)
	current := marbles
	for i := 0; i < last; i++ {
		marble := i + 1
		player := marble % players
		if marble == 1 {
			current.after = &node{val: 1, after: current, before: current}
			current.before = current.after
			current = current.after
			continue
		}
		if marble%23 != 0 {
			current = current.after
			current = &node{val: marble, before: current, after: current.after}
			current.before.after = current
			current.after.before = current
			continue
		}
		for i := 0; i < 7; i++ {
			current = current.before
		}
		playerScores[player] += marble + current.val
		current.after.before = current.before
		current.before.after = current.after
		current = current.after
	}
	max := 0
	for _, val := range playerScores {
		if val > max {
			max = val
		}
	}
	return max
}

func main() {
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	start := time.Now()
	res := run(string(input))
	fmt.Printf("_duration:%f\n", time.Now().Sub(start).Seconds()*1000)
	fmt.Println(res)
}
