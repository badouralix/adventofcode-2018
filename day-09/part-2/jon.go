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

func run(s string) interface{} {
	words := strings.Split(s, " ")
	nbPlayers, _ := strconv.Atoi(words[0])
	nbMarbles, _ := strconv.Atoi(words[6])
	nbMarbles *= 100

	curr := &node{0, nil, nil}
	curr.prev = curr
	curr.next = curr

	scores := make([]int, nbPlayers)

	for turn := 1; turn <= nbMarbles; turn++ {
		/* printList(curr)
		if turn == 26 {
			break
		} //*/

		if turn%23 == 0 {
			player := turn % nbPlayers
			curr = curr.prev.prev.prev.prev.prev.prev.prev
			scores[player] += turn + curr.value
			curr.prev.next = curr.next
			curr = curr.next
		} else {
			new := &node{turn, curr.next, curr.next.next}
			curr.next.next.prev = new
			curr.next.next = new
			curr = new
		}
	}

	max := 0
	for _, v := range scores {
		if v > max {
			max = v
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

func printList(curr *node) {
	printNode(curr)
	c := curr.next
	for c != curr {
		fmt.Print(", ")
		printNode(c)
		c = c.next
	}
	fmt.Println()
}

func printNode(c *node) {
	fmt.Printf("%d (%d, %d)", c.value, c.prev.value, c.next.value)
}
