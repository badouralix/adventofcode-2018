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
	value int
	prev  *node
	next  *node
}

func newnode(value int) *node {
	n := node{value, nil, nil}
	n.prev = &n
	n.next = &n
	return &n
}

func (this *node) insert(value int) *node {
	n := node{value, this, this.next}
	this.next.prev = &n
	this.next = &n
	return &n
}

func (this *node) delete() *node {
	this.prev.next = this.next
	this.next.prev = this.prev
	return this.next
}

func run(s string) interface{} {
	split := strings.Split(s, " ")
	players, _ := strconv.Atoi(split[0])
	last, _ := strconv.Atoi(split[6])

	scores := make([]int, players)
	current := newnode(0)
	player := 1
	result := 0

	for m := 1; m <= last; m++ {
		if m%23 != 0 {
			current = current.next.insert(m)
		} else {
			culprit := current.prev.prev.prev.prev.prev.prev.prev
			scores[player] += m + culprit.value
			current = culprit.delete()

		}

		player = player + 1
		if player >= players {
			player = 0
		}
	}

	for _, score := range scores {
		if score > result {
			result = score
		}
	}

	return result
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
