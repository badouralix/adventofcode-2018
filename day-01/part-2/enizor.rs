use std::collections::HashSet;
use std::env::args;

fn main() {
    println!("{}", run(&args().nth(1).expect("Please provide an input")))
}

fn run(input: &str) -> isize {
    let v: Vec<isize> = input
        .lines()
        .map(|l| l.parse().unwrap_or_else(|_| 0))
        .collect();
    let n: usize = v.len();
    let mut frequencies = HashSet::new();
    let mut sum2 = 0;
    let mut i = 0;
    while !frequencies.contains(&sum2) {
        frequencies.insert(sum2);
        sum2 += v[i];
        i = (i + 1) % n;
    }
    sum2
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("1\n-2\n3\n1"), 2);
        assert_eq!(run("1\n-1"), 0);
        assert_eq!(run("3\n3\n4\n-2\n-4"), 10);
        assert_eq!(run("-6\n3\n8\n5\n-6"), 5);
        assert_eq!(run("7\n7\n-2\n-7\n-4"), 14);
    }
}
