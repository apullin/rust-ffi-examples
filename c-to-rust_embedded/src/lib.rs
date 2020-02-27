#![crate_type = "staticlib"]

#![no_std]
#![feature(lang_items)]
#![no_builtins]

extern crate panic_halt;


#[no_mangle]
pub extern fn double_input(input: i32) -> i32 {
    input * 18
}

