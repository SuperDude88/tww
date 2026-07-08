#!/usr/bin/env python3

from argparse import ArgumentParser
import struct
import os
from enum import Enum
from binary_funcs import read_f32, read_u8


def write_macro_line(file, line):
    line_with_escape = line + (" "*(99-len(line))) + "\n"
    file.write(line_with_escape)

def convert_binary_to_vec3_c_source(src_path, dest_path, symbol_name, scope):
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:
        
        if scope == "local":
            var_def_prefix = "static "
        else:
            var_def_prefix = ""

        write_macro_line(c_file, f"{var_def_prefix}Vec {symbol_name}[] = {{")
        
        while True:
            try:
                x, y, z = read_f32(binary_file), read_f32(binary_file), read_f32(binary_file)
            except EOFError:
                break
            
            line_elements = []
            def add_vec_to_line(x, y, z):
                line_elements.append(f"{{{x:f}f, {y:f}f, {z:f}f}}")
            
            add_vec_to_line(x, y, z)

            write_macro_line(c_file, "    " + ", ".join(line_elements) + ",")
        
        write_macro_line(c_file, "};")

def convert_binary_to_vec2_c_source(src_path, dest_path, symbol_name, scope):
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:
        
        if scope == "local":
            var_def_prefix = "static "
        else:
            var_def_prefix = ""

        write_macro_line(c_file, f"{var_def_prefix}cXy {symbol_name}[] = {{")
        
        while True:
            try:
                x, y = read_f32(binary_file), read_f32(binary_file)
            except EOFError:
                break
            
            line_elements = []
            def add_vec_to_line(x, y):
                line_elements.append(f"{{{x:f}f, {y:f}f}}")
            
            add_vec_to_line(x, y)

            write_macro_line(c_file, "    " + ", ".join(line_elements) + ",")
        
        write_macro_line(c_file, "};")

def convert_binary_to_color_c_source(src_path, dest_path, symbol_name, scope):
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:
        
        if scope == "local":
            var_def_prefix = "static "
        else:
            var_def_prefix = ""

        write_macro_line(c_file, f"{var_def_prefix}GXColor {symbol_name}[] = {{")
        
        while True:
            try:
                r, g, b, a = read_u8(binary_file), read_u8(binary_file), read_u8(binary_file), read_u8(binary_file)
            except EOFError:
                break
            
            line_elements = []
            def add_color_to_line(r, g, b, a):
                line_elements.append(f"{{0x{r:02X}, 0x{g:02X}, 0x{b:02X}, 0x{a:02X}}}")
            
            add_color_to_line(r, g, b, a)

            write_macro_line(c_file, "    " + ", ".join(line_elements) + ",")
        
        write_macro_line(c_file, "};")


def main():
    parser = ArgumentParser(
        description="Converts a binary file containing a material display list to a macro for defining an array of u8 type"
    )
    parser.add_argument("src_path", type=str, help="Binary source file path")
    parser.add_argument("dest_path", type=str, help="Destination C include file path")
    parser.add_argument(
        "--type",
        type=str,
        help="Data type",
    )
    parser.add_argument(
        "--symbol",
        type=str,
        help="Symbol name",
    )
    parser.add_argument(
        "--scope",
        choices=["global", "local"],
        default="local",
        help="The scope of the symbol",
    )

    args = parser.parse_args()

    # TODO: align the array elements, skip trailing 0s on floats
    # Maybe also generalize it, so instead it specifies element type + component count
    # instead of specific combinations? Would make it easier to support things like
    # mDoExt_3DlineMat1_c::setMaterial::l_normal *but* makes usage of Vec/cXy/etc less straightforward
    if args.type == "pos3" or args.type == "nrm3":
        convert_binary_to_vec3_c_source(args.src_path, args.dest_path, args.symbol, args.scope)
    elif args.type == "uv":
        convert_binary_to_vec2_c_source(args.src_path, args.dest_path, args.symbol, args.scope)
    elif args.type == "rgba8":
        convert_binary_to_color_c_source(args.src_path, args.dest_path, args.symbol, args.scope)
    else:
        raise Exception(f"Unknown data type: {args.type}")


if __name__ == "__main__":
    main()
