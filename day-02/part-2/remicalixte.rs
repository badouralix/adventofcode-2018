use std::env::args;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")))
}

fn run(input: String) -> String {
    // Your code goes here
    let lines: Vec<&str> = input.lines().collect();
    let mut res =   String::new();
    for i in 0..lines.len() {
        for j in 0..i {
            let mut diff = 0;
            let mut diff_index = 0;
            let mut iter = lines[i].bytes().zip(lines[j].bytes()).enumerate();
            loop {
                match iter.next() {
                    Some((k, (b1, b2))) => {
                        if  b1 != b2 {
                            diff += 1;
                            diff_index = k;    
                        }
                        if diff > 1 {
                            break;
                        }
                    },
                    None => break
                }
            }
            if diff == 1 {
                res = lines[i].to_string();
                res.remove(diff_index);
            }


        }
    }
    res
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("abc\nadc\n".to_string()), "ac".to_string())
    }
}
