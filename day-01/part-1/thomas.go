package main

import (
	"fmt"
	"os"
	"strings"
	"bufio"
	"strconv"
)

func run(s string) string {
	scanner := bufio.NewScanner(strings.NewReader(s))
	res := 0
	for scanner.Scan() {
		val, _ := strconv.Atoi(scanner.Text())
		res = res + val
	}
	return strconv.Itoa(res)
}

func main() {
	fmt.Println(run(os.Args[1]))
}
