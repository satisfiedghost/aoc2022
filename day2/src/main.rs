use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    if let Ok(lines) = read_lines("input.txt") {
        // Consumes the iterator, returns an (Optional) String
        process(lines);
    }
}

fn process(lines: io::Lines<io::BufReader<File>>) {
    let mut score1 = 0;
    let mut score2 = 0;
    for line in lines {
        if let Ok(ip) = line {
            let your_move = ip.chars().nth(2).unwrap();
            match ip.chars().nth(0).unwrap() {
                'A' => match your_move {
                    'X' => {
                        score1 += 1 + 3;
                        score2 += 3 + 0;
                    }
                    'Y' => {
                        score1 += 2 + 6;
                        score2 += 1 + 3;
                    }
                    'Z' => {
                        score1 += 3 + 0;
                        score2 += 2 + 6;
                    }
                    _ => println!("confused")
                },
                'B' => match your_move {
                    'X' => {
                        score1 += 1 + 0;
                        score2 += 1 + 0;
                    }
                    'Y' => {
                        score1 += 2 + 3;
                        score2 += 2 + 3;
                    }
                    'Z' => {
                        score1 += 3 + 6;
                        score2 += 3 + 6;
                    }
                    _ => println!("confused")
                },
                'C' => match your_move {
                    'X' => {
                        score1 += 1 + 6;
                        score2 += 2 + 0;
                    }
                    'Y' => {
                        score1 += 2 + 0;
                        score2 += 3 + 3;
                    }
                    'Z' => {
                        score1 += 3 + 3;
                        score2 += 1 + 6;
                    }
                    _ => println!("confused")
                },
                _ => println!("???")
            };
        }
    }
    println!("Part1: {}", score1);
    println!("Part2: {}", score2);
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path> {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
