package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"

	"github.com/golang-collections/collections/stack"
)

func reduceAll(in string) int {
	shortest := len(in)
	for excluded := 65; excluded <= 90; excluded++ {
		l := reduce(in, excluded)
		if l <= shortest {
			shortest = l
		}
	}
	return shortest
}

func reduce(in string, excluded int) int {
	s := stack.New()

	for _, r := range in {
		if (int(r) == excluded) || (int(r) == excluded+32) {
			continue
		} else if (s.Len() == 0) || !areOpposite(s.Peek().(rune), r) {
			s.Push(r)
		} else {
			s.Pop()
		}
	}

	return s.Len()
}

func areOpposite(r1, r2 rune) bool {
	return (r1 == r2+32) || (r2 == r1+32)
}

func main() {
	b, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	in := strings.Split(string(b), "\n")[0]
	fmt.Println(reduceAll(in))
}
