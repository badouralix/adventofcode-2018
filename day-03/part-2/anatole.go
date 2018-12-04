package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"regexp"
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

func run(s []string) int {
	claims := parseInputs(s)
	fabric := map[int]map[int]int{}
	overlap := map[int]bool{}

	for _, c := range claims {
		addClaim(c, fabric, overlap)
	}

	return claimNotInMap(claims, overlap)
}

func claimNotInMap(claims []claim, m map[int]bool) int {
	for _, c := range claims {
		if _, ok := m[c.id]; !ok {
			return c.id
		}
	}
	panic("all claims are overlapping :(")
}

func addClaim(c claim, fabric map[int]map[int]int, overlap map[int]bool) {
	for i := 0; i < c.width; i++ {
		for j := 0; j < c.height; j++ {
			exists, prevID := addToMap(c.id, c.x+i, c.y+j, fabric)
			if exists {
				overlap[prevID] = true
				overlap[c.id] = true
			}
		}
	}
}

func addToMap(id, x, y int, m map[int]map[int]int) (exists bool, prevID int) {
	if _, ok := m[x]; ok {
		if v, ok := m[x][y]; ok {
			return true, v
		}
		m[x][y] = id
	} else {
		m[x] = map[int]int{y: id}
	}
	return false, -1
}

func parseInputs(input []string) []claim {
	re := regexp.MustCompile("#(\\d*) @ (\\d*),(\\d*): (\\d*)x(\\d*)")
	claims := []claim{}
	for _, line := range input {
		groups := re.FindStringSubmatch(line)
		c := claim{}
		c.id, _ = strconv.Atoi(groups[1])
		c.x, _ = strconv.Atoi(groups[2])
		c.y, _ = strconv.Atoi(groups[3])
		c.width, _ = strconv.Atoi(groups[4])
		c.height, _ = strconv.Atoi(groups[5])
		claims = append(claims, c)
	}
	return claims
}

func main() {
	b, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	s := strings.Split(string(b), "\n")
	fmt.Println(run(s))
}
