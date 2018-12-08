package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"time"
)

func run(s string) interface{} {
	// Your code goes here
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
