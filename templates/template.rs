use std::env::args;
use std::time::Instant;

fn main() {
    let now = Instant::now();
    let output: String = run(args().nth(1).expect("Please provide an input"));
    let elapsed = now.elapsed();
    println!(
        "_duration:{}.{}",
        elapsed.as_secs(),
        elapsed.subsec_millis()
    );
    println!("{}", output);
}

fn run(input: String) -> String {
    // Your code goes here
    input
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("Test example".to_string()), "Test example".to_string())
    }
}
