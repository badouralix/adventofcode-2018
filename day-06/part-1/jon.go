package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
	"time"
)

func minMax(array []int) (int, int) {
	var max = array[0]
	var min = array[0]
	for _, value := range array {
		if max < value {
			max = value
		}
		if min > value {
			min = value
		}
	}
	return min, max
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func dist(x1, y1, x2, y2 int) int {
	return abs(x1-x2) + abs(y1-y2)
}

func run(s string) interface{} {

	lines := strings.Split(s, "\n")
	n := len(lines)

	if len(lines[n-1]) == 0 {
		n--
	}

	px := make([]int, n)
	py := make([]int, n)

	for i := 0; i < n; i++ {
		parts := strings.Split(lines[i], ", ")
		px[i], _ = strconv.Atoi(parts[0])
		py[i], _ = strconv.Atoi(parts[1])
	}

	xMin, xMax := minMax(px)
	yMin, yMax := minMax(py)

	areas := make([]int, n)
	isInfinite := make([]bool, n)

	for x := xMin; x <= xMax; x++ {
		for y := yMin; y <= yMax; y++ {
			closest := 0
			alone := true
			minDist := dist(px[0], py[0], x, y)

			for i := 1; i < n; i++ {
				d := dist(px[i], py[i], x, y)
				if d < minDist {
					closest = i
					alone = true
					minDist = d
				} else if d == minDist {
					alone = false
				}
			}

			if !alone {
				continue
			}

			areas[closest]++

			if x == xMin || x == xMax || y == yMin || y == yMax {
				isInfinite[closest] = true
			}
		}
	}

	maxArea := 0
	for i := 0; i < n; i++ {
		if !isInfinite[i] {
			if areas[i] > maxArea {
				maxArea = areas[i]
			}
		}
	}

	return maxArea
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
