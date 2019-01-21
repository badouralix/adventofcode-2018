// +build go1.11

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"time"
)

func main() {
	start := time.Now()

	sum := 0
	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		i, _ := strconv.Atoi(scanner.Text())
		sum += i
	}
	fmt.Printf("_duration:%f\n", time.Now().Sub(start).Seconds()*1000)
	fmt.Println(sum)
}
