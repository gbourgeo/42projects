
fn main()
{
	println!("Hello World !");
	println!("{} is an argument.", 2);
	println!("{0}, this is argument number 1:{1}, number 0:{0}, and 1 again {1}.", "0", "1");
	println!("Named argument: {subject} {verb} {cod}{end}",
		end="...",
		verb="goes",
		subject="Ilhan",
		cod="to the store alone");
	println!("{} of {:b}", 1, 2);
	println!("Width now: {number:>width$}0", number=1, width=6);
	println!("Width now: {number:<width$}0", number=1, width=6);
	println!("Width now: {number:>0width$}0", number=1, width=6);

	#[derive(Debug)]
	struct Structure(i32);

	println!("Structure got an i32 value of : {0:?}\nor: {0:#?}",
		Structure(3i32));

	let pi = 3.141592;

	println!("Pi is {:.2}", pi);

	// Printing structure
	#[derive(Debug)]
	struct Deep(Structure);

	println!("Deep is {:?}\nor: {0:#?}", Deep(Structure(7)));

	#[derive(Debug)]
	struct Person<'a> {
		name: &'a str,
		age: u8
	}

	let name = "peter";
	let age = 32;
	let peter = Person { name, age };
	println!("Person is {:#?}", peter);
}