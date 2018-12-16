package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
	"time"
)

func run() string {
	var i, k int
	j := 1
	b, _ := ioutil.ReadAll(os.Stdin)
	list := strings.Split(string(b), "\n")
	var common string
	var different int
	n := len(list[0])
	l := len(list)

	for i < l {
		for j < l {
			for k < n {
				if different > 1 {
					goto NEXT
				} else if list[i][k]-list[j][k] > 0 {
					different++
				} else {
					common += string(list[i][k])
				}
				k++
			}
			if different <= 1 {
				return common
			}
		NEXT:
			k = 0
			common = ""
			different = 0
			j++
		}
		i++
		j = i + 1
	}
	return ""
}

func main() {
	start := time.Now()
	res := run()
	fmt.Printf("_duration:%f\n", time.Now().Sub(start).Seconds()*1000)
	fmt.Println(res)
}
