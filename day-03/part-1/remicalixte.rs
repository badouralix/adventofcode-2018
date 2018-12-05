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

    fn interset(&self, other: &Rect) -> Option<Rect> {
        let x = max(self.x, other.x);
        let y = max(self.y, other.y);
        let w = min(self.x + self.w - x, other.x + other.w - x);
        let h = min(self.y + self.h - y, other.y + other.h - y);
        if w <= 0 || h <= 0 {
            return None;
        }
        Some(Rect { id: 0, x, y, w, h })
    }
}

fn run(input: String) -> String {
    let rects = input
        .lines()
        .map(Rect::from_string)
        .collect::<Result<Vec<Rect>, Box<std::error::Error>>>()
        .unwrap();

    let mut intersections: Vec<Rect> = Vec::new();

    for rect1 in rects.iter() {
        for rect2 in rects.iter() {
            if ptr::eq(rect1, rect2) {
                continue;
            }
            match rect1.interset(rect2) {
                Some(surface) => intersections.push(surface),
                None => (),
            }
        }
    }

    let mut points = HashSet::new();
    for intersection in intersections {
        for i in intersection.x..(intersection.x + intersection.w) {
            for j in intersection.y..(intersection.y + intersection.h) {
                points.insert((i, j));
            }
        }
    }
    points.len().to_string()
}

fn run_hashmap(input: String) -> String {
    let mut points = HashMap::new();
    for rect in input.lines().map(Rect::from_string) {
        let rect = rect.unwrap();
        for i in rect.x..(rect.x + rect.w) {
            for j in rect.y..(rect.y + rect.h) {
                *points.entry((i, j)).or_insert(0) += 1;
            }
        }
    }
    points.values().filter(|c| **c > 1).count().to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(
            run("#123 @ 3,2: 5x4\n#123 @ 3,3: 5x1".to_string()),
            "5".to_string()
        )
    }
}
