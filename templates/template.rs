use std::env::args;
use std::time::Instant;

fn main() {
    let now = Instant::now();
    let output: String = run(args().nth(1).expect("Please provide an input"));
    let elapsed = now.elapsed();
    println!(
        "_duration:{}.{}",
        elapsed.as_secs() * 1000 + u64::from(elapsed.subsec_millis()),
        elapsed.subsec_micros() - (elapsed.subsec_millis() * 1000)
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
