package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type claim struct {
	id     int
	x      int
	y      int
	width  int
	height int
}

func parse() (result []claim) {
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		splitline := strings.Split(scanner.Text(), " @ ")
		id, _ := strconv.Atoi(strings.Split(splitline[0], "#")[1])
		loc := splitline[1]

		splitloc := strings.Split(loc, ": ")
		pos, dim := splitloc[0], splitloc[1]

		splitpos := strings.Split(pos, ",")
		posx, _ := strconv.Atoi(splitpos[0])
		posy, _ := strconv.Atoi(splitpos[1])

		splitdim := strings.Split(dim, "x")
		dimw, _ := strconv.Atoi(splitdim[0])
		dimh, _ := strconv.Atoi(splitdim[1])

		result = append(result, claim{id, posx, posy, dimw, dimh})
	}

	return
}

func run() string {
	results := make(map[int]struct{})
	fabric := make([]int, 1000*1000)

	input := parse()

	for _, c := range input {
		alone := true
		for i := 0; i < c.width; i++ {
			for j := 0; j < c.height; j++ {
				switch fabric[(c.x+i)+1000*(c.y+j)] {
				case 0:
					fabric[(c.x+i)+1000*(c.y+j)] = c.id
				default:
					alone = false
					delete(results, fabric[(c.x+i)+1000*(c.y+j)])
				}
			}
		}
		if alone {
			results[c.id] = struct{}{}
		}
	}

	for id := range results {
		return strconv.Itoa(id)
	}

	return ""
}

func main() {
	fmt.Println(run())
}
