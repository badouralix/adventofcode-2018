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
	x      int
	y      int
	width  int
	height int
}

func run(s []string) int {
	claims := parseInputs(s)
	fabric := map[int]map[int]bool{}
	overlap := map[int]map[int]bool{}

	for _, c := range claims {
		addClaim(c, fabric, overlap)
	}
	return len2(overlap)
}

// 2-dimensional len
func len2(m map[int]map[int]bool) int {
	res := 0
	for _, v := range m {
		res += len(v)
	}
	return res
}

func addClaim(c claim, fabric map[int]map[int]bool, overlap map[int]map[int]bool) {
	for i := 0; i < c.width; i++ {
		for j := 0; j < c.height; j++ {
			exists := addToMap(c.x+i, c.y+j, fabric)
			if exists {
				addToMap(c.x+i, c.y+j, overlap)
			}
		}
	}
}

func addToMap(x, y int, m map[int]map[int]bool) (exists bool) {
	if _, ok := m[x]; ok {
		if _, ok := m[x][y]; ok {
			return true
		} else {
			m[x][y] = true
		}
	} else {
		m[x] = map[int]bool{y: true}
	}
	return false
}

func parseInputs(input []string) []claim {
	re := regexp.MustCompile("#.* @ (\\d*),(\\d*): (\\d*)x(\\d*)")
	claims := []claim{}
	for _, line := range input {
		groups := re.FindStringSubmatch(line)
		c := claim{}
		c.x, _ = strconv.Atoi(groups[1])
		c.y, _ = strconv.Atoi(groups[2])
		c.width, _ = strconv.Atoi(groups[3])
		c.height, _ = strconv.Atoi(groups[4])
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
