use std::collections::{HashMap, HashSet};
use std::env::args;
use std::time::Instant;

fn main() {
    let now = Instant::now();
    let output: usize = run(&args().nth(1).expect("Please provide an input"), 5, 60);
    let elapsed = now.elapsed();
    println!(
        "_duration:{}.{}",
        elapsed.as_secs() * 1000 + u64::from(elapsed.subsec_millis()),
        elapsed.subsec_micros() - (elapsed.subsec_millis() * 1000)
    );
    println!("{}", output);
}

fn run(input: &str, nb_workers: usize, base_time: usize) -> usize {
    let mut steps = HashMap::new();
    let mut workers = vec![(None, 0); nb_workers];
    let mut time = 0;
    for line in input.lines() {
        let x = line.chars().nth(5).expect("Cannot parse 1st step") as u8;
        let y = line.chars().nth(36).expect("Cannot parse 2nd step") as u8;
        {
            let steps_needed = steps.entry(y).or_insert_with(HashSet::new);
            steps_needed.insert(x);
        }
        steps.entry(x).or_insert_with(HashSet::new);
    }
    assign_workers(&mut workers, &mut steps, base_time);
    let mut working = true;
    while working {
        let (finished, time_spent) = update_workers(&mut workers);
        for task in finished {
            for task2 in steps.values_mut() {
                task2.remove(&task);
            }
        }
        time += time_spent;
        assign_workers(&mut workers, &mut steps, base_time);
        working = workers.iter().any(|x| x.0.is_some());
    }
    time
}

fn availables(steps: &HashMap<u8, HashSet<u8>>) -> Vec<u8> {
    let mut res = vec![];
    for (step, necessary) in steps.iter() {
        if necessary.is_empty() {
            res.push(*step);
        }
    }
    res
}

fn update_workers(workers: &mut Vec<(Option<u8>, usize)>) -> (Vec<u8>, usize) {
    let mut res = vec![];
    let mut min_time = None;
    for (step, time_remaining) in workers.iter() {
        if step.is_some() && (min_time.is_none() || *time_remaining < min_time.unwrap()) {
            min_time = Some(*time_remaining);
        }
    }
    for (step, time_remaining) in workers.iter_mut() {
        if step.is_some() {
            *time_remaining -= min_time.unwrap();
            if *time_remaining == 0 {
                res.push(step.unwrap());
                *step = None;
            }
        }
    }

    (res, min_time.unwrap())
}

fn assign_workers(
    workers: &mut Vec<(Option<u8>, usize)>,
    steps: &mut HashMap<u8, HashSet<u8>>,
    base_time: usize,
) {
    let mut steps_availables = availables(steps);
    steps_availables.sort_unstable();
    let mut cursor = 0;
    for (step, time_remaining) in workers.iter_mut() {
        if cursor < steps_availables.len() && step.is_none() {
            *step = Some(steps_availables[cursor]);
            *time_remaining = steps_availables[cursor] as usize + base_time - 64;
            steps.remove(&steps_availables[cursor]);
            cursor += 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(
            run(
                "Step C must be finished before step A can begin.
Step C must be finished before step F can begin.
Step A must be finished before step B can begin.
Step A must be finished before step D can begin.
Step B must be finished before step E can begin.
Step D must be finished before step E can begin.
Step F must be finished before step E can begin.
",
                2,
                0
            ),
            15
        )
    }
}
