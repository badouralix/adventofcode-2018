use std::env::args;

fn main() {
    println!("{}", run(&args().nth(1).expect("Please provide an input")));
}

fn run(input: &str) -> isize {
    input
        .split_whitespace()
        .map(|l| l.parse().unwrap_or(0))
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("1\n-2\n3\n1"), 3);
        assert_eq!(run("1\n-1"), 0);
        assert_eq!(run("3\n3\n4\n-2\n-4"), 4);
        assert_eq!(run("-6\n3\n8\n5\n-6"), 4);
        assert_eq!(run("7\n7\n-2\n-7\n-4"), 1);
    }
}
