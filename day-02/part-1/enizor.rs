use std::collections::HashMap;
use std::env::args;

fn main() {
    println!("{}", run(&args().nth(1).expect("Please provide an input")))
}

fn run(input: &str) -> usize {
    let mut freqs = HashMap::new();
    let mut twos = 0;
    let mut threes = 0;
    for line in input.lines() {
        for c in line.chars() {
            let counter = freqs.entry(c).or_insert(0);
            *counter += 1;
        }
        if freqs.values().any(|&x| x == 2) {
            twos += 1;
        }
        if freqs.values().any(|&x| x == 3) {
            threes += 1;
        }
        freqs.clear();
    }
    twos * threes
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        let input = "abcdef\nbababc\nabbcde\naabcdd\nabcccd\nabcdee\nababab";
        assert_eq!(run(input), 12);
    }

}
