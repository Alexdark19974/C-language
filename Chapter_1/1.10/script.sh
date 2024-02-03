#! /bin/bash
src_dir="src"
obj_dir="obj"
bin_dir="bin"
c_files="*.c"
o_files="*.o"

mkdir  $src_dir $obj_dir $bin_dir
mv $c_files $src_dir
mv $o_files $obj_dir
