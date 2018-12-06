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
    let input = react_string(input);
    let mut min = input.len();
    for c in 65..91 {
        let new_min = react_string_ignore(&input, c);
        if new_min < min {
            min = new_min;
        }
    }
    min.to_string()
}


fn react_string(s: String) -> String {
    let mut v: Vec<u8> = Vec::new();
    for c2 in s.bytes() {
        if react(v.last(), &c2) {
            v.pop();
        } else {
            v.push(c2);
        }
    }
    String::from_utf8(v).unwrap()

}

fn react_string_ignore(s: &String, i: u8) -> usize {
    let mut v: Vec<u8> = Vec::new();
    for c2 in s.bytes() {
        if c2 == i || c2 + 32 == i || c2 - 32 == i {
            continue;
        }
        if react(v.last(), &c2) {
            v.pop();
        } else {
            v.push(c2);
        }
    }
    v.len()

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
        assert_eq!(run("dabAcCaCBAcCcaDA".to_string()), "4".to_string())
    }
}
