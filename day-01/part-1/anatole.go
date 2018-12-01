package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func run() int {
	res := 0
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		num, err := strconv.Atoi(scanner.Text())
		if err != nil {
			panic(err)
		}
		res += num
	}
	if err := scanner.Err(); err != nil {
		log.Println(err)
	}
	return res
}

func main() {
	fmt.Println(run())
}
