package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
	"time"
)

const (
	limit = 10000
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

func rollUp(l []int) []int {
	res := make([]int, len(l))
	s := 0
	for i, v := range l {
		s += v
		res[i] = s
	}
	return res
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
	for i := 0; i < n; i++ {
		px[i] -= xMin
		py[i] -= yMin
	}
	xMin, xMax = 0, xMax-xMin
	yMin, yMax = 0, yMax-yMin

	pointsByX := make([]int, xMax+1)
	pointsByY := make([]int, yMax+1)

	for i := 0; i < n; i++ {
		pointsByX[px[i]]++
		pointsByY[py[i]]++
	}

	pointsUnderX := rollUp(pointsByX)
	pointsUnderY := rollUp(pointsByY)

	area := 0
	dBase := 0
	for i := 0; i < n; i++ {
		dBase += px[i] + py[i]
	}

	for x := xMin; x <= xMax; x++ {
		if x > xMin {
			dBase += 2*pointsUnderX[x-1] - n
		}
		d := dBase
		for y := yMin; y <= yMax; y++ {
			if y > yMin {
				d += 2*pointsUnderY[y-1] - n
			}
			if d < limit {
				area++
			}
		}
	}

	return area
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
