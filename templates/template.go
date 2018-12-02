package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func run(s string) string {
	// Your code goes here
}

func main() {
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	fmt.Println(run(string(input)))
}
