use std::collections::HashMap;
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
    let mut lines: Vec<&str> = input.lines().collect();
    lines.sort_unstable();
    let mut guards: HashMap<usize, Guard> = HashMap::new();
    let mut guard_id = 0;
    let mut most_sleep = 0;
    let mut most_sleep_id = 0;
    let mut most_sleep_minute = 0;
    let mut sleep_start = 0;
    for line in lines.iter() {
        match &line[19..24] {
            "Guard" => {
                guard_id = line.split_whitespace().nth(3).unwrap()[1..]
                    .parse()
                    .expect("Cannot parse guard ID");
            }
            "falls" => {
                sleep_start = line.split_whitespace().nth(1).unwrap()[3..5]
                    .parse()
                    .expect("Cannot parse sleep start");
            }
            "wakes" => {
                let sleep_end: usize = line.split_whitespace().nth(1).unwrap()[3..5]
                    .parse()
                    .expect("Cannot parse sleep end");
                let guard = guards.entry(guard_id).or_insert(Guard {
                    sleep_schedule: [0; 60],
                    most_asleep: 0,
                });
                for i in sleep_start..sleep_end {
                    guard.sleep_schedule[i] += 1;
                    if guard.sleep_schedule[i] > guard.sleep_schedule[guard.most_asleep] {
                        guard.most_asleep = i;
                    }
                }
                if guard.sleep_schedule[guard.most_asleep] > most_sleep {
                    most_sleep = guard.sleep_schedule[guard.most_asleep];
                    most_sleep_minute = guard.most_asleep;
                    most_sleep_id = guard_id;
                }
            }
            _ => panic!("Wrong input format!"),
        }
    }
    most_sleep_id * most_sleep_minute
}

struct Guard {
    sleep_schedule: [usize; 60],
    most_asleep: usize,
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn run_test() {
        assert_eq!(
            run("[1518-11-01 00:00] Guard #10 begins shift
[1518-11-01 00:05] falls asleep
[1518-11-01 00:25] wakes up
[1518-11-01 00:30] falls asleep
[1518-11-01 00:55] wakes up
[1518-11-01 23:58] Guard #99 begins shift
[1518-11-02 00:40] falls asleep
[1518-11-02 00:50] wakes up
[1518-11-03 00:05] Guard #10 begins shift
[1518-11-03 00:24] falls asleep
[1518-11-03 00:29] wakes up
[1518-11-04 00:02] Guard #99 begins shift
[1518-11-04 00:36] falls asleep
[1518-11-04 00:46] wakes up
[1518-11-05 00:03] Guard #99 begins shift
[1518-11-05 00:45] falls asleep
[1518-11-05 00:55] wakes up"),
            4455
        )
    }
}
