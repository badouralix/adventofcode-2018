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

	_, result := rec(0, 0, tree)
	return result
}

func rec(idx int, acc int, tree []int) (int, int) {
	nNode := tree[idx]
	nMeta := tree[idx+1]
	idx += 2

	for n := 0; n < nNode; n++ {
		idx, acc = rec(idx, acc, tree)
	}

	for n := 0; n < nMeta; n++ {
		acc += tree[idx+n]
	}

	return idx + nMeta, acc
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
