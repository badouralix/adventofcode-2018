package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
	"time"
)

func run(s string) interface{} {
	split := strings.Split(s, " ")

	tree := make([]int, len(split))
	for i := 0; i < len(split); i++ {
		tree[i], _ = strconv.Atoi(split[i])
	}

	_, result := rec(0, tree)
	return result
}

func rec(idx int, tree []int) (int, int) {
	nNode := tree[idx]
	nMeta := tree[idx+1]
	idx += 2

	value := 0

	if nNode == 0 {
		for n := 0; n < nMeta; n++ {
			value += tree[idx+n]
		}
		return idx + nMeta, value
	}

	children := make([]int, nNode)

	for n := 0; n < nNode; n++ {
		idx, children[n] = rec(idx, tree)
	}

	for n := 0; n < nMeta; n++ {
		if tree[idx+n]-1 < nNode {
			value += children[tree[idx+n]-1]
		}
	}

	return idx + nMeta, value
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
