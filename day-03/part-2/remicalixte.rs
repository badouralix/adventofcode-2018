use std::cmp::{max, min};
use std::collections::{HashMap, HashSet};
use std::env::args;
use std::ptr;

fn main() {
    println!("{}", run(args().nth(1).expect("Please provide an input")))
}

#[derive(Default, Debug)]
struct Rect {
    id: i32,
    x: i32,
    y: i32,
    w: i32,
    h: i32,
}

impl Rect {
    fn from_string(s: &str) -> Result<Rect, Box<std::error::Error>> {
        let i1 = s.find("@").ok_or("fail")?;
        let i2 = s.find(",").ok_or("fail")?;
        let i3 = s.find(":").ok_or("fail")?;
        let i4 = s.find("x").ok_or("fail")?;
        Ok(Rect {
            id: s[1..(i1 - 1)].parse()?,
            x: s[(i1 + 2)..i2].parse()?,
            y: s[(i2 + 1)..i3].parse()?,
            w: s[(i3 + 2)..i4].parse()?,
            h: s[(i4 + 1)..].parse()?,
        })
    }

    fn interset(&self, other: &Rect) -> bool {
        let x = max(self.x, other.x);
        let y = max(self.y, other.y);
        let w = min(self.x + self.w - x, other.x + other.w - x);
        let h = min(self.y + self.h - y, other.y + other.h - y);
        w > 0 && h > 0
    }
}

fn run(input: String) -> String {
    let rects = input
        .lines()
        .map(Rect::from_string)
        .collect::<Result<Vec<Rect>, Box<std::error::Error>>>()
        .unwrap();

    for rect1 in rects.iter() {
        let mut intersections = 0;

        for rect2 in rects.iter() {
            if ptr::eq(rect1, rect2) {
                continue;
            }
            if rect1.interset(rect2) {
                intersections += 1;
            }
        }
        if intersections == 0 {
            return rect1.id.to_string();
        }
    }

    String::new()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(run("#123 @ 3,2: 5x4".to_string()), "123".to_string())
    }
}
