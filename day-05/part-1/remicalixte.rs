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
    let mut v: Vec<u8> = Vec::with_capacity(input.len());
    for c2 in input.bytes() {
        if react(v.last(), &c2) {
            v.pop();
        } else {
            v.push(c2);
        }
    }
    v.len().to_string()
}


fn react(c1: Option<&u8>, c2: &u8) -> bool {
    match c1 {
        None => false,
        Some(c) => (c > c2 && (c - c2) == 32) || (c2 > c && (c2 - c) == 32)
    }

}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("dabAcCaCBAcCcaDA".to_string()), "10".to_string())
    }
}
