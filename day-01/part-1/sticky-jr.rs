use std::env::args;

fn main() {

    println!(
        "{}", 
        args().nth(1)                       // Take first command-line argument
              .expect("No input")           // Panic if absent
              .lines()                      // Decompose into lines
              .map(|x| x.parse::<i64>().expect("Error") ) // Convert lines into (signed) integer
              .sum::<i64>()                        // Sum all lines
    )
}

