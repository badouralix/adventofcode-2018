package main

import (
	"fmt"
	"io/ioutil"
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
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	fmt.Println(run(string(input)))
}
