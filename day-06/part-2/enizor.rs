use std::env::args;
use std::time::Instant;

fn main() {
    let now = Instant::now();
    let output: usize = run(&args().nth(1).expect("Please provide an input"), 10_000);
    let elapsed = now.elapsed();
    println!(
        "_duration:{}.{}",
        elapsed.as_secs() * 1000 + u64::from(elapsed.subsec_millis()),
        elapsed.subsec_micros() - (elapsed.subsec_millis() * 1000)
    );
    println!("{}", output);
}

fn run(input: &str, total: usize) -> usize {
    let mut points = vec![];
    let mut min_x = 1000;
    let mut min_y = 1000;
    let mut max_x = 0;
    let mut max_y = 0;
    // parse the input
    for coords in input.lines() {
        let mut point = coords.split(", ");
        let x = point.next().unwrap().parse().expect("Cannot parse X coord");
        let y = point.next().unwrap().parse().expect("Cannot parse Y coord");
        points.push((x, y));
        // update min & max coordinates
        if x < min_x {
            min_x = x;
        }
        if x + 1 > max_x {
            max_x = x + 1;
        }
        if y < min_y {
            min_y = y;
        }
        if y + 1 > max_y {
            max_y = y + 1;
        }
    }

    let points_close = is_close(&points[1..], points[0].0, points[0].0, total);
    if points_close.0 {
        // extend the grid
        let extend_size = ((total-points_close.1)/points.len() )as isize;
        min_x -= extend_size;
        min_y -= extend_size;
        max_x += extend_size;
        max_y += extend_size;
    }
    // Iterate over the grid to count the size of the domains
    let mut max_domain_size = 0;
    for x in min_x..max_x {
        for y in min_y..max_y {
            if is_close(&points, x, y, total).0 {
                max_domain_size += 1;
            }
        }
    }

    max_domain_size
}

fn is_close(points: &[(isize, isize)], x: isize, y: isize, total: usize) -> (bool, usize) {
    let mut res = 0;
    let mut points_iter = points.iter();
    let mut point = points_iter.next();
    while res < total && point.is_some() {
        let (x1, y1) = point.unwrap();
        res += taxicab(x, y, *x1, *y1);
        point = points_iter.next();
    }
    (res < total, res)
}

fn taxicab(x1: isize, y1: isize, x2: isize, y2: isize) -> usize {
    (x1 as isize - x2 as isize).abs() as usize + (y1 as isize - y2 as isize).abs() as usize
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(
            run(
                "1, 1
1, 6
8, 3
3, 4
5, 5
8, 9",
                32
            ),
            16
        )
    }
}
