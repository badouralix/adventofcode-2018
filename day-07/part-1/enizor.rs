use std::collections::{HashMap, HashSet};
use std::env::args;
use std::time::Instant;

fn main() {
    let now = Instant::now();
    let output: String = run(&args().nth(1).expect("Please provide an input"));
    let elapsed = now.elapsed();
    println!(
        "_duration:{}.{}",
        elapsed.as_secs() * 1000 + u64::from(elapsed.subsec_millis()),
        elapsed.subsec_micros() - (elapsed.subsec_millis() * 1000)
    );
    println!("{}", output);
}

fn run(input: &str) -> String {
    let mut res = String::from("");
    let mut steps = HashMap::new();
    for line in input.lines() {
        let x = line.chars().nth(5).expect("Cannot parse 1st step") as u8;
        let y = line.chars().nth(36).expect("Cannot parse 2nd step") as u8;
        {
            let steps_needed = steps.entry(y).or_insert_with(HashSet::new);
            steps_needed.insert(x);
        }
        steps.entry(x).or_insert_with(HashSet::new);
    }
    while !steps.is_empty() {
        let next_step = next_available(&steps);
        res.push(next_step as char);
        steps.remove(&next_step);
        for steps_necessary in steps.values_mut() {
            steps_necessary.remove(&next_step);
        }
    }
    res
}

fn next_available(steps: &HashMap<u8, HashSet<u8>>) -> u8 {
    let mut min = 255;
    for (step, necessary) in steps.iter() {
        if necessary.is_empty() && *step < min {
            min = *step;
        }
    }
    min
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(
            run("Step C must be finished before step A can begin.
Step C must be finished before step F can begin.
Step A must be finished before step B can begin.
Step A must be finished before step D can begin.
Step B must be finished before step E can begin.
Step D must be finished before step E can begin.
Step F must be finished before step E can begin.
"),
            "CABDFE"
        )
    }
}
