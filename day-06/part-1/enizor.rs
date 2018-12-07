use std::collections::{BTreeSet, HashMap};
use std::env::args;
use std::time::Instant;

fn main() {
    let now = Instant::now();
    let output: usize = run(&args().nth(1).expect("Please provide an input"));
    let elapsed = now.elapsed();
    println!(
        "_duration:{}.{}",
        elapsed.as_secs() * 1000 + u64::from(elapsed.subsec_millis()),
        elapsed.subsec_micros() - (elapsed.subsec_millis() * 1000)
    );
    println!("{}", output);
}

fn run(input: &str) -> usize {
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
        } else if x + 1 > max_x {
            max_x = x + 1;
        }
        if y < min_y {
            min_y = y;
        } else if y + 1 > max_y {
            max_y = y + 1;
        }
    }
    let mut infinite_indexes = BTreeSet::new();
    // Check the regions on the side : those are the infinite ones
    // Then only count for non-infinite indexes
    for x in min_x..max_x {
        if let Some(index) = closest_point(&points, x, 0) {
            infinite_indexes.insert(index);
        }
        if let Some(index) = closest_point(&points, x, max_y - 1) {
            infinite_indexes.insert(index);
        }
    }
    for y in min_y..max_y {
        if let Some(index) = closest_point(&points, 0, y) {
            infinite_indexes.insert(index);
        }
        if let Some(index) = closest_point(&points, max_x - 1, y) {
            infinite_indexes.insert(index);
        }
    }

    // Iterate over the grid to count the size of the domains
    // when the domain's index is not in the infinite_indexes set
    let mut domains = HashMap::new();
    let mut max_domain_size = 0;
    for x in min_x + 1..max_x - 1 {
        for y in min_y + 1..max_y - 1 {
            if let Some(index) = closest_point(&points, x, y) {
                if !infinite_indexes.contains(&index) {
                    let mut domain_size = domains.entry(index).or_insert(0);
                    *domain_size += 1;
                    if *domain_size > max_domain_size {
                        max_domain_size = *domain_size;
                    }
                }
            }
        }
    }
    max_domain_size
}

fn closest_point(points: &[(usize, usize)], x: usize, y: usize) -> Option<usize> {
    let mut min_dist = None;
    let mut min_index = None;
    for (index, (px, py)) in points.iter().enumerate() {
        let new_dist = taxicab(x, y, *px, *py);
        if min_dist == None || new_dist < min_dist.unwrap() {
            min_dist = Some(new_dist);
            min_index = Some(index);
        } else if new_dist == min_dist.unwrap() {
            min_index = None;
        }
    }
    min_index
}

fn taxicab(x1: usize, y1: usize, x2: usize, y2: usize) -> usize {
    (x1 as isize - x2 as isize).abs() as usize + (y1 as isize - y2 as isize).abs() as usize
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(
            run("1, 1
1, 6
8, 3
3, 4
5, 5
8, 9"),
            17
        )
    }
}
