package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"

	"github.com/golang-collections/collections/stack"
)

func reduce(in string) int {
	s := stack.New()

	for _, r := range in {
		if (s.Len() == 0) || !areOpposite(s.Peek().(rune), r) {
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
	fmt.Println(reduce(in))
}
