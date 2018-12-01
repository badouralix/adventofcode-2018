package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func run(s string) string {
	result := 0

	for _, i := range strings.Split(s, "\n") {
		j, err := strconv.Atoi(i)
		if err != nil {
			panic(err)
		}

		result += j
	}

	return strconv.Itoa(result)
}

func main() {
	fmt.Println(run(os.Args[1]))
}
