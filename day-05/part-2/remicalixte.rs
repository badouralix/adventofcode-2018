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
        let s = remove_char(&input, c);
        let new_min = react_string(s).len();
        if new_min < min {
            min = new_min;
        }
    }
    min.to_string()
}


fn remove_char(s: &String, c: u8) -> String {
    let mut res = String::with_capacity(s.len());

    for c2 in s.bytes() {
        if !(c2 == c || c2 + 32 == c || c2 - 32 == c) {
            res.push(c2 as char)
        }
    }

    res
}

fn react_string(s: String) -> String {
    let mut res = String::with_capacity(s.len());
    unsafe {
        let v = res.as_mut_vec();
        for c2 in s.bytes() {
            if react(v.last(), &c2) {
                v.pop();
            } else {
                v.push(c2);
            }
        }
    }
    res

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
