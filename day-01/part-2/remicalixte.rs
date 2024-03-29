use std::env::args;
use std::collections::HashSet;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")))
}

fn run(input: String) -> String {
    // Your code goes here
    let mut freq: i32 = 0;
    let mut past_freqs = HashSet::new();
    past_freqs.insert(freq);
    let changes: Vec<i32> = input.lines().map(|s| s.parse().unwrap()).collect();
    loop {
        for change in changes.iter() {
            freq += change;
            if past_freqs.contains(&freq) {
                return freq.to_string()
            }
            past_freqs.insert(freq);            

        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("+1\n-1\n".to_string()), "0".to_string())
    }
}
