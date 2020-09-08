
use std::fmt;

struct Structure(i32);

impl fmt::Display for Structure {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{}", self.0)
	}
}

#[derive(Debug)]
struct MinMax(i64, i64);

impl fmt::Display for MinMax {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({} {})", self.0, self.1)
	}
}

#[derive(Debug)]
struct Point2D {
	x: f64,
	y: f64
}

impl fmt::Display for Point2D {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "x: {}, y: {}", self.x, self.y)
	}
}

#[derive(Debug)]
struct Complex {
	real: f64,
	imag: f64
}

impl fmt::Display for Complex {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{} + {}i", self.real, self.imag)
	}
}

fn main()
{
	println!("Structure Display: {}", Structure(3));

	let minmax = MinMax(3, 5);

	println!("MinMax Display: {}", minmax);
	println!("MinMax Debug: {:?}", minmax);

	let big = MinMax(-300, 300);
	let small_r = MinMax(-3, 3);

	println!("Big range is {big} and Small range is {small}",
		big = big,
		small = small_r);

	let point = Point2D { x: 3.3, y: 7.7 };

	println!("Point2D Display: {}", point);
	println!("Point2D Debug: {:?}", point);

	let complex = Complex { real : 3.3, imag : 7.2 };

	println!("Complex Display: {}", complex);
	println!("Complex Debug: {:?}", complex);

}
