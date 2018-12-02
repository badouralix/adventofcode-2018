use std::env::args;
use std::collections::HashMap;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")))
}

fn run(input: String) -> String {
    // Your code goes here
    let (mut two, mut three) = (0, 0);
    for line in input.lines() {
        let mut chars = HashMap::new();
        for c in line.bytes() {
            *chars.entry(c).or_insert(0) += 1;
        }
        let (mut found_two, mut found_three) = (false, false);
        for v in chars.values() {
            if *v == 2 {
                found_two = true;
            }
            if *v == 3 {
                found_three = true;
            }
        }
        if found_three {
            three += 1;
        }
        if found_two {
            two += 1;
        }
    }
    (two*three).to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("abcdef\nbababc\nabbcde\nabcccd\naabcdd\nabcdee\nababab\n".to_string()), "12".to_string())
    }
}
