use std::env::args;

fn main() {
    println!("{}", run(&args().nth(1).expect("Please provide an input")))
}

#[derive(Copy, Clone)]
enum Found {
    Never,
    Once,
    Twice,
}

impl Found {
    fn next(&mut self) -> bool {
        match self {
            Found::Never => {
                *self = Found::Once;
                false
            }
            Found::Once => {
                *self = Found::Twice;
                true
            }
            Found::Twice => {
                *self = Found::Twice;
                false
            }
        }
    }
}

fn run(input: &str) -> usize {
    let mut fabric: Vec<Vec<Found>> = vec![vec![Found::Never; 1000]; 1000];
    let mut res = 0;
    for line in input.lines() {
        let mut words = line.split_whitespace();
        let mut corner = words.nth(2).unwrap().trim_end_matches(":").split(",");
        let x: usize = corner.next().unwrap().parse().expect("Wrong entry");
        let y: usize = corner.next().unwrap().parse().expect("Wrong entry");
        let mut size = words.next().unwrap().split("x");
        let lx: usize = size.next().unwrap().parse().expect("Wrong entry");
        let ly: usize = size.next().unwrap().parse().expect("Wrong entry");
        for i in x..x + lx {
            for j in y..y + ly {
                if fabric[i][j].next() {
                    res += 1;
                }
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
        assert_eq!(run("#1 @ 1,3: 4x4\n#2 @ 3,1: 4x4\n#3 @ 5,5: 2x2"), 4)
    }
}
