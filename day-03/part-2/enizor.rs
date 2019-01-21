use std::env::args;
use std::num;
use std::str::FromStr;

fn main() {
    println!("{}", run(&args().nth(1).expect("Please provide an input")))
}

#[derive(PartialEq)]
struct Claim {
    x: usize,
    lx: usize,
    y: usize,
    ly: usize,
    id: usize,
}

impl Claim {
    fn overlap(&self, c: &Claim) -> bool {
        let mut res =
            (self.x >= c.x && self.x < c.x + c.lx) || (c.x >= self.x && c.x <= self.x + self.lx);
        res = res
            && ((self.y >= c.y && self.y < c.y + c.ly)
                || (c.y >= self.y && c.y < self.y + self.ly));
        res
    }
}

impl FromStr for Claim {
    type Err = num::ParseIntError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        // I should not use unwrap but a custom Error type
        // Maybe one day...
        let at = s.find('@').unwrap();
        let id = s[1..at - 1].parse()?;
        let comma = s.find(',').unwrap();
        let x = s[at + 2..comma].parse()?;
        let colon = s.find(':').unwrap();
        let y = s[comma + 1..colon].parse()?;
        let times = s.find('x').unwrap();
        let lx = s[colon + 2..times].parse()?;
        let ly = s[times + 1..].parse()?;
        Ok(Claim { id, x, lx, y, ly })
    }
}

fn run(input: &str) -> usize {
    let claims: Vec<Claim> = input
        .lines()
        .map(|s| s.parse().expect("Wrong input"))
        .collect();
    for c1 in claims.iter() {
        let mut res = true;
        for c2 in claims.iter() {
            if c1 != c2 && c1.overlap(c2) {
                res = false;
                break;
            }
        }
        if res {
            return c1.id;
        }
    }
    0
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("#1 @ 1,3: 4x4\n#2 @ 3,1: 4x4\n#3 @ 5,5: 2x2"), 3)
    }
}
