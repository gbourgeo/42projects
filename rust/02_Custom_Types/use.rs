
#![allow(dead_code)]

enum Status {
	Rich,
	Poor,
}

enum Work {
	Civilian,
	Soldier,
}

fn main() {
	use crate::Status::{ Poor, Rich };
	use crate::Work::*;

	// Equivalent to Status::Poor
	let status = Poor;

	// Equivalent to Work::Civilian
	let work = Civilian;

	match status {
		Rich => println!("I am rich ! I have a lot of money."),
		Poor => println!("I am poor ! I have no money."),
	}

	match work {
		Civilian => println!("I am a civilian !"),
		Soldier => println!("i am a soldier !"),
	}
}
