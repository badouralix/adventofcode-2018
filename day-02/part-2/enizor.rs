use std::env::args;

fn main() {
    println!("{}", run(&args().nth(1).expect("Please provide an input")))
}

fn run(input: &str) -> String {
    let lines: Vec<_> = input.lines().collect();
    for (index, u) in lines.iter().enumerate() {
        for v in lines.iter().skip(index + 1) {
            if is_close(u, v) {
                return commonchars(u, v);
            }
        }
    }
    "".to_owned()
}

fn is_close(u: &str, v: &str) -> bool {
    if u.is_empty() {
        false
    } else if u.chars().nth(0).unwrap() == v.chars().nth(0).unwrap() {
        is_close(&u[1..], &v[1..])
    } else {
        u[1..] == v[1..]
    }
}

fn commonchars(u: &str, v: &str) -> String {
    if u.chars().nth(0) == v.chars().nth(0) {
        let mut res = String::from(&u[0..1]);
        res.push_str(&commonchars(&u[1..], &v[1..]));
        res
    } else {
        u[1..].to_string()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(
            run("abcde\nfghij\nklmno\npqrst\nfguij\naxcye\nwvxyz"),
            "fgij".to_string()
        )
    }
}
