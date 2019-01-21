package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"runtime/debug"
	"strconv"
	"strings"
	"time"
)

const allocConst = 4000

type node struct {
	val    int
	before *node
	after  *node
}

type pool struct {
	prev  *node
	alloc []node
	i     int
}

func newPool() pool {
	return pool{
		alloc: make([]node, allocConst),
	}
}

func (p *pool) Get(val int, before, after *node) (current *node) {
	if p.prev != nil {
		current = p.prev
		p.prev = nil
	} else {
		if p.i == len(p.alloc) {
			p.alloc = make([]node, allocConst)
			p.i = 0
		}
		current = &p.alloc[p.i]
		p.i++
	}
	current.val = val
	current.before = before
	current.after = after
	before.after = current
	after.before = current
	return current
}

func (p *pool) Put(c *node) {
	p.prev = c
}

func run(s string) interface{} {
	// Your code goes here
	parsed := strings.Split(s, " ")
	players, _ := strconv.Atoi(parsed[0])
	last, _ := strconv.Atoi(parsed[len(parsed)-2])
	last *= 100
	current := &node{val: 0}
	current.after = current
	current.before = current
	playerScores := make([]int, players)
	pool := newPool()
	for marble := 1; marble <= last; marble++ {
		if marble%23 != 0 {
			current = pool.Get(marble, current.after, current.after.after)
		} else {
			current = current.before.before.before.before.before.before.before
			playerScores[marble%players] += marble + current.val
			pool.Put(current)
			current.after.before = current.before
			current.before.after = current.after
			current = current.after
		}
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
	// Uncomment this line to disable garbage collection
	debug.SetGCPercent(-1)

	// Read input from stdin
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}

	// Start resolution
	start := time.Now()
	result := run(string(input))

	// Print result
	fmt.Printf("_duration:%f\n", time.Now().Sub(start).Seconds()*1000)
	fmt.Println(result)
}
