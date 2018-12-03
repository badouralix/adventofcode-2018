package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func run(boxes []string) string {
	// map[box ID with one missing letter][position of missing letter]
	variations := map[string]map[int]bool{}

	for _, box := range boxes {
		for pos, _ := range box {
			variation := box[0:pos] + box[pos+1:]
			if _, variationExists := variations[variation]; variationExists {
				if _, posExists := variations[variation][pos]; posExists {
					return variation
				} else {
					variations[variation][pos] = true
				}
			} else {
				variations[variation] = map[int]bool{pos: true}
			}
		}
	}
	panic("No match found")
}

func main() {
	b, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		panic(err)
	}
	s := strings.Split(string(b), "\n")
	fmt.Println(run(s))
}
