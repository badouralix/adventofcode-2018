package main

import (
	"errors"
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

type (
	node struct {
		value byte
		next  *node
	}

	stack struct {
		top  *node
		size int
	}
)

func (this stack) Len() int {
	return this.size
}

func (this stack) Peek() (byte, error) {
	if this.size == 0 {
		return '\x00', errors.New("Cannot peek, stack is empty")
	}

	return this.top.value, nil
}

func (this *stack) Pop() (stack, error) {
	if this.size == 0 {
		return stack{}, errors.New("Cannot pop, stack is empty")
	}

	return stack{this.top.next, this.size - 1}, nil
}

func (this *stack) Push(c byte) stack {
	n := node{c, this.top}
	return stack{&n, this.size + 1}
}

func collapse(s string) int {
	st := stack{nil, 0}

	for i := 0; i < len(s); i++ {
		c, err := st.Peek()

		if err != nil {
			st = st.Push(s[i])
			continue
		}

		if strings.ToLower(string(s[i])) != strings.ToLower(string(c)) || s[i] == c {
			st = st.Push(s[i])
			continue
		}

		st, _ = st.Pop()
	}

	return st.Len()
}

func run(s string) int {
	result := 0

	for _, c := range "qwertyuiopasdfghjklzxcvbnm" {
		size := collapse(strings.Replace(strings.Replace(s, string(c), "", -1), strings.ToUpper(string(c)), "", -1))
		if result > size || result == 0 {
			result = size
		}
	}

	return result
}

func main() {
	input, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	fmt.Println(run(string(input)))
}
