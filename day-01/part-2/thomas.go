package main

import (
	"fmt"
	"os"
	"strings"
	"bufio"
	"strconv"
)

func run(s string) string {
	res := 0
	set := map[int]bool{0: true}
	for true {
		scanner := bufio.NewScanner(strings.NewReader(s))
		for scanner.Scan() {
			val, _ := strconv.Atoi(scanner.Text())
			res = res + val
			if _, ok := set[res]; ok {
				return strconv.Itoa(res)
			}
			set[res] = true
		}
	}
	return ""
}

func main() {
	fmt.Println(run(os.Args[1]))
}
