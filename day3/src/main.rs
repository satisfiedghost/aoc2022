use std::collections::HashMap;
use std::collections::HashSet;

fn main() {
    // convert input to item values
    let rucksacks: Vec<Vec<u32>> =
    std::io::stdin()
    .lines()
    .map(|line| line.unwrap().chars().map(|c| {
        let mut val = c as u32;

        if val <= 'Z' as u32 {
            val = val + 1 - 'A' as u32 + 26;
        } else {
            val = val + 1 - 'a' as u32;
        }
        val
    }).collect())
    .collect();

    println!("p1: {}", part1(&rucksacks));
    println!("p2: {}", part2(&rucksacks));
}

fn part1(sacks: &Vec<Vec<u32>>) -> u32 {
    let mut map = HashMap::new();
    let mut sum = 0;

    // iterate over first half, keep track of what we see
    // then iterate over 2nd half and check for a dup
    for sack in sacks {
        let mut idx = 0;
        while idx < sack.len() / 2 {
            map.insert(sack[idx], true);
            idx += 1;
        }
        while idx < sack.len() {
            if map.contains_key(&sack[idx]) {
                sum += sack[idx];
                map.drain();
                break;
            }
            idx += 1;
        }
    }
    sum
}

fn part2(sacks: &Vec<Vec<u32>>) -> u32 {
    let mut map: HashMap<u32, u32> = HashMap::new();
    let mut sum = 0;

    // all sacks
    for (idx, sack) in sacks.iter().enumerate() {

        // keep track of what we see, and don't count dups
        // if it's not a dup, add it
        let mut set = HashSet::new();
        for item in sack {
            if set.contains(item) {
                continue;
            } else {
                set.insert(item);
            }

            if map.contains_key(item) {
                *map.get_mut(item).unwrap() += 1;
            } else {
                map.insert(*item, 1);
            }
        }

        // reset for every group of 3, and check which item they have in common
        if (idx + 1) % 3 == 0 {
            for item in map.keys() {
                if *map.get(item).unwrap() == 3 {
                    sum += item;
                    break;
                }
            }
            map.drain();
        }
    }

    sum
}