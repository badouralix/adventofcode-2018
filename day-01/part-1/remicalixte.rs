use std::env::args;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")).unwrap())
}

fn run(input: String) -> Result<i32, std::num::ParseIntError> {
    // Your code goes here
    input.lines().map(|s| s.parse::<i32>()).sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("+1\n-1".to_string()).unwrap(), 0)
    }
}
