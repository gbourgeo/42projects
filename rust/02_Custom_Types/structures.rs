
use std::fmt;

#[derive(Debug)]
struct Person <'a> {
	name: &'a str,
	age: u8,
}

struct Point {
	x: f32,
	y: f32,
}

// #[allow(dead_code)]
struct Rectangle {
	top_left: Point,
	bottom_right: Point,
}

struct Nil;

struct Pair(i32, f32);

// Personnal exercice
impl fmt::Display for Rectangle {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		writeln!(f, "Rectangle (")?;
		writeln!(f, "top_left    : x:{} y:{}", self.top_left.x, self.top_left.y)?;
		writeln!(f, "bottom_right: x:{} y:{}", self.bottom_right.x, self.bottom_right.y)?;
		writeln!(f, "longueur    : {}", (self.top_left.x - self.bottom_right.x).abs())?;
		writeln!(f, "largeur     : {})", (self.top_left.y - self.bottom_right.y).abs())
	}
}

// Exercices
fn rect_area(rectangle: &Rectangle) -> f32 {
	let longueur = rectangle.top_left.x - rectangle.bottom_right.x;
	let largeur = rectangle.top_left.y - rectangle.bottom_right.y;

	(longueur * largeur).abs()
}

fn square(lower_left: Point, width_height: f32) -> Rectangle {
	Rectangle {
		top_left:     Point { x: lower_left.x, y: lower_left.y + width_height },
		bottom_right: Point { x: lower_left.x + width_height, y: lower_left.y }
	}
}
//

fn main() {
	let name = "Peter";
	let age = 32;
	let peter = Person { name, age };

	println!("{:?}\n", peter);

	let point: Point = Point { x: 10.3, y: 0.4 };

	println!("Point x={} y={}\n", point.x, point.y);

	let other_point = Point { x: 5.2, ..point };

	println!("Other point x={} y={}\n", other_point.x, other_point.y);

	let Point { x: top_edge, y: left_edge } = point;

	let _rectangle = Rectangle {
		top_left: Point { x: left_edge, y: top_edge },
		bottom_right: other_point,
	};

	let _nil = Nil;

	let pair = Pair(1, 3.2);

	println!("pair contains: {:?} and {:?}", pair.0, pair.1);

	let Pair(integer, decimal) = pair;

	println!("pair contains: {:?} and {:?}", integer, decimal);

	//Exercices
	println!("{} area is {}", _rectangle, rect_area(&_rectangle));
	println!("{}", square(Point { x: 3.5, y: 7.9 }, 3.1));
}
