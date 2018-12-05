package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func run(s string) int {
	i := 0

	for {
		if strings.ToLower(string(s[i])) == strings.ToLower(string(s[i+1])) && s[i] != s[i+1] {
			s = s[:i] + s[i+2:]
			if i = i - 1; i < 0 {
				i = 0
			}
		} else {
			i++
		}

		if i == len(s)-1 {
			break
		}
	}

	return len(s)
}

func main() {
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	fmt.Println(run(string(input)))
}
