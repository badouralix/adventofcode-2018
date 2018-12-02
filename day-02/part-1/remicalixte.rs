use std::env::args;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")))
}

fn run(input: String) -> String {
    // Your code goes here
    let (mut two, mut three) = (0, 0);
    let mut chars = [0u8; 26];
    for line in input.lines() {
        for i in 0..26 {
            chars[i] = 0;
        }
        let (mut found_two, mut found_three) = (0, 0);
        for c in line.bytes() {
            let previous_count = chars[(c - 97) as usize];
            match previous_count {
                1 => found_two += 1,
                2 => {
                    found_two -= 1;
                    found_three += 1;
                },
                3 => found_three -= 1,
                _ => (),
            }
            chars[(c - 97) as usize] += 1;
        }
        if found_two != 0 {
            two += 1;
        }
        if found_three != 0 {
            three += 1;
        }
    }
    (two*three).to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("abcdef\nbababc\nabbcde\nabcccd\naabcdd\nabcdee\nababab\n".to_string()), "12".to_string())
    }
}
