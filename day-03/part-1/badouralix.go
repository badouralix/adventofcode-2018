package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
)

type claim struct {
	x      int
	y      int
	width  int
	height int
}

func parse(s string) (result []claim) {
	for _, line := range strings.Split(s, "\n") {
		splitline := strings.Split(strings.Split(line, "@ ")[1], ": ")
		pos, dim := splitline[0], splitline[1]

		splitpos := strings.Split(pos, ",")
		posx, _ := strconv.Atoi(splitpos[0])
		posy, _ := strconv.Atoi(splitpos[1])

		splitdim := strings.Split(dim, "x")
		dimw, _ := strconv.Atoi(splitdim[0])
		dimh, _ := strconv.Atoi(splitdim[1])

		result = append(result, claim{posx, posy, dimw, dimh})
	}

	return
}

func run(s string) string {
	fabric := make([]int, 1000*1000)
	input := parse(s)
	result := 0

	for _, c := range input {
		for i := 0; i < c.width; i++ {
			for j := 0; j < c.height; j++ {
				switch fabric[(c.x+i)+1000*(c.y+j)] {
				case 1:
					result++
					fallthrough
				case 0:
					fabric[(c.x+i)+1000*(c.y+j)]++
				}
			}
		}
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
