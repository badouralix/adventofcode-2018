use std::env::args;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")))
}

fn run(input: String) -> String {
    // Your code goes here
    let lines: Vec<&str> = input.lines().collect();
    for i in 0..lines.len() {
        for j in 0..i {

            let (mut byte1, mut byte2) = (lines[i].as_bytes(), lines[j].as_bytes());
            let mut diff = false;
            let mut diff_index = 0;

            loop {
                if  !diff && byte1[diff_index] != byte2[diff_index] {
                    diff = byte1[(diff_index+1)..] == byte2[(diff_index+1)..];
                    break;
                }
                diff_index += 1;
            }

            if diff {
                let mut res = lines[i].to_string();
                res.remove(diff_index);
                return res;
            }
        }
    }
    String::new()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("abc\nadc\n".to_string()), "ac".to_string())
    }
}
