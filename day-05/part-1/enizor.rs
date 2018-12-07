use std::env::args;
use std::time::Instant;

fn main() {
    let now = Instant::now();
    let output: usize = run(&args().nth(1).expect("Please provide an input"));
    let elapsed = now.elapsed();
    println!(
        "_duration:{}.{}",
        elapsed.as_secs() * 1000 + u64::from(elapsed.subsec_millis()),
        elapsed.subsec_micros() - (elapsed.subsec_millis() * 1000)
    );
    println!("{}", output);
}

fn run(input: &str) -> usize {
    let mut stack: Vec<u8> = vec![];
    let mut len = 0;
    for &byte in input.as_bytes() {
        if len > 0 && (i16::from(stack[len - 1]) - i16::from(byte)).abs() == 32 {
            stack.pop();
            len -= 1;
        } else {
            stack.push(byte);
            len += 1;
        }
    }
    len
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("dabAcCaCBAcCcaDA"), 10);
    }
}
