use std::env::args;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")))
}

fn run(input: String) -> i32 {
    // Your code goes here
    input.lines().map(|s| s.parse::<i32>().unwrap()).fold(0, |acc, x| acc + x)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("+1\n-1".to_string()), 0)
    }
}
