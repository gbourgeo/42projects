

fn analyse_slice(slice: &[i32]) {
	println!("first element of the slice: {}", slice[0]);
	println!("the slice has {} elements", slice.len());
	println!("Array occupies: {}", std::mem::size_of_val(slice));
	println!("");
}

fn main() {
	let xs: [i32; 5] = [1, 2, 3, 4, 5];

	let ys: [i32; 500] = [0; 500];

	// Indexing starts at 0
	println!("first element of the array: {}", xs[0]);
	println!("second element of the array: {}", xs[1]);
	println!("Array size is: {}", xs.len());
	println!("Array occupies: {}", std::mem::size_of_val(&xs));
	println!("");

	println!("first element of the array: {}", ys[0]);
	println!("second element of the array: {}", ys[1]);
	println!("Array size is: {}", ys.len());
	println!("Array occupies: {}", std::mem::size_of_val(&ys));
	println!("");

	// Arrays can be automatically borrowed as slices
	println!("borrow the whole array as a slice");
	analyse_slice(&xs);
	analyse_slice(&xs[2 .. 3]);

	// Slices can point to a section of an array
	// They are of the form [starting_index..ending_index]
	// starting_index is the first position in the slice
	// ending_index is one more than the last position in the slice
	println!("borrow a section of the array as a slice");
	analyse_slice(&ys[1 .. 4]);

	// Out of bound indexing causes compile error
	// println!("{}", xs[5]);
}