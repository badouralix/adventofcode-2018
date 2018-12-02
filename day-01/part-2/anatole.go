package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
)

func run() int {
	b, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	s := strings.Split(string(b), "\n")
	n := len(s)

	res := 0
	seen := map[int]bool{0: true}
	i := 0
	for {
		num, err := strconv.Atoi(s[i])
		if err != nil {
			panic(err)
		}
		res += num
		if _, ok := seen[res]; ok {
			return res
		}
		seen[res] = true
		i = (i + 1) % n
	}
}

func main() {
	fmt.Println(run())
}
